
#include "stdint.h"
#include "../cpu_instructions.hpp"
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <iostream>
#include "stdio.h"
#include <memory>

namespace MipsEmulator{
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
    bool testIInstruction(IType instruction){
      std::cout << "Testing I Type Instruction: " << instruction.name << std::endl;
      bool final_status = true;
      uint32_t instruction_binary = 0;
      instruction_binary = instruction_binary | instruction.opcode;
      instruction_binary = instruction_binary << 5;
      instruction_binary = instruction_binary | instruction.rs;
      instruction_binary = instruction_binary << 5;
      instruction_binary = instruction_binary | instruction.rt;
      instruction_binary = instruction_binary << 16;
      instruction_binary = instruction_binary | instruction.immediate;
      std::shared_ptr<CpuInstructions::instruction> instruction_decoded = CpuInstructions::parseRawInstruction(instruction_binary);
      if(instruction.name != instruction_decoded->name){
        cout << "Error: Instruction name does not match" << endl;
        final_status = false;
      }
      if(instruction.opcode != instruction_decoded->opcode){
        cout << "Error: Instruction opcode does not match" << endl;
        final_status = false;
      }
      if(instruction.rs != instruction_decoded->rs){
        cout << "Error: Instruction rs does not match" << endl;
        final_status = false;
      }
      if(instruction.rt != instruction_decoded->rt){
        cout << "Error: Instruction rt does not match" << endl;
        final_status = false;
      }
      if(instruction.immediate != instruction_decoded->imm){
        cout << "Error: Instruction immediate does not match" << endl;
        final_status = false;
      }
      return final_status;
    }
    bool testJInstruction(JType instruction){
      std::cout << "Testing J Instruction" << std::endl;
      bool final_status = true;
      uint32_t instruction_binary = 0;
      instruction_binary = instruction_binary | instruction.opcode;
      instruction_binary = instruction_binary << 26;
      instruction_binary = instruction_binary | instruction.address;
      std::shared_ptr<CpuInstructions::instruction> instruction_decoded = CpuInstructions::parseRawInstruction(instruction_binary);
      if(instruction.name != instruction_decoded->name){
        cout << "Error: Instruction name does not match" << endl;
        final_status = false;
      }
      if(instruction.opcode != instruction_decoded->opcode){
        cout << "Error: Instruction opcode does not match" << endl;
        final_status = false;
      }
      if(instruction.address != instruction_decoded->addr){
        cout << "Error: Instruction address does not match" << endl;
        final_status = false;
      }
      return final_status;
    }

    bool testRInstruction(RType instruction){
      std::cout << "Testing R Instruction" << std::endl;
      bool final_status = true;
      uint32_t instruction_binary = 0;
      instruction_binary = instruction_binary | instruction.opcode;
      instruction_binary = instruction_binary << 5;
      instruction_binary = instruction_binary | instruction.rs;
      instruction_binary = instruction_binary << 5;
      instruction_binary = instruction_binary | instruction.rt;
      instruction_binary = instruction_binary << 5;
      instruction_binary = instruction_binary | instruction.rd;
      instruction_binary = instruction_binary << 5;
      instruction_binary = instruction_binary | instruction.shamt;
      instruction_binary = instruction_binary << 6;
      instruction_binary = instruction_binary | instruction.funct;
      std::shared_ptr<CpuInstructions::instruction> instruction_decoded = CpuInstructions::parseRawInstruction(instruction_binary);
      if(instruction.name != instruction_decoded->name){
        cout << "Error: Instruction name does not match" << endl;
        final_status = false;
      }
      if(instruction.opcode != instruction_decoded->opcode){
        cout << "Error: Instruction opcode does not match" << endl;
        final_status = false;
      }
      if(instruction.rs != instruction_decoded->rs){
        cout << "Error: Instruction rs does not match" << endl;
        final_status = false;
      }
      if(instruction.rt != instruction_decoded->rt){
        cout << "Error: Instruction rt does not match" << endl;
        final_status = false;
      }
      if(instruction.rd != instruction_decoded->rd){
        cout << "Error: Instruction rd does not match" << endl;
        final_status = false;
      }
      if(instruction.shamt != instruction_decoded->shamt){
        cout << "Error: Instruction shamt does not match" << endl;
        final_status = false;
      }
      if(instruction.funct != instruction_decoded->funct){
        cout << "Error: Instruction funct does not match" << endl;
        final_status = false;
      }
      return final_status;
    }

