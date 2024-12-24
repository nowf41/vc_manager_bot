#pragma once
#define rep(i,n) for (std::int i = 0; i < (n); i++)
#define commandObject std::function<dpp::slashcommand(dpp::cluster&)>
#define slashCommandFunction std::function<void(dpp::cluster&, const dpp::slashcommand_t&)>
#define slashCommands std::map<std::string, std::pair<commandObject, slashCommandFunction>>