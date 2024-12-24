#include <bits/stdc++.h>
#include <dpp/dpp.h>
#include <sqlite3.h>
#include "../def.h"

slashCommandFunction createvc() {
    return [](dpp::cluster& bot, const dpp::slashcommand_t& event) {
        try {
            dpp::snowflake parent_id = NULL;
            try {
                // try to get category id from guild id
                sqlite3 *db = NULL;
                int ret = sqlite3_open("./data.db", &db);
                if (ret == SQLITE_OK) {
                    std::string sql = "SELECT * FROM vccategory WHERE guild == " + std::to_string(event.command.guild_id);
                    sqlite3_stmt *stmt;
                    ret = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
                    if (ret == SQLITE_OK) {
                        if (sqlite3_step(stmt) == SQLITE_ROW) {
                            parent_id = dpp::snowflake(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))));
                        }
                        sqlite3_finalize(stmt);
                    }
                    sqlite3_close(db);
                }
            } catch(std::exception e){}
            dpp::channel vc;
            vc.set_name(std::get<std::string>(event.get_parameter("name")));
            vc.set_guild_id(event.command.guild_id);
            vc.set_type(dpp::channel_type::CHANNEL_VOICE);
            if (parent_id != NULL) {
                vc.set_parent_id(parent_id);
            }

            bot.channel_create(vc);

            // report that succeed
            event.reply("Created!");
        } catch (std::exception e) {
            std::cout << e.what() << std::endl;
            event.reply("Failed.");
        }
    };
}

commandObject rgCreatevc() {
    return [](const dpp::cluster& bot) {
        dpp::slashcommand cmd;
        cmd.set_name("createvc")
            .set_description("Create a specified VC channel")
            .set_application_id(bot.me.id)
            .add_option(
                dpp::command_option(
                    dpp::co_string,
                    "name",
                    "Name to create",
                    true
                )
            )
            ;
        return cmd;
    };
}