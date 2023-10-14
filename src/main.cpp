#include <dpp/dispatcher.h>
#include <iostream>
#include <dpp/dpp.h>
#include "secrets.hpp"
#include "cpu.hpp"
#include <format>
#include "assembler/assembler.hpp"


int main(){
  using std::string;
  using std::cout;
  using std::endl;


  dpp::cluster bot(DISCORD_APPLICATION_TOKEN);

  std::unique_ptr<Cpu::Cpu> cpu(new Cpu::Cpu());

  cpu->memory[0] = 0x69;
  cpu->memory[1] = 0x420;
  cpu->memory[2] = 0x69420;
  cpu->memory[3] = 0x42069;
  cpu->memory[4] = 0xdeadbeef;


  Assembler::tokenize(Assembler::test_asm);




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
          if(i > Cpu::MEMORY_MAX){
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
      }else if(event.command.get_command_name() == "dump_reg"){
        string* reg_str = new string();
        reg_str->append("```");
        reg_str->append(std::format("ZERO: {:#04x}\n",cpu->registers_gp[Cpu::REGISTER_ZERO]));
        reg_str->append(std::format("AT: {:#04x}\n",cpu->registers_gp[Cpu::REGISTER_AT]));
        reg_str->append(std::format("V0: {:#04x}\n",cpu->registers_gp[Cpu::REGISTER_V0]));
        reg_str->append(std::format("V1: {:#04x}\n",cpu->registers_gp[Cpu::REGISTER_V1]));
        for(uint8_t i = 0; i < 8; i++){
          reg_str->append(std::format("A{}: {:#04x} ",i,cpu->registers_gp[Cpu::REGISTER_A_START + i]));
        }
        reg_str->append("\n");
        for(uint8_t i = 0; i < 8; i++){
          reg_str->append(std::format("T{}: {:#04x} ",i,cpu->registers_gp[Cpu::REGISTER_T_START + i]));
        }
        reg_str->append("\n");
        for(uint8_t i = 0; i < 8; i++){
          reg_str->append(std::format("S{}: {:#04x} ",i,cpu->registers_gp[Cpu::REGISTER_S_START + i]));
        }
        reg_str->append("\n");
        reg_str->append(std::format("K0: {:#04x}\n",cpu->registers_gp[Cpu::REGISTER_K0]));
        reg_str->append(std::format("K1: {:#04x}\n",cpu->registers_gp[Cpu::REGISTER_K1]));
        reg_str->append(std::format("GP: {:#04x}\n",cpu->registers_gp[Cpu::REGISTER_GP]));
        reg_str->append(std::format("SP: {:#04x}\n",cpu->registers_gp[Cpu::REGISTER_STACK_POINTER]));
        reg_str->append(std::format("FP: {:#04x}\n",cpu->registers_gp[Cpu::REGISTER_FRAME_POINTER]));
        reg_str->append(std::format("RA: {:#04x}\n",cpu->registers_gp[Cpu::REGISTER_RETURN_ADDRESS]));
        reg_str->append("```");
        event.reply(reg_str->c_str());
      }
    });

  bot.on_ready([&bot](const dpp::ready_t &event) {
    cout << "Logged in as " << bot.me.username << "!\n";


    if(dpp::run_once<struct register_bot_commands>()){
      dpp::slashcommand mem_dump_command("dump_mem", "Dumps the memory of the CPU",bot.me.id);
      mem_dump_command.add_option(dpp::command_option(dpp::co_string, "offset", "The offset to start dumping from", false));
      bot.global_command_create(mem_dump_command);
      dpp::slashcommand reg_dump_command("dump_reg", "Dumps the registers of the CPU",bot.me.id);
      bot.global_command_create(reg_dump_command);
    }
  });


  bot.start(dpp::st_wait);
  std::cout << "Hello World!\n";
  return 0;
}
