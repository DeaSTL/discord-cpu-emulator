#include <dpp/dispatcher.h>
#include <iostream>
#include <dpp/dpp.h>
#include "secrets.hpp"
#include "cpu.hpp"
#include <format>


int main(){
  using std::string;


  dpp::cluster bot(DISCORD_APPLICATION_TOKEN);

  std::unique_ptr<Cpu::Cpu> cpu(new Cpu::Cpu());

  cpu->memory[0] = 0x69;
  cpu->memory[1] = 0x420;
  cpu->memory[2] = 0x69420;
  cpu->memory[3] = 0x42069;
  cpu->memory[4] = 0xdeadbeef;




  bot.on_slashcommand([&cpu](const dpp::slashcommand_t event) {
      if(event.command.get_command_name() == "dump_mem") {
        string* mem_str = new string();
        uint32_t offset = 0;
        std::string offset_str = std::get<std::string>(event.get_parameter("offset"));
        if(offset_str != ""){
          offset = std::stoi(offset_str);
        }
        mem_str->append("```");
        for(uint64_t i = (8 * offset); i < 256 + (8 * offset); i++){
          if(i > MEMORY_MAX){
            mem_str->append("Ain't got that much memory chief\n");
            break;
          }
          if(i % 8 == 0){
            mem_str->append("\n");
            mem_str->append(std::format("{:#04x}: ",i));
          }
          mem_str->append(std::format("{:#04x} ",*((uint8_t*)(&cpu->memory) + i)));
        }
        mem_str->append("```");
        event.reply(mem_str->c_str());
      }

    });

  bot.on_ready([&bot](auto event) {
    if(dpp::run_once<struct register_bot_commands>()){
      dpp::slashcommand mem_dump_command("dump_mem", "Dumps the memory of the CPU",bot.me.id);
      mem_dump_command.add_option(dpp::command_option(dpp::co_string, "offset", "The offset to start dumping from", false));
      bot.global_command_create(mem_dump_command);
    }
  });


  bot.start(dpp::st_wait);
  std::cout << "Hello World!\n";
  return 0;
}
