#include <memory>
#include "cpu_instructions.hpp" 
#include "cpu_constants.hpp"

#define FUNCTION_CASE(type,function) case CpuConstants::type##_FUNCTION_##function: current_instruction->id = CpuConstants::INS_##function; return current_instruction; break;

namespace MipsEmulator{
  namespace CpuInstructions{ 
    std::shared_ptr<CpuInstructions::instruction> parseRInstruction(uint32_t raw_instruction){
      uint8_t opcode = (raw_instruction >> CpuConstants::OPCODE_OFF) &  CpuConstants::OPCODE_MASK;
      uint8_t rs = (raw_instruction >>  CpuConstants::R_TYPE_RS_OFF) &  CpuConstants::R_TYPE_RS_MASK; 
      uint8_t rt = (raw_instruction >>  CpuConstants::R_TYPE_RT_OFF) &  CpuConstants::R_TYPE_RT_MASK;
      uint8_t rd = (raw_instruction >>  CpuConstants::R_TYPE_RD_OFF) &  CpuConstants::R_TYPE_RD_MASK;
      uint8_t shamt = (raw_instruction >>  CpuConstants::R_TYPE_SHAMT_OFF) &  CpuConstants::R_TYPE_SHAMT_MASK;
      uint8_t funct = (raw_instruction >>  CpuConstants::R_TYPE_FUNCT_OFF) &  CpuConstants::R_TYPE_FUNCT_MASK;
      CpuInstructions::instruction _current_instruction = {};

      _current_instruction.opcode = opcode;
      _current_instruction.rs = rs;
      _current_instruction.rt = rt;
      _current_instruction.rd = rd;
      _current_instruction.shamt = shamt;
      _current_instruction.funct = funct;
      _current_instruction.type = CpuInstructions::InstructionType::R;
      _current_instruction.raw_instruction = raw_instruction;
      _current_instruction.valid = true;

      std::shared_ptr<CpuInstructions::instruction> current_instruction = std::make_shared<CpuInstructions::instruction>(_current_instruction);
      switch(current_instruction->funct){
        FUNCTION_CASE(R,ADD);
        FUNCTION_CASE(R,ADDU);
        FUNCTION_CASE(R,AND);
        FUNCTION_CASE(R,DIV);
        FUNCTION_CASE(R,DIVU);
        FUNCTION_CASE(R,JALR);
        FUNCTION_CASE(R,JR);
        FUNCTION_CASE(R,MFHI);
        FUNCTION_CASE(R,MFLO);
        FUNCTION_CASE(R,MTHI);
        FUNCTION_CASE(R,MTLO);
        FUNCTION_CASE(R,MULT);
        FUNCTION_CASE(R,MULTU);
        FUNCTION_CASE(R,NOR);
        FUNCTION_CASE(R,OR);
        FUNCTION_CASE(R,SLL);
        FUNCTION_CASE(R,SLLV);
        FUNCTION_CASE(R,SLT);
        FUNCTION_CASE(R,SLTU);
        FUNCTION_CASE(R,SRA);
        FUNCTION_CASE(R,SRAV);
        FUNCTION_CASE(R,SRL);
        FUNCTION_CASE(R,SRLV);
        FUNCTION_CASE(R,SUB);
        FUNCTION_CASE(R,SUBU);
        FUNCTION_CASE(R,SYSCALL);
        FUNCTION_CASE(R,XOR);
        FUNCTION_CASE(R,BREAK);
      }
      current_instruction->valid = false;
      return current_instruction;
    }
    std::shared_ptr<CpuInstructions::instruction> parseJInstruction(uint32_t raw_instruction){
      uint8_t opcode = (raw_instruction >> CpuConstants::OPCODE_OFF) & CpuConstants::OPCODE_MASK;
      uint32_t addr = (raw_instruction >> CpuConstants::J_TYPE_ADDR_OFF) & CpuConstants::J_TYPE_ADDR_MASK;
      CpuInstructions::instruction _current_instruction = {};

      _current_instruction.opcode = opcode;
      _current_instruction.addr = addr;
      _current_instruction.type = CpuInstructions::InstructionType::J;
      _current_instruction.raw_instruction = raw_instruction;
      _current_instruction.valid = true;

      std::shared_ptr<CpuInstructions::instruction> current_instruction = std::make_shared<CpuInstructions::instruction>(_current_instruction);

      switch(current_instruction->opcode){
        case CpuConstants::J_FUNCTION_J:
          current_instruction->id = CpuConstants::INS_J;
          return current_instruction;
          break;
        case CpuConstants::J_FUNCTION_JAL:
          current_instruction->id = CpuConstants::INS_JAL;
          return current_instruction;
          break;
      }
      current_instruction->valid = false;
      return current_instruction;
    }
    std::shared_ptr<CpuInstructions::instruction> parseIInstruction(uint32_t raw_instruction){
      uint8_t opcode = (raw_instruction >> CpuConstants::OPCODE_OFF) & CpuConstants::OPCODE_MASK;
      uint8_t rs = (raw_instruction >> CpuConstants::I_TYPE_RS_OFF) & CpuConstants::I_TYPE_RS_MASK;
      uint8_t rt = (raw_instruction >> CpuConstants::I_TYPE_RT_OFF) & CpuConstants::I_TYPE_RT_MASK;
      uint16_t imm = (raw_instruction >> CpuConstants::I_TYPE_IMM_OFF) & CpuConstants::I_TYPE_IMM_MASK;
      CpuInstructions::instruction _current_instruction = {};

      _current_instruction.opcode = opcode;
      _current_instruction.rs = rs;
      _current_instruction.rt = rt;
      _current_instruction.imm = imm;
      _current_instruction.type = CpuInstructions::InstructionType::I;
      _current_instruction.raw_instruction = raw_instruction;
      _current_instruction.valid = true;

      std::shared_ptr<CpuInstructions::instruction> current_instruction = std::make_shared<CpuInstructions::instruction>(_current_instruction);
      switch(current_instruction->opcode){
        FUNCTION_CASE(I,ADDI);
        FUNCTION_CASE(I,ADDIU);
        FUNCTION_CASE(I,ANDI);
        FUNCTION_CASE(I,BEQ);
        FUNCTION_CASE(I,BGTZ);
        FUNCTION_CASE(I,BLEZ);
        FUNCTION_CASE(I,BNE);
        FUNCTION_CASE(I,LBU);
        FUNCTION_CASE(I,LHU);
        FUNCTION_CASE(I,LL);
        FUNCTION_CASE(I,LUI);
        FUNCTION_CASE(I,LW);
        FUNCTION_CASE(I,LWL);
        FUNCTION_CASE(I,LWR);
        FUNCTION_CASE(I,ORI);
        FUNCTION_CASE(I,SB);
        FUNCTION_CASE(I,SC);
        FUNCTION_CASE(I,SH);
        FUNCTION_CASE(I,SLTI);
        FUNCTION_CASE(I,SLTIU);
        FUNCTION_CASE(I,SW);
        FUNCTION_CASE(I,XORI);
      }
      current_instruction->valid = false;
      return current_instruction;
    }
    std::shared_ptr<CpuInstructions::instruction> parseRawInstruction(uint32_t raw_instruction){
      uint8_t opcode = raw_instruction >> 26;
      CpuInstructions::instruction _current_instruction = {};
      _current_instruction.opcode = opcode;
      _current_instruction.type = CpuInstructions::InstructionType::INVALID;
      _current_instruction.raw_instruction = raw_instruction;
      _current_instruction.valid = true;
      std::shared_ptr<CpuInstructions::instruction> current_instruction = std::make_shared<CpuInstructions::instruction>(_current_instruction);

      switch(opcode){
        //R-Type instructions
        case 0x00:
          return parseRInstruction(raw_instruction);
          break;
        case 0x10:
          return parseRInstruction(raw_instruction);
          break;
        case 0x11:
          return parseRInstruction(raw_instruction);
          break;
        case 0x12:
          return parseRInstruction(raw_instruction);
          break;
          //J-Type instructions case 0x02:
          return parseJInstruction(raw_instruction);
          break;
        case 0x03:
          return parseJInstruction(raw_instruction);
          break;
          //I-Type instructions
        case 0x04:
          return parseIInstruction(raw_instruction);
          break;
        case 0x05:
          return parseIInstruction(raw_instruction);
          break;
        case 0x06:
          return parseIInstruction(raw_instruction);
          break;
        case 0x07:
          return parseIInstruction(raw_instruction);
          break;
        case 0x08:
          return parseIInstruction(raw_instruction);
          break;
        case 0x09:
          return parseIInstruction(raw_instruction);
          break;
        case 0x0A:
          return parseIInstruction(raw_instruction);
          break;
        case 0x0B:
          return parseIInstruction(raw_instruction);
          break;
        case 0x0C:
          return parseIInstruction(raw_instruction);
          break;
        case 0x0D:
          return parseIInstruction(raw_instruction);
          break;
        case 0x0F:
          return parseIInstruction(raw_instruction);
          break;
        case 0x20:
          return parseIInstruction(raw_instruction);
          break;
        case 0x21:
          return parseIInstruction(raw_instruction);
          break;
        case 0x23:
          return parseIInstruction(raw_instruction);
          break;
        case 0x24:
          return parseIInstruction(raw_instruction);
          break;
        case 0x25:
          return parseIInstruction(raw_instruction);
          break;
        case 0x28:
          return parseIInstruction(raw_instruction);
          break;
        case 0x29:
          return parseIInstruction(raw_instruction);
          break;
        case 0x2B:
          return parseIInstruction(raw_instruction);
          break;
        case 0x0E:
          return parseIInstruction(raw_instruction);
          break;
      }
      return current_instruction;
    }
  }
}
