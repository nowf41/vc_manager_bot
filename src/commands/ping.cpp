#include <bits/stdc++.h>
#include <dpp/dpp.h>
#include "../def.h"

slashCommandFunction ping() {
    return [](dpp::cluster& bot, const dpp::slashcommand_t& event) {
        event.reply("Pong!");
    };
}

commandObject rgPing() {
    return [](const dpp::cluster& bot) {
        return dpp::slashcommand("ping", "ping pong!", bot.me.id);
    };
}