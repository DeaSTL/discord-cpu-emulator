#include "cpu.hpp"
#include <iostream>



namespace Cpu {
  using std::cout;
  using std::endl;
  using std::string;

  Instruction::Instruction(){
  };
  Instruction::Instruction(uint8_t opcode, int8_t funct, instructionTypes type, int id){
    this->opcode = opcode;
    this->funct = funct;
    this->type = type;
    this->id = id;
  };
  void Instruction::print(){
    cout << "Instruction: " << this->id << endl;
    cout << "Type: " << this->type << endl;
    cout << "Opcode: " << this->opcode << endl;
    cout << "Funct: " << this->funct << endl;
    cout << "RS: " << this->rs << endl;
    cout << "RT: " << this->rt << endl;
    cout << "RD: " << this->rd << endl;
    cout << "Shamt: " << this->shamt << endl;
    cout << "Imm: " << this->imm << endl;
    cout << "Addr: " << this->addr << endl;
    cout << "Fmt: " << this->fmt << endl;
    cout << "FT: " << this->ft << endl;
    cout << "FS: " << this->fs << endl;
    cout << "FD: " << this->fd << endl;


  };
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
    switch(instruction->funct){
      case R_FUNCTION_ADD:
        instruction->id = INS_ADD;
        break;
      case R_FUNCTION_ADDU:
        instruction->id = INS_ADDU;
        break;
      case R_FUNCTION_AND:
        instruction->id = INS_AND; 
        break;
      case R_FUNCTION_DIV:
        instruction->id = INS_DIV; 
        break;
      case R_FUNCTION_DIVU:
        instruction->id = INS_DIVU; 
        break;
      case R_FUNCTION_JALR:
        instruction->id = INS_JALR;
        break;
      case R_FUNCTION_JR:
        instruction->id = INS_JR;
        break;
      case R_FUNCTION_MFHI:
        instruction->id = INS_MFHI;
        break;
      case R_FUNCTION_MFLO:
        instruction->id = INS_MFLO;
        break;
      case R_FUNCTION_MTHI:
        instruction->id = INS_MTHI;
        break;
      case R_FUNCTION_MTLO:
        instruction->id = INS_MTLO;
        break;
      case R_FUNCTION_MULT:
        instruction->id = INS_MULT;
        break;
      case R_FUNCTION_MULTU:
        instruction->id = INS_MULTU;
        break;
      case R_FUNCTION_NOR:
        instruction->id = INS_NOR;
        break;
      case R_FUNCTION_OR:
        instruction->id = INS_OR;
        break;
      case R_FUNCTION_SLL:
        instruction->id = INS_SLL;
        break;
      case R_FUNCTION_SLT:
        instruction->id = INS_SLT;
        break;
      case R_FUNCTION_SLTU:
        instruction->id = INS_SLTU;
        break;
      case R_FUNCTION_SRA:
        instruction->id = INS_SRA;
        break;
      case R_FUNCTION_SRL:
        instruction->id = INS_SRL;
        break;
      case R_FUNCTION_SUB:
        instruction->id = INS_SUB;
        break;
      case R_FUNCTION_SUBU:
        instruction->id = INS_SUBU;
        break;
    }
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
    switch(instruction->opcode){
      case J_FUNCTION_J:
        instruction->id = INS_J;
        break;
      case J_FUNCTION_JAL:
        instruction->id = INS_JAL;
        break;
    }
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
    switch(instruction->opcode){
      case I_FUNCTION_ADDI:
        instruction->id = INS_ADDI;
        break;
      case I_FUNCTION_ADDIU:
        instruction->id = INS_ADDIU;
        break;
      case I_FUNCTION_ANDI:
        instruction->id = INS_ANDI;
        break;
      case I_FUNCTION_BEQ:
        instruction->id = INS_BEQ;
        break;
      case I_FUNCTION_BGTZ:
        instruction->id = INS_BGTZ;
        break;
      case I_FUNCTION_BLEZ:
        instruction->id = INS_BLEZ;
        break;
      case I_FUNCTION_BNE:
        instruction->id = INS_BNE;
        break;
      case I_FUNCTION_LB:
        instruction->id = INS_LB;
        break;
      case I_FUNCTION_LBU:
        instruction->id = INS_LBU;
        break;
      case I_FUNCTION_LHU:
        instruction->id = INS_LHU;
        break;
      case I_FUNCTION_LUI:
        instruction->id = INS_LUI;
        break;
      case I_FUNCTION_LW:
        instruction->id = INS_LW;
        break;
      case I_FUNCTION_ORI:
        instruction->id = INS_ORI;
        break;
      case I_FUNCTION_SB:
        instruction->id = INS_SB;
        break;
      case I_FUNCTION_SH:
        instruction->id = INS_SH;
        break;
      case I_FUNCTION_SLTI:
        instruction->id = INS_SLTI;
        break;
      case I_FUNCTION_SLTIU:
        instruction->id = INS_SLTIU;
        break;
      case I_FUNCTION_SW:
        instruction->id = INS_SW;
        break;
      }
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
  namespace instructions {
    Instruction ADD(  0x00 , 0x20 ,instructionTypes::R,INS_ADD);
    Instruction ADDI( 0x08 , -1   ,instructionTypes::I,INS_ADDI);
    Instruction ADDIU(0x09 , -1   ,instructionTypes::I,INS_ADDIU);
    Instruction ADDU( 0x00 , 0x21 ,instructionTypes::R,INS_ADDU);
    Instruction AND(  0x00 , 0x24 ,instructionTypes::R,INS_AND);
    Instruction ANDI( 0x0C , -1   ,instructionTypes::I,INS_ANDI);
    Instruction BEQ(  0x04 , -1   ,instructionTypes::I,INS_BEQ);
    Instruction BLEZ( 0x06 , -1   ,instructionTypes::I,INS_BLEZ);
    Instruction BNE(  0x05 , -1   ,instructionTypes::I,INS_BNE);
    Instruction BGTZ( 0x07 , -1   ,instructionTypes::I,INS_BGTZ);
    Instruction DIV(  0x00 , 0x1A , instructionTypes::R,INS_DIV);
    Instruction DIVU( 0x00 , 0x1B , instructionTypes::R,INS_DIVU);
    Instruction J(    0x02 , -1   ,instructionTypes::J,INS_J);
    Instruction JAL(  0x03 , -1   ,instructionTypes::J,INS_JAL);
    Instruction JALR( 0x00 , 0x09 , instructionTypes::R,INS_JALR);
    Instruction JR(   0x00 , 0x08 , instructionTypes::R,INS_JR);
    Instruction LB(   0x20 , -1   ,instructionTypes::I,INS_LB);
    Instruction LBU(  0x24 , -1   ,instructionTypes::I,INS_LBU);
    Instruction LHU(  0x25 , -1   ,instructionTypes::I,INS_LHU);
    Instruction LUI(  0x0F , -1   ,instructionTypes::I,INS_LUI);
    Instruction LW(   0x23 , -1   ,instructionTypes::I,INS_LW);
    Instruction MFHI( 0x00 , 0x10 , instructionTypes::R,INS_MFHI);
    Instruction MTHI( 0x00 , 0x11 , instructionTypes::R,INS_MTHI);
    Instruction MFLO( 0x00 , 0x12 , instructionTypes::R,INS_MFLO);
    Instruction MTLO( 0x00 , 0x13 , instructionTypes::R,INS_MTLO);
    Instruction MULT( 0x00 , 0x18 , instructionTypes::R,INS_MULT);
    Instruction MULTU(0x00 , 0x19 , instructionTypes::R,INS_MULTU);
    Instruction NOR(  0x00 , 0x27 , instructionTypes::R,INS_NOR);
    Instruction XOR(  0x00 , 0x26 , instructionTypes::R,INS_XOR);
    Instruction OR(   0x00 , 0x25 , instructionTypes::R,INS_OR);
    Instruction ORI(  0x0D , -1   ,instructionTypes::I,INS_ORI);
    Instruction SB(   0x28 , -1   ,instructionTypes::I,INS_SB);
    Instruction SH(   0x29 , -1   ,instructionTypes::I,INS_SH);
    Instruction SLT(  0x00 , 0x2A , instructionTypes::R,INS_SLT);
    Instruction SLTI( 0x0A , -1   ,instructionTypes::I,INS_SLTI);
    Instruction SLTIU(0x0B , -1   ,instructionTypes::I,INS_SLTIU);
    Instruction SLTU( 0x00 , 0x2B , instructionTypes::R,INS_SLTU);
    Instruction SLL(  0x00 , 0x00 , instructionTypes::R,INS_SLL);
    Instruction SRL(  0x00 , 0x02 , instructionTypes::R,INS_SRL);
    Instruction SRA(  0x00 , 0x03 , instructionTypes::R,INS_SRA);
    Instruction SUB(  0x00 , 0x22 , instructionTypes::R,INS_SUB);
    Instruction SUBU( 0x00 , 0x23 , instructionTypes::R,INS_SUBU);
    Instruction SW(   0x2B , -1   ,instructionTypes::I,INS_SW);

  }
}
