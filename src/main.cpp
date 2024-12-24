#include <fstream>
#include <dpp/dpp.h>
#include <bits/stdc++.h>
#include "allCommands.h"
#include "def.h"

std::string BOT_TOKEN = "";

int main() {
    // load token
    {
        std::ifstream token_file("../token.txt");
        if (!token_file.fail()) {
            getline(token_file, BOT_TOKEN);
        } else {
            return 1;
        }
    }

    dpp::cluster bot(BOT_TOKEN);

    // logging
    bot.on_log(dpp::utility::cout_logger());

    // slash commands
    slashCommands commands;
    bot.on_slashcommand([&](const dpp::slashcommand_t& event) {
        std::string cmdName = event.command.get_command_name();
        if (commands.find(cmdName) != commands.end()) {
            commands.at(cmdName).second(bot, event);
        }
    });

    // register commands
    bot.on_ready([&](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            std::vector<dpp::slashcommand> v;
            for (auto& i : commands) {
                v.push_back(i.second.first(bot));
            }
            bot.global_bulk_command_create(v);
        }
    });

    // get commands
    commands = getCommands();

    // start
    bot.start(dpp::st_wait);
}