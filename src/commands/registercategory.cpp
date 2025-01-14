#include <bits/stdc++.h>
#include <dpp/dpp.h>
#include "../def.h"
#include <sqlite3.h>

slashCommandFunction registercategory() {
    return [](dpp::cluster& bot, const dpp::slashcommand_t& event) {
        const std::vector<dpp::snowflake> roles = event.command.member.get_roles();
        bool hasRole = false;
        for (dpp::snowflake sf : roles) {
            if (sf & (dpp::permissions::p_manage_channels | dpp::permissions::p_administrator)) {
                hasRole = true;
            }
        }

        if (!hasRole) {
            event.reply("You don't have enough permissions.");
        } else {
            try {
                sqlite3 *db = NULL;
                int ret = sqlite3_open("./data.db", &db);
                if (ret == SQLITE_OK) {
                    std::string guild = std::to_string(event.command.guild_id);
                    std::string id = "NULL";
                    try {
                        id = std::to_string(dpp::snowflake(std::get<std::string>(event.get_parameter("id"))));
                    } catch(std::exception e) {}
                    std::string del = "DELETE FROM vccategory WHERE guild == " + guild + ";";
                    sqlite3_exec(db, del.c_str(), NULL, NULL, NULL);
                    if (id != "NULL") {
                        std::string ins = "INSERT INTO vccategory VALUES ("+guild+","+id+");";
                        sqlite3_exec(db, ins.c_str(), NULL, NULL, NULL);
                    }
                    sqlite3_close(db);
                }
            } catch(std::exception e) {
                event.reply("Failed to change target category.");
                return;
            }
            event.reply("succeeded to change target category.");
        }
    };
}

commandObject rgRegistercategory() {
    return [](const dpp::cluster& bot) {
        dpp::slashcommand cmd;
        cmd.set_name("registercategory")
            .set_description("Change target to creaete VC (needs Manage Channel permission to executer)")
            .set_application_id(bot.me.id)
            .add_option(
                dpp::command_option(
                    dpp::co_string,
                    "id",
                    "id of category",
                    false
                )
            )
            ;
        return cmd;
    };
}