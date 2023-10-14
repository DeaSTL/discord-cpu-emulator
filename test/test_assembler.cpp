#include "test_assembler.hpp"
#include "../src/cpu.hpp"


namespace Test {
  std::string tolower(std::string str){
    std::string lower = "";
    for(char c : str){
      lower += std::tolower(c);
    }
    return lower;
  }
  const std::vector<Cpu::instruction> test_instructions = {
    Cpu::instructions::J_,
    Cpu::instructions::ADD,
    Cpu::instructions::LW,
    Cpu::instructions::SW,
    Cpu::instructions::BEQ,
    Cpu::instructions::BNE,
    Cpu::instructions::SLT,
    Cpu::instructions::ADDI,
    Cpu::instructions::SUB,
    Cpu::instructions::AND,
    Cpu::instructions::OR,
    Cpu::instructions::XOR,
    Cpu::instructions::NOR,
    Cpu::instructions::SLL,
    Cpu::instructions::SRL,
    Cpu::instructions::SRA,
    Cpu::instructions::JR,
    Cpu::instructions::JAL,
    Cpu::instructions::JALR,
    Cpu::instructions::MFHI,
    Cpu::instructions::MFLO,
    Cpu::instructions::MULT,
    Cpu::instructions::MULTU,
    Cpu::instructions::DIV,
    Cpu::instructions::DIVU,
    Cpu::instructions::ADDU,
    Cpu::instructions::SUBU,
    Cpu::instructions::ANDI,
    Cpu::instructions::ORI,
    Cpu::instructions::LUI,
    Cpu::instructions::SLTI,
    Cpu::instructions::SLTIU,
    Cpu::instructions::LB,
    Cpu::instructions::LBU,
    Cpu::instructions::LHU,
    Cpu::instructions::SB,
    Cpu::instructions::SH,
  };
  typedef struct expected_data{
    std::vector<Assembler::token> tokens;
    std::string line;
  } expected_data;
  expected_data instructionToLine(Cpu::instruction instruction){
    expected_data data;
    data.line = "";
    data.tokens.push_back(Assembler::token{.type = Assembler::TokenType::INSTRUCTION, .value = tolower(instruction.name)});
    if(instruction.type == Cpu::InstructionType::J){
      data.line += tolower(instruction.name) + "->" + std::to_string(instruction.imm);
      data.tokens.push_back(Assembler::token{.type = Assembler::TokenType::LABEL, .value = std::to_string(instruction.imm)});
    }
    if(instruction.type == Cpu::InstructionType::R){
      data.line += tolower(instruction.name) + " $" + 
        std::to_string(instruction.rd) + " $" + 
        std::to_string(instruction.rs) + " " + 
        std::to_string(instruction.rt);
      data.tokens.push_back(Assembler::token{.type = Assembler::TokenType::REGISTER, .value = std::to_string(instruction.rd)});
      data.tokens.push_back(Assembler::token{.type = Assembler::TokenType::REGISTER, .value = std::to_string(instruction.rs)});
      data.tokens.push_back(Assembler::token{.type = Assembler::TokenType::REGISTER, .value = std::to_string(instruction.rt)});
    }
    if(instruction.type == Cpu::InstructionType::I){
      data.line += tolower(instruction.name) + " $" + 
        std::to_string(instruction.rt) + " $" + 
        std::to_string(instruction.rs) + " " + 
        std::to_string(instruction.imm);
      data.tokens.push_back(Assembler::token{.type = Assembler::TokenType::REGISTER, .value = std::to_string(instruction.rt)});
      data.tokens.push_back(Assembler::token{.type = Assembler::TokenType::REGISTER, .value = std::to_string(instruction.rs)});
      data.tokens.push_back(Assembler::token{.type = Assembler::TokenType::DECIMAL, .value = std::to_string(instruction.imm)});
    }
    return data;
  }
  bool testTokenizer(){
    std::cout << "Testing tokenizer" << std::endl;
    std::string test_asm = "";
    std::vector<expected_data> expected; 
    for(Cpu::instruction inst : test_instructions){
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
    if(tokens.size() != expected_tokens.size()){
      std::cout << "Expected " << expected_tokens.size() << " tokens but got " << tokens.size() << std::endl;
    }
    for(size_t i = 0; i < expected_tokens.size(); i++ ){
      if(expected_tokens[i].type != tokens[i].type || expected_tokens[i].value != tokens[i].value){
        std::cout << "Expected: ";
        expected_tokens[i].print();
        std::cout << "Got: \n";
        tokens[i].print();
        return false;
      }else{
        std::cout << "Testing: ";
        expected_tokens[i].print();
      }
      if(i > tokens.size()){
        std::cout << "Expected " << expected_tokens.size() << " tokens but got " << tokens.size() << std::endl;
        return false;
      }
    }

    return false;
  }
  bool testAssembler() {
    testTokenizer();

    return true;
  }
}
