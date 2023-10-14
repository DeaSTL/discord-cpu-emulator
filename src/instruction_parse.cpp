#include "cpu.hpp"
#include <memory>


namespace Cpu {
  std::shared_ptr<instruction> parseRInstruction(uint32_t raw_instruction){
    uint8_t opcode = (raw_instruction >> OPCODE_OFF) & OPCODE_MASK;
    uint8_t rs = (raw_instruction >> R_TYPE_RS_OFF) & R_TYPE_RS_MASK;
    uint8_t rt = (raw_instruction >> R_TYPE_RT_OFF) & R_TYPE_RT_MASK;
    uint8_t rd = (raw_instruction >> R_TYPE_RD_OFF) & R_TYPE_RD_MASK;
    uint8_t shamt = (raw_instruction >> R_TYPE_SHAMT_OFF) & R_TYPE_SHAMT_MASK;
    uint8_t funct = (raw_instruction >> R_TYPE_FUNCT_OFF) & R_TYPE_FUNCT_MASK;
    instruction _current_instruction = {};

    _current_instruction.opcode = opcode;
    _current_instruction.rs = rs;
    _current_instruction.rt = rt;
    _current_instruction.rd = rd;
    _current_instruction.shamt = shamt;
    _current_instruction.funct = funct;
    _current_instruction.type = InstructionType::R;
    _current_instruction.raw_instruction = raw_instruction;
    _current_instruction.valid = true;

    std::shared_ptr<instruction> current_instruction = std::make_shared<instruction>(_current_instruction);
    switch(current_instruction->funct){
      case R_FUNCTION_ADD:
        current_instruction->id = INS_ADD;
        return current_instruction;
        break;
      case R_FUNCTION_ADDU:
        current_instruction->id = INS_ADDU;
        return current_instruction;
        break;
      case R_FUNCTION_AND:
        current_instruction->id = INS_AND; 
        return current_instruction;
        break;
      case R_FUNCTION_DIV:
        current_instruction->id = INS_DIV; 
        return current_instruction;
        break;
      case R_FUNCTION_DIVU:
        current_instruction->id = INS_DIVU; 
        return current_instruction;
        break;
      case R_FUNCTION_JALR:
        current_instruction->id = INS_JALR;
        return current_instruction;
        break;
      case R_FUNCTION_JR:
        current_instruction->id = INS_JR;
        return current_instruction;
        break;
      case R_FUNCTION_MFHI:
        current_instruction->id = INS_MFHI;
        return current_instruction;
        break;
      case R_FUNCTION_MFLO:
        current_instruction->id = INS_MFLO;
        return current_instruction;
        break;
      case R_FUNCTION_MTHI:
        current_instruction->id = INS_MTHI;
        return current_instruction;
        break;
      case R_FUNCTION_MTLO:
        current_instruction->id = INS_MTLO;
        return current_instruction;
        break;
      case R_FUNCTION_MULT:
        current_instruction->id = INS_MULT;
        return current_instruction;
        break;
      case R_FUNCTION_MULTU:
        current_instruction->id = INS_MULTU;
        return current_instruction;
        break;
      case R_FUNCTION_NOR:
        current_instruction->id = INS_NOR;
        return current_instruction;
        break;
      case R_FUNCTION_OR:
        current_instruction->id = INS_OR;
        return current_instruction;
        break;
      case R_FUNCTION_SLL:
        current_instruction->id = INS_SLL;
        return current_instruction;
        break;
      case R_FUNCTION_SLT:
        current_instruction->id = INS_SLT;
        return current_instruction;
        break;
      case R_FUNCTION_SLTU:
        current_instruction->id = INS_SLTU;
        return current_instruction;
        break;
      case R_FUNCTION_SRA:
        current_instruction->id = INS_SRA;
        return current_instruction;
        break;
      case R_FUNCTION_SRL:
        current_instruction->id = INS_SRL;
        return current_instruction;
        break;
      case R_FUNCTION_SUB:
        current_instruction->id = INS_SUB;
        return current_instruction;
        break;
      case R_FUNCTION_SUBU:
        current_instruction->id = INS_SUBU;
        return current_instruction;
        break;
    }
    current_instruction->valid = false;
    return current_instruction;
  }
  std::shared_ptr<instruction> parseJInstruction(uint32_t raw_instruction){
    uint8_t opcode = (raw_instruction >> OPCODE_OFF) & OPCODE_MASK;
    uint32_t addr = (raw_instruction >> J_TYPE_ADDR_OFF) & J_TYPE_ADDR_MASK;
    instruction _current_instruction = {};

    _current_instruction.opcode = opcode;
    _current_instruction.addr = addr;
    _current_instruction.type = InstructionType::J;
    _current_instruction.raw_instruction = raw_instruction;
    _current_instruction.valid = true;

    std::shared_ptr<instruction> current_instruction = std::make_shared<instruction>(_current_instruction);

    switch(current_instruction->opcode){
      case J_FUNCTION_J:
        current_instruction->id = INS_J;
        return current_instruction;
        break;
      case J_FUNCTION_JAL:
        current_instruction->id = INS_JAL;
        return current_instruction;
        break;
    }
    current_instruction->valid = false;
    return current_instruction;
  }
  std::shared_ptr<instruction> parseIInstruction(uint32_t raw_instruction){
    uint8_t opcode = (raw_instruction >> OPCODE_OFF) & OPCODE_MASK;
    uint8_t rs = (raw_instruction >> I_TYPE_RS_OFF) & I_TYPE_RS_MASK;
    uint8_t rt = (raw_instruction >> I_TYPE_RT_OFF) & I_TYPE_RT_MASK;
    uint16_t imm = (raw_instruction >> I_TYPE_IMM_OFF) & I_TYPE_IMM_MASK;
    instruction _current_instruction = {};

    _current_instruction.opcode = opcode;
    _current_instruction.rs = rs;
    _current_instruction.rt = rt;
    _current_instruction.imm = imm;
    _current_instruction.type = InstructionType::I;
    _current_instruction.raw_instruction = raw_instruction;
    _current_instruction.valid = true;

    std::shared_ptr<instruction> current_instruction = std::make_shared<instruction>(_current_instruction);
    switch(current_instruction->opcode){
      case I_FUNCTION_ADDI:
        current_instruction->id = INS_ADDI;
        return current_instruction;
        break;
      case I_FUNCTION_ADDIU:
        current_instruction->id = INS_ADDIU;
        return current_instruction;
        break;
      case I_FUNCTION_ANDI:
        current_instruction->id = INS_ANDI;
        return current_instruction;
        break;
      case I_FUNCTION_BEQ:
        current_instruction->id = INS_BEQ;
        return current_instruction;
        break;
      case I_FUNCTION_BGTZ:
        current_instruction->id = INS_BGTZ;
        return current_instruction;
        break;
      case I_FUNCTION_BLEZ:
        current_instruction->id = INS_BLEZ;
        return current_instruction;
        break;
      case I_FUNCTION_BNE:
        current_instruction->id = INS_BNE;
        return current_instruction;
        break;
      case I_FUNCTION_LB:
        current_instruction->id = INS_LB;
        return current_instruction;
        break;
      case I_FUNCTION_LBU:
        current_instruction->id = INS_LBU;
        return current_instruction;
        break;
      case I_FUNCTION_LHU:
        current_instruction->id = INS_LHU;
        return current_instruction;
        break;
      case I_FUNCTION_LUI:
        current_instruction->id = INS_LUI;
        return current_instruction;
        break;
      case I_FUNCTION_LW:
        current_instruction->id = INS_LW;
        return current_instruction;
        break;
      case I_FUNCTION_ORI:
        current_instruction->id = INS_ORI;
        return current_instruction;
        break;
      case I_FUNCTION_SB:
        current_instruction->id = INS_SB;
        return current_instruction;
        break;
      case I_FUNCTION_SH:
        current_instruction->id = INS_SH;
        return current_instruction;
        break;
      case I_FUNCTION_SLTI:
        current_instruction->id = INS_SLTI;
        return current_instruction;
        break;
      case I_FUNCTION_SLTIU:
        current_instruction->id = INS_SLTIU;
        return current_instruction;
        break;
      case I_FUNCTION_SW:
        current_instruction->id = INS_SW;
        return current_instruction;
        break;
    }
    current_instruction->valid = false;
    return current_instruction;
  }
  std::shared_ptr<instruction> parseRawInstruction(uint32_t raw_instruction){
    uint8_t opcode = raw_instruction >> 26;
    instruction _current_instruction = {};
    _current_instruction.opcode = opcode;
    _current_instruction.type = InstructionType::INVALID;
    _current_instruction.raw_instruction = raw_instruction;
    _current_instruction.valid = true;
    std::shared_ptr<instruction> current_instruction = std::make_shared<instruction>(_current_instruction);

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
        //J-Type instructions
      case 0x02:
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
