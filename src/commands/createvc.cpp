#include <bits/stdc++.h>
#include <dpp/dpp.h>
#include "../def.h"

slashCommandFunction createvc() {
    return [](dpp::cluster& bot, const dpp::slashcommand_t& event) {
        try {
            dpp::snowflake parent_id = NULL;
            try {
                // try to get category id from guild id
            } catch(std::exception e){}
            dpp::channel vc;
            vc.set_name(std::get<std::string>(event.get_parameter("name")));
            vc.set_guild_id(event.command.guild_id);
            vc.set_type(dpp::channel_type::CHANNEL_VOICE);
            vc.set_parent_id(dpp::snowflake(std::get<std::string>(event.get_parameter("id"))));
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
            .add_option(
                dpp::command_option(
                    dpp::co_string,
                    "id",
                    "id of category",
                    true
                )
            )
            ;
        return cmd;
    };
}