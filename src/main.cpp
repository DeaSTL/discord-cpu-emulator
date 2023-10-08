#include <iostream>
#include <dpp/dpp.h>
#include "secrets.hpp"


int main()
{
    dpp::cluster bot(DISCORD_APPLICATION_TOKEN);

    bot.on_slashcommand([](auto event) {
        if(event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        }

    });

    bot.on_ready([&bot](auto event) {
        if(dpp::run_once<struct register_bot_commands>()){
          bot.global_command_create(
              dpp::slashcommand("ping", "Ping the bot",bot.me.id)
          );
        }
    });


    bot.start(dpp::st_wait);
    std::cout << "Hello World!\n";
    return 0;
}