    TEST_CASE("I Type Instruction decode", "[instruction decode]"){
      REQUIRE(testIInstruction(IType{"SLTI",0x0A, 0x01, 0x02, 0x0000}));
      REQUIRE(testIInstruction(IType{"SLTIU",0x0B, 0x01, 0x02, 0x0000}));
      REQUIRE(testIInstruction(IType{"ADDI",0x08, 0x01, 0x02, 0x0000}));
      REQUIRE(testIInstruction(IType{"ADDIU",0x09, 0x01, 0x02, 0x0000}));
      REQUIRE(testIInstruction(IType{"ANDI",0x0C, 0x01, 0x02, 0x0000}));
      REQUIRE(testIInstruction(IType{"ORI",0x0D, 0x01, 0x02, 0x0000}));
      REQUIRE(testIInstruction(IType{"XORI",0x0E, 0x01, 0x02, 0x0000}));
      REQUIRE(testIInstruction(IType{"LUI",0x0F, 0x00, 0x01, 0x0000}));
      REQUIRE(testIInstruction(IType{"LB",0x20, 0x01, 0x02, 0x0000}));
      REQUIRE(testIInstruction(IType{"LH",0x21, 0x01, 0x02, 0x0000}));
      REQUIRE(testIInstruction(IType{"LW",0x23, 0x01, 0x02, 0x0000}));
      REQUIRE(testIInstruction(IType{"LBU",0x24, 0x01, 0x02, 0x0000}));
      REQUIRE(testIInstruction(IType{"LHU",0x25, 0x01, 0x02, 0x0000}));
      REQUIRE(testIInstruction(IType{"SB",0x28, 0x01, 0x02, 0x0000}));
      REQUIRE(testIInstruction(IType{"SH",0x29, 0x01, 0x02, 0x0000}));
      REQUIRE(testIInstruction(IType{"SW",0x2B, 0x01, 0x02, 0x0000}));
    }

    TEST_CASE("J Type Instruction decode", "[instruction decode]"){
      REQUIRE(testJInstruction(JType{"J",0x02, 0x00000000}));
      REQUIRE(testJInstruction(JType{"JAL",0x03, 0x00000000}));
    }

    TEST_CASE("R Type Instruction decode", "[instruction decode]"){
      REQUIRE(testRInstruction(RType{"ADD",0x00, 0x01, 0x02, 0x03, 0x00, 0x20}));
      REQUIRE(testRInstruction(RType{"ADDU",0x00, 0x01, 0x02, 0x03, 0x00, 0x21}));
      REQUIRE(testRInstruction(RType{"AND",0x00, 0x01, 0x02, 0x03, 0x00, 0x24}));
      REQUIRE(testRInstruction(RType{"DIV",0x00, 0x01, 0x02, 0x03, 0x00, 0x1A}));
      REQUIRE(testRInstruction(RType{"DIVU",0x00, 0x01, 0x02, 0x03, 0x00, 0x1B}));
      REQUIRE(testRInstruction(RType{"JR",0x00, 0x01, 0x00, 0x00, 0x00, 0x08}));
      REQUIRE(testRInstruction(RType{"MFHI",0x00, 0x00, 0x00, 0x00, 0x00, 0x10}));
      REQUIRE(testRInstruction(RType{"MFLO",0x00, 0x00, 0x00, 0x00, 0x00, 0x12}));
      REQUIRE(testRInstruction(RType{"MTHI",0x00, 0x00, 0x00, 0x00, 0x00, 0x11}));
      REQUIRE(testRInstruction(RType{"MTLO",0x00, 0x00, 0x00, 0x00, 0x00, 0x13}));
      REQUIRE(testRInstruction(RType{"MULT",0x00, 0x01, 0x02, 0x00, 0x00, 0x18}));
      REQUIRE(testRInstruction(RType{"MULTU",0x00, 0x01, 0x02, 0x00, 0x00, 0x19}));
      REQUIRE(testRInstruction(RType{"OR",0x00, 0x01, 0x02, 0x03, 0x00, 0x25}));
      REQUIRE(testRInstruction(RType{"SLL",0x00, 0x00, 0x02, 0x03, 0x04, 0x00}));
      REQUIRE(testRInstruction(RType{"SLLV",0x00, 0x01, 0x02, 0x00, 0x00, 0x04}));
      REQUIRE(testRInstruction(RType{"SLT",0x00, 0x01, 0x02, 0x03, 0x00, 0x2A}));
      REQUIRE(testRInstruction(RType{"SLTU",0x00, 0x01, 0x02, 0x03, 0x00, 0x2B}));
      REQUIRE(testRInstruction(RType{"SRA",0x00, 0x00, 0x02, 0x03, 0x04, 0x03}));
      REQUIRE(testRInstruction(RType{"SRAV",0x00, 0x01, 0x02, 0x00, 0x00, 0x07}));
      REQUIRE(testRInstruction(RType{"SRL",0x00, 0x00, 0x02, 0x03, 0x04, 0x02}));
      REQUIRE(testRInstruction(RType{"SRLV",0x00, 0x01, 0x02, 0x00, 0x00, 0x06}));
      REQUIRE(testRInstruction(RType{"SUB",0x00, 0x01, 0x02, 0x03, 0x00, 0x22}));
      REQUIRE(testRInstruction(RType{"SUBU",0x00, 0x01, 0x02, 0x03, 0x00, 0x23}));
      REQUIRE(testRInstruction(RType{"SYSCALL",0x00, 0x00, 0x00, 0x00, 0x00, 0x0C}));
      REQUIRE(testRInstruction(RType{"XOR",0x00, 0x01, 0x02, 0x03, 0x00, 0x26}));
    }

  }
}
