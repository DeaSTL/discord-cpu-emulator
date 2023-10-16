#include <memory>
#include "cpu_instructions.hpp" 
#include "cpu_constants.hpp"

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
        case  CpuConstants::R_FUNCTION_ADD:
          current_instruction->id =  CpuConstants::INS_ADD;
          return current_instruction;
          break;
        case  CpuConstants::R_FUNCTION_ADDU:
          current_instruction->id =  CpuConstants::INS_ADDU;
          return current_instruction;
          break;
        case  CpuConstants::R_FUNCTION_AND:
          current_instruction->id =  CpuConstants::INS_AND; 
          return current_instruction;
          break;
        case  CpuConstants::R_FUNCTION_DIV:
          current_instruction->id =  CpuConstants::INS_DIV; 
          return current_instruction;
          break;
        case  CpuConstants::R_FUNCTION_DIVU:
          current_instruction->id =  CpuConstants::INS_DIVU; 
          return current_instruction;
          break;
        case CpuConstants:: R_FUNCTION_JALR:
          current_instruction->id =  CpuConstants::INS_JALR;
          return current_instruction;
          break;
        case  CpuConstants::R_FUNCTION_JR:
          current_instruction->id =  CpuConstants::INS_JR;
          return current_instruction;
          break;
        case  CpuConstants::R_FUNCTION_MFHI:
          current_instruction->id =  CpuConstants::INS_MFHI;
          return current_instruction;
          break;
        case  CpuConstants::R_FUNCTION_MFLO:
          current_instruction->id =  CpuConstants::INS_MFLO;
          return current_instruction;
          break;
        case  CpuConstants::R_FUNCTION_MTHI:
          current_instruction->id =  CpuConstants::INS_MTHI;
          return current_instruction;
          break;
        case  CpuConstants::R_FUNCTION_MTLO:
          current_instruction->id =  CpuConstants::INS_MTLO;
          return current_instruction;
          break;
        case  CpuConstants::R_FUNCTION_MULT:
          current_instruction->id =  CpuConstants::INS_MULT;
          return current_instruction;
          break;
        case  CpuConstants::R_FUNCTION_MULTU:
          current_instruction->id =  CpuConstants::INS_MULTU;
          return current_instruction;
          break;
        case  CpuConstants::R_FUNCTION_NOR:
          current_instruction->id =  CpuConstants::INS_NOR;
          return current_instruction;
          break;
        case  CpuConstants::R_FUNCTION_OR:
          current_instruction->id =  CpuConstants::INS_OR;
          return current_instruction;
          break;
        case  CpuConstants::R_FUNCTION_SLL:
          current_instruction->id =  CpuConstants::INS_SLL;
          return current_instruction;
          break;
        case  CpuConstants::R_FUNCTION_SLT:
          current_instruction->id =  CpuConstants::INS_SLT;
          return current_instruction;
          break;
        case  CpuConstants::R_FUNCTION_SLTU:
          current_instruction->id =  CpuConstants::INS_SLTU;
          return current_instruction;
          break;
        case  CpuConstants::R_FUNCTION_SRA:
          current_instruction->id =  CpuConstants::INS_SRA;
          return current_instruction;
          break;
        case  CpuConstants::R_FUNCTION_SRL:
          current_instruction->id =  CpuConstants::INS_SRL;
          return current_instruction;
          break;
        case  CpuConstants::R_FUNCTION_SUB:
          current_instruction->id =  CpuConstants::INS_SUB;
          return current_instruction;
          break;
        case  CpuConstants::R_FUNCTION_SUBU:
          current_instruction->id =  CpuConstants::INS_SUBU;
          return current_instruction;
          break;
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
        case CpuConstants::I_FUNCTION_ADDI:
          current_instruction->id = CpuConstants::INS_ADDI;
          return current_instruction;
          break;
        case CpuConstants::I_FUNCTION_ADDIU:
          current_instruction->id = CpuConstants::INS_ADDIU;
          return current_instruction;
          break;
        case CpuConstants::I_FUNCTION_ANDI:
          current_instruction->id = CpuConstants::INS_ANDI;
          return current_instruction;
          break;
        case CpuConstants::I_FUNCTION_BEQ:
          current_instruction->id = CpuConstants::INS_BEQ;
          return current_instruction;
          break;
        case CpuConstants::I_FUNCTION_BGTZ:
          current_instruction->id = CpuConstants::INS_BGTZ;
          return current_instruction;
          break;
        case CpuConstants::I_FUNCTION_BLEZ:
          current_instruction->id = CpuConstants::INS_BLEZ;
          return current_instruction;
          break;
        case CpuConstants::I_FUNCTION_BNE:
          current_instruction->id = CpuConstants::INS_BNE;
          return current_instruction;
          break;
        case CpuConstants::I_FUNCTION_LB:
          current_instruction->id = CpuConstants::INS_LB;
          return current_instruction;
          break;
        case CpuConstants::I_FUNCTION_LBU:
          current_instruction->id = CpuConstants::INS_LBU;
          return current_instruction;
          break;
        case CpuConstants::I_FUNCTION_LHU:
          current_instruction->id = CpuConstants::INS_LHU;
          return current_instruction;
          break;
        case CpuConstants::I_FUNCTION_LUI:
          current_instruction->id = CpuConstants::INS_LUI;
          return current_instruction;
          break;
        case CpuConstants::I_FUNCTION_LW:
          current_instruction->id = CpuConstants::INS_LW;
          return current_instruction;
          break;
        case CpuConstants::I_FUNCTION_ORI:
          current_instruction->id = CpuConstants::INS_ORI;
          return current_instruction;
          break;
        case CpuConstants::I_FUNCTION_SB:
          current_instruction->id = CpuConstants::INS_SB;
          return current_instruction;
          break;
        case CpuConstants::I_FUNCTION_SH:
          current_instruction->id = CpuConstants::INS_SH;
          return current_instruction;
          break;
        case CpuConstants::I_FUNCTION_SLTI:
          current_instruction->id = CpuConstants::INS_SLTI;
          return current_instruction;
          break;
        case CpuConstants::I_FUNCTION_SLTIU:
          current_instruction->id = CpuConstants::INS_SLTIU;
          return current_instruction;
          break;
        case CpuConstants::I_FUNCTION_SW:
          current_instruction->id = CpuConstants::INS_SW;
          return current_instruction;
          break;
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
      }
      return current_instruction;
    }
  }
}
