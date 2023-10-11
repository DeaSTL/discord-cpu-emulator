#include "cpu.hpp"


namespace Cpu {
  Instruction* parseRInstruction(uint32_t raw_instruction){
    uint8_t opcode = (raw_instruction >> OPCODE_OFF) & OPCODE_MASK;
    uint8_t rs = (raw_instruction >> R_TYPE_RS_OFF) & R_TYPE_RS_MASK;
    uint8_t rt = (raw_instruction >> R_TYPE_RT_OFF) & R_TYPE_RT_MASK;
    uint8_t rd = (raw_instruction >> R_TYPE_RD_OFF) & R_TYPE_RD_MASK;
    uint8_t shamt = (raw_instruction >> R_TYPE_SHAMT_OFF) & R_TYPE_SHAMT_MASK;
    uint8_t funct = (raw_instruction >> R_TYPE_FUNCT_OFF) & R_TYPE_FUNCT_MASK;
    Instruction* instruction = new Instruction();
    instruction->opcode = opcode;
    instruction->rs = rs;
    instruction->rt = rt;
    instruction->rd = rd;
    instruction->shamt = shamt;
    instruction->funct = funct;
    instruction->type = instructionTypes::R;
    instruction->fetch_raw = raw_instruction;
    instruction->valid = true;
    switch(instruction->funct){
      case R_FUNCTION_ADD:
        instruction->id = INS_ADD;
        return instruction;
        break;
      case R_FUNCTION_ADDU:
        instruction->id = INS_ADDU;
        return instruction;
        break;
      case R_FUNCTION_AND:
        instruction->id = INS_AND; 
        return instruction;
        break;
      case R_FUNCTION_DIV:
        instruction->id = INS_DIV; 
        return instruction;
        break;
      case R_FUNCTION_DIVU:
        instruction->id = INS_DIVU; 
        return instruction;
        break;
      case R_FUNCTION_JALR:
        instruction->id = INS_JALR;
        return instruction;
        break;
      case R_FUNCTION_JR:
        instruction->id = INS_JR;
        return instruction;
        break;
      case R_FUNCTION_MFHI:
        instruction->id = INS_MFHI;
        return instruction;
        break;
      case R_FUNCTION_MFLO:
        instruction->id = INS_MFLO;
        return instruction;
        break;
      case R_FUNCTION_MTHI:
        instruction->id = INS_MTHI;
        return instruction;
        break;
      case R_FUNCTION_MTLO:
        instruction->id = INS_MTLO;
        return instruction;
        break;
      case R_FUNCTION_MULT:
        instruction->id = INS_MULT;
        return instruction;
        break;
      case R_FUNCTION_MULTU:
        instruction->id = INS_MULTU;
        return instruction;
        break;
      case R_FUNCTION_NOR:
        instruction->id = INS_NOR;
        return instruction;
        break;
      case R_FUNCTION_OR:
        instruction->id = INS_OR;
        return instruction;
        break;
      case R_FUNCTION_SLL:
        instruction->id = INS_SLL;
        return instruction;
        break;
      case R_FUNCTION_SLT:
        instruction->id = INS_SLT;
        return instruction;
        break;
      case R_FUNCTION_SLTU:
        instruction->id = INS_SLTU;
        return instruction;
        break;
      case R_FUNCTION_SRA:
        instruction->id = INS_SRA;
        return instruction;
        break;
      case R_FUNCTION_SRL:
        instruction->id = INS_SRL;
        return instruction;
        break;
      case R_FUNCTION_SUB:
        instruction->id = INS_SUB;
        return instruction;
        break;
      case R_FUNCTION_SUBU:
        instruction->id = INS_SUBU;
        return instruction;
        break;
    }
    instruction->valid = false;
    return instruction;
  }
  Instruction* parseJInstruction(uint32_t raw_instruction){
    uint8_t opcode = (raw_instruction >> OPCODE_OFF) & OPCODE_MASK;
    uint32_t addr = (raw_instruction >> J_TYPE_ADDR_OFF) & J_TYPE_ADDR_MASK;
    Instruction* instruction = new Instruction();

    instruction->opcode = opcode;
    instruction->addr = addr;
    instruction->type = instructionTypes::J;
    instruction->fetch_raw = raw_instruction;
    instruction->valid = true;
    switch(instruction->opcode){
      case J_FUNCTION_J:
        instruction->id = INS_J;
        return instruction;
        break;
      case J_FUNCTION_JAL:
        instruction->id = INS_JAL;
        return instruction;
        break;
    }
    instruction->valid = false;
    return instruction;
  }
  Instruction* parseIInstruction(uint32_t raw_instruction){
    uint8_t opcode = (raw_instruction >> OPCODE_OFF) & OPCODE_MASK;
    uint8_t rs = (raw_instruction >> I_TYPE_RS_OFF) & I_TYPE_RS_MASK;
    uint8_t rt = (raw_instruction >> I_TYPE_RT_OFF) & I_TYPE_RT_MASK;
    uint16_t imm = (raw_instruction >> I_TYPE_IMM_OFF) & I_TYPE_IMM_MASK;
    Instruction* instruction = new Instruction();
    instruction->opcode = opcode;
    instruction->rs = rs;
    instruction->rt = rt;
    instruction->imm = imm;
    instruction->type = instructionTypes::I;
    instruction->fetch_raw = raw_instruction;
    instruction->valid = true;
    switch(instruction->opcode){
      case I_FUNCTION_ADDI:
        instruction->id = INS_ADDI;
        return instruction;
        break;
      case I_FUNCTION_ADDIU:
        instruction->id = INS_ADDIU;
        return instruction;
        break;
      case I_FUNCTION_ANDI:
        instruction->id = INS_ANDI;
        return instruction;
        break;
      case I_FUNCTION_BEQ:
        instruction->id = INS_BEQ;
        return instruction;
        break;
      case I_FUNCTION_BGTZ:
        instruction->id = INS_BGTZ;
        return instruction;
        break;
      case I_FUNCTION_BLEZ:
        instruction->id = INS_BLEZ;
        return instruction;
        break;
      case I_FUNCTION_BNE:
        instruction->id = INS_BNE;
        return instruction;
        break;
      case I_FUNCTION_LB:
        instruction->id = INS_LB;
        return instruction;
        break;
      case I_FUNCTION_LBU:
        instruction->id = INS_LBU;
        return instruction;
        break;
      case I_FUNCTION_LHU:
        instruction->id = INS_LHU;
        return instruction;
        break;
      case I_FUNCTION_LUI:
        instruction->id = INS_LUI;
        return instruction;
        break;
      case I_FUNCTION_LW:
        instruction->id = INS_LW;
        return instruction;
        break;
      case I_FUNCTION_ORI:
        instruction->id = INS_ORI;
        return instruction;
        break;
      case I_FUNCTION_SB:
        instruction->id = INS_SB;
        return instruction;
        break;
      case I_FUNCTION_SH:
        instruction->id = INS_SH;
        return instruction;
        break;
      case I_FUNCTION_SLTI:
        instruction->id = INS_SLTI;
        return instruction;
        break;
      case I_FUNCTION_SLTIU:
        instruction->id = INS_SLTIU;
        return instruction;
        break;
      case I_FUNCTION_SW:
        instruction->id = INS_SW;
        return instruction;
        break;
    }
    instruction->valid = false;
    return instruction;
  }
  Instruction* parseRawInstruction(uint32_t raw_instruction){
    uint8_t opcode = raw_instruction >> 26;

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
        break;
    }
    return new Instruction();
  }
}