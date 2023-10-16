#include "test_assembler.hpp"
#include "../src/cpu_instructions.hpp"
#include "../src/assembler/assembler.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <memory> 

namespace MipsEmulator {
  namespace Test {
    std::string tolower(std::string str){
      std::string lower = "";
      for(char c : str){
        lower += std::tolower(c);
      }
      return lower;
    }
    const std::vector<CpuInstructions::instruction> test_instructions = {
      CpuInstructions::J_,
      CpuInstructions::ADD,
      CpuInstructions::LW,
      CpuInstructions::SW,
      CpuInstructions::BEQ,
      CpuInstructions::BNE,
      CpuInstructions::SLT,
      CpuInstructions::ADDI,
      CpuInstructions::SUB,
      CpuInstructions::AND,
      CpuInstructions::OR,
      CpuInstructions::XOR,
      CpuInstructions::NOR,
      CpuInstructions::SLL,
      CpuInstructions::SRL,
      CpuInstructions::SRA,
      CpuInstructions::JR,
      CpuInstructions::JAL,
      CpuInstructions::JALR,
      CpuInstructions::MFHI,
      CpuInstructions::MFLO,
      CpuInstructions::MULT,
      CpuInstructions::MULTU,
      CpuInstructions::DIV,
      CpuInstructions::DIVU,
      CpuInstructions::ADDU,
      CpuInstructions::SUBU,
      CpuInstructions::ANDI,
      CpuInstructions::ORI,
      CpuInstructions::LUI,
      CpuInstructions::SLTI,
      CpuInstructions::SLTIU,
      CpuInstructions::LB,
      CpuInstructions::LBU,
      CpuInstructions::LHU,
      CpuInstructions::SB,
      CpuInstructions::SH,
    };
    typedef struct expected_data{
      std::vector<Assembler::token> tokens;
      std::string line;
    } expected_data;
    expected_data instructionToLine(CpuInstructions::instruction instruction){
      expected_data data;
      data.line = "";
      data.tokens.push_back(Assembler::token{.type = Assembler::TokenType::INSTRUCTION, .value = tolower(instruction.name)});
      if(instruction.type == CpuInstructions::InstructionType::J){
        data.line += tolower(instruction.name) + "->" + std::to_string(instruction.imm);
        data.tokens.push_back(Assembler::token{.type = Assembler::TokenType::LABEL, .value = std::to_string(instruction.imm)});
      }
      if(instruction.type == CpuInstructions::InstructionType::R){
        data.line += tolower(instruction.name) + " $s" + 
          std::to_string(instruction.rd) + " $s" + 
          std::to_string(instruction.rs) + " $s" + 
          std::to_string(instruction.rt);
        data.tokens.push_back(Assembler::token{.type = Assembler::TokenType::REGISTER, .value = "s" + std::to_string(instruction.rd)});
        data.tokens.push_back(Assembler::token{.type = Assembler::TokenType::REGISTER, .value = "s" + std::to_string(instruction.rs)});
        data.tokens.push_back(Assembler::token{.type = Assembler::TokenType::REGISTER, .value = "s" + std::to_string(instruction.rt)});
      }
      if(instruction.type == CpuInstructions::InstructionType::I){
        data.line += tolower(instruction.name) + " $s" + 
          std::to_string(instruction.rt) + " $s" + 
          std::to_string(instruction.rs) + " " + 
          std::to_string(instruction.imm);
        data.tokens.push_back(Assembler::token{.type = Assembler::TokenType::REGISTER, .value = "s" + std::to_string(instruction.rt)});
        data.tokens.push_back(Assembler::token{.type = Assembler::TokenType::REGISTER, .value = "s" + std::to_string(instruction.rs)});
        data.tokens.push_back(Assembler::token{.type = Assembler::TokenType::DECIMAL, .value = std::to_string(instruction.imm)});
      }
      return data;
    }
    bool testTokenizer(){
      std::cout << "Testing tokenizer" << std::endl;
      std::string test_asm = "";
      std::vector<expected_data> expected; 
      for(CpuInstructions::instruction inst :test_instructions){
        inst.imm = rand() % 0x69;
        inst.rd = rand() % 0x8;
        inst.rs = rand() % 0x8;
        inst.rt = rand() % 0x8;
        std::string line = instructionToLine(inst).line;
        expected_data data = instructionToLine(inst);
        expected.push_back(data);
        test_asm += line + "\n";
      }
      std::vector<Assembler::token> tokens = Assembler::tokenize(test_asm);
      std::vector<Assembler::token> expected_tokens;

      for(expected_data data : expected){
        for(Assembler::token token : data.tokens){
          expected_tokens.push_back(token);
        }
      }
      for(size_t i = 0; i < expected_tokens.size(); i++ ){
        if(expected_tokens[i].type != tokens[i].type || expected_tokens[i].value != tokens[i].value){
          std::cout << "Expected: ";
          expected_tokens[i].print();
          std::cout << "Got: \n";
          tokens[i].print();
          break;
        }else{
          std::cout << "Testing: ";
          expected_tokens[i].print();
        }
        if(i > tokens.size()){
          std::cout << "Expected " << expected_tokens.size() << " tokens but got " << tokens.size() << std::endl;
          break;
        }
      }

      if(tokens.size() != expected_tokens.size()){
        std::cout << "Expected " << expected_tokens.size() << " tokens but got " << tokens.size() << std::endl;
        return false;
      }else{
        std::cout << "Tokenizer test passed" << std::endl;
      }

      return false;
    }
    bool testAssembler() {
      testTokenizer();

      return true;
    }
  }
}
