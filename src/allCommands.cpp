#include <bits/stdc++.h>
#include <dpp/dpp.h>
#include "def.h"

#include "commands/ping.h"
#include "commands/createvc.h"
#include "commands/registercategory.h"

slashCommands getCommands() {
    slashCommands commands;

    commands.emplace("ping", make_pair(rgPing(), ping()));
    commands.emplace("createvc", make_pair(rgCreatevc(), createvc()));
    commands.emplace("registercategory", make_pair(rgRegistercategory(), registercategory()));

    return commands;
}