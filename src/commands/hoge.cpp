#include <bits/stdc++.h>
#include <dpp/dpp.h>
#include "../def.h"

slashCommandFunction hoge() {
    return [](dpp::cluster& bot, const dpp::slashcommand_t& event) {
        event.reply("Fuga!");
    };
}

commandObject rgHoge() {
    return [](const dpp::cluster& bot) {
        return dpp::slashcommand("hoge", "hoge fuga!", bot.me.id);
    };
}