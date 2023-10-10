
#include "stdint.h"
#include "../src/cpu.hpp"
#include <string>
#include <iostream>
#include "stdio.h"

namespace Test{
  using std::string;
  using std::cout;
  using std::endl;
  typedef struct RType {
    string name;
    uint8_t opcode;
    uint8_t rs;
    uint8_t rt;
    uint8_t rd;
    uint8_t shamt;
    uint8_t funct;

  } RType;
  typedef struct IType {
    string name;
    uint8_t opcode;
    uint8_t rs;
    uint8_t rt;
    uint16_t immediate;

  } IType;
  typedef struct JType {
    string name;
    uint8_t opcode;
    uint32_t address;

  } JType;
  bool testInstructions(){
    bool final_status = true;
    JType JInstructions[100]{
      JType{"J",0x02, 0x00000000},
      JType{"JAL",0x03, 0x00000000}
    };
    RType RInstructions[100]{
      RType{"ADD",0x00, 0x01, 0x02, 0x03, 0x00, 0x20},
      RType{"ADDU",0x00, 0x01, 0x02, 0x03, 0x00, 0x21},
      RType{"AND",0x00, 0x01, 0x02, 0x03, 0x00, 0x24},
      RType{"DIV",0x00, 0x01, 0x02, 0x03, 0x00, 0x1A},
      RType{"DIVU",0x00, 0x01, 0x02, 0x03, 0x00, 0x1B},
      RType{"JALR",0x00, 0x01, 0x02, 0x03, 0x00, 0x09},
      RType{"JR",0x00, 0x01, 0x02, 0x03, 0x00, 0x08},
      RType{"MFHI",0x00, 0x01, 0x02, 0x03, 0x00, 0x10},
      RType{"MFLO",0x00, 0x01, 0x02, 0x03, 0x00, 0x12},
      RType{"MTHI",0x00, 0x01, 0x02, 0x03, 0x00, 0x11},
      RType{"MTLO",0x00, 0x01, 0x02, 0x03, 0x00, 0x13},
      RType{"MULT",0x00, 0x01, 0x02, 0x03, 0x00, 0x18},
      RType{"MULTU",0x00, 0x01, 0x02, 0x03, 0x00, 0x19},
      RType{"OR",0x00, 0x01, 0x02, 0x03, 0x00, 0x25},
      RType{"SLT",0x00, 0x01, 0x02, 0x03, 0x00, 0x2A},
      RType{"SLTU",0x00, 0x01, 0x02, 0x03, 0x00, 0x2B},
      RType{"SLL",0x00, 0x01, 0x02, 0x03, 0x00, 0x00},
      RType{"SRL",0x00, 0x01, 0x02, 0x03, 0x00, 0x02},
      RType{"SRA",0x00, 0x01, 0x02, 0x03, 0x00, 0x03},
      RType{"SUB",0x00, 0x01, 0x02, 0x03, 0x00, 0x22},
      RType{"SUBU",0x00, 0x01, 0x02, 0x03, 0x00, 0x23},
    };
    IType IInstructions[100] {
      IType{"SLTI",0x0A, 0x01, 0x02, 0x0000},
      IType{"SLTIU",0x0B, 0x01, 0x02, 0x0000},
      IType{"ORI",0x0D, 0x01, 0x02, 0x0000},
      IType{"SW",0x2B, 0x01, 0x02, 0x0000},
      IType{"BEQ",0x04, 0x01, 0x02, 0x0000},
      IType{"BNE",0x05, 0x01, 0x02, 0x0000},
      IType{"BLEZ",0x06, 0x01, 0x02, 0x0000},
      IType{"BGTZ",0x07, 0x01, 0x02, 0x0000},
      IType{"ADDI",0x08, 0x01, 0x02, 0x0000},
      IType{"ADDIU",0x09, 0x01, 0x02, 0x0000},
      IType{"LB",0x20, 0x01, 0x02, 0x0000},
      IType{"LW",0x23, 0x01, 0x02, 0x0000},
      IType{"LBU",0x24, 0x01, 0x02, 0x0000},
      IType{"LHU",0x25, 0x01, 0x02, 0x0000},
      IType{"SB",0x28, 0x01, 0x02, 0x0000},
      IType{"SH",0x29, 0x01, 0x02, 0x0000},
    };

    cout << "Testing R-Type Instructions" << endl;
    for(int i = 0; i < 21; i++){
      uint32_t instruction = 0;
      uint8_t opcode = RInstructions[i].opcode;
      uint8_t rs = RInstructions[i].rs;
      uint8_t rt = RInstructions[i].rt;
      uint8_t rd = RInstructions[i].rd;
      uint8_t shamt = RInstructions[i].shamt;
      uint8_t funct = RInstructions[i].funct;
      string name = RInstructions[i].name;
      instruction |= opcode << 26;
      instruction |= rs << 21;
      instruction |= rt << 16;
      instruction |= rd << 11;
      instruction |= shamt << 6;
      instruction |= funct;
      cout << "Testing " << RInstructions[i].name << endl;
      Cpu::Instruction* parsed_instruction = Cpu::parseRawInstruction(instruction);
      printf("Instruction: %s\n", name.c_str());
      printf("Opcode Expected: %x Got: %x\n", opcode, parsed_instruction->opcode);
      printf("rs Expected: %x Got: %x\n", rs, parsed_instruction->rs);
      printf("rt Expected: %x Got: %x\n", rt, parsed_instruction->rt);
      printf("rd Expected: %x Got: %x\n", rd, parsed_instruction->rd);
      printf("shamt Expected: %x Got: %x\n", shamt, parsed_instruction->shamt);
      printf("funct Expected: %x Got: %x\n", funct, parsed_instruction->funct);

      if(
          parsed_instruction->opcode == opcode 
          && parsed_instruction->rs == rs 
          && parsed_instruction->rt == rt 
          && parsed_instruction->rd == rd 
          && parsed_instruction->shamt == shamt 
          && parsed_instruction->funct == funct
      ){
        printf("Test Passed\n");
      } else {
        printf("Test Failed\n");
        final_status = false;
      }
    }
    cout << "Testing I-Type Instructions" << endl;
    for(int i = 0; i < 16; i++){
      uint32_t instruction = 0;
      uint8_t opcode = IInstructions[i].opcode;
      uint8_t rs = IInstructions[i].rs;
      uint8_t rt = IInstructions[i].rt;
      uint16_t immediate = IInstructions[i].immediate;
      string name = IInstructions[i].name;
      instruction |= opcode << 26;
      instruction |= rs << 21;
      instruction |= rt << 16;
      instruction |= immediate;
      cout << "Testing " << IInstructions[i].name << endl;
      Cpu::Instruction* parsed_instruction = Cpu::parseRawInstruction(instruction);
      printf("Instruction: %s\n", name.c_str());
      printf("Opcode Expected: %x Got: %x\n", opcode, parsed_instruction->opcode);
      printf("rs Expected: %x Got: %x\n", rs, parsed_instruction->rs);
      printf("rt Expected: %x Got: %x\n", rt, parsed_instruction->rt);
      printf("immediate Expected: %x Got: %x\n", immediate, parsed_instruction->imm);

      if(
          parsed_instruction->opcode == opcode 
          && parsed_instruction->rs == rs 
          && parsed_instruction->rt == rt 
          && parsed_instruction->imm == immediate
      ){
        printf("Test Passed\n");
      } else {
        printf("Test Failed\n");
        final_status = false;
      }
    }
    cout << "Testing J-Type Instructions" << endl;
    for(int i = 0; i < 2; i++){
      uint32_t instruction = 0;
      uint8_t opcode = JInstructions[i].opcode;
      uint32_t address = JInstructions[i].address;
      string name = JInstructions[i].name;
      instruction |= opcode << 26;
      instruction |= address;
      cout << "Testing " << JInstructions[i].name << endl;
      Cpu::Instruction* parsed_instruction = Cpu::parseRawInstruction(instruction);
      printf("Instruction: %s\n", name.c_str());
      printf("Opcode Expected: %x Got: %x\n", opcode, parsed_instruction->opcode);
      printf("address Expected: %x Got: %x\n", address, parsed_instruction->addr);

      if(
          parsed_instruction->opcode == opcode 
          && parsed_instruction->addr == address
      ){
        printf("Test Passed\n");
      } else {
        printf("Test Failed\n");
        final_status = false;
      }
    }

    cout << endl;
    if(final_status){
      cout << "All tests passed" << endl;
    } else {
      cout << "Some tests failed" << endl;
    }
    return final_status;
  }
}



