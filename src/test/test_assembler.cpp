#include "test_assembler.hpp"
#include "../cpu_instructions.hpp"
#include "../assembler/assembler.hpp"
#include <catch2/catch_test_macros.hpp>
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
    typedef struct test_data_line{
      std::vector<Assembler::token> tokens;
      std::string line;
      void print(){
        std::cout << "Line: " << line << std::endl;
        std::cout << "Tokens: " << std::endl;
        for(Assembler::token token : tokens){
          token.print();
        }
      }
    } expected_data;
    test_data_line instructionToLine(CpuInstructions::instruction instruction){
      test_data_line data;
      instruction.fd = rand() % 8;
      instruction.fs = rand() % 8;
      instruction.ft = rand() % 8;
      instruction.rd = rand() % 8;
      instruction.rs = rand() % 8;
      instruction.rt = rand() % 8;
      instruction.imm = rand() % 100;

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
          std::to_string(instruction.rt) + " $s" + std::to_string(instruction.rs) + " " + 
          std::to_string(instruction.imm);
        data.tokens.push_back(Assembler::token{.type = Assembler::TokenType::REGISTER, .value = "s" + std::to_string(instruction.rt)});
        data.tokens.push_back(Assembler::token{.type = Assembler::TokenType::REGISTER, .value = "s" + std::to_string(instruction.rs)});
        data.tokens.push_back(Assembler::token{.type = Assembler::TokenType::DECIMAL, .value = std::to_string(instruction.imm)});
      }
      return data;
    }

    bool compareMockTokens(test_data_line line){
      std::vector<Assembler::token> tokens = Assembler::tokenize(line.line);
      if(tokens.size() != line.tokens.size()){
        std::cout << "Token size mismatch expected: " << line.tokens.size() << " got: " << tokens.size() << std::endl;
        return false;
      }
      for(size_t i = 0; i < tokens.size(); i++){
        if(tokens[i].type != line.tokens[i].type){
          std::cout << "Token type mismatch expected: " << (int)line.tokens[i].type << " got: " << (int)tokens[i].type << std::endl;
          return false;
        }
        if(tokens[i].value != line.tokens[i].value){
          std::cout << "Token value mismatch expected: " << line.tokens[i].value << " got: " << tokens[i].value << std::endl;
          return false;
        }
      }
      return true;
    };

    TEST_CASE("Test assembler tokenize", "[assembler]"){
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::ADD)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::LW)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::SW)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::BEQ)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::BNE)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::SLT)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::ADDI)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::SUB)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::AND)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::OR)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::XOR)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::NOR)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::SLL)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::SRL)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::SRA)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::JR)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::JAL)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::JALR)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::MFHI)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::MFLO)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::MULT)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::MULTU)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::DIV)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::DIVU)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::ADDU)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::SUBU)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::ANDI)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::ORI)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::LUI)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::SLTI)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::SLTIU)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::LB)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::LBU)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::LHU)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::SB)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::SH)));
      REQUIRE(compareMockTokens(instructionToLine(CpuInstructions::J_)));
    }


  }
}
