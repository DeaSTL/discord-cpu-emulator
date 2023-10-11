#include "cpu.hpp"
#include <iostream>
#include <memory>


namespace Cpu {
  using std::cout;
  using std::endl;
  using std::string;

  Instruction::Instruction(){
  };
  Instruction::Instruction(uint8_t opcode, int8_t funct, instructionTypes type, int id,void (*execution_callback)(std::shared_ptr<Cpu> cpu)){
    this->opcode = opcode;
    this->funct = funct;
    this->type = type;
    this->id = id;
    this->execution_callback = execution_callback;
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
    cout << "Size: " << sizeof(*this) << endl;
  };
  namespace instructions {
    Instruction ADD(  0x00 , 0x20 ,instructionTypes::R,INS_ADD , execution::add);
    Instruction ADDI( 0x08 , -1   ,instructionTypes::I,INS_ADDI, execution::addi);
    Instruction ADDIU(0x09 , -1   ,instructionTypes::I,INS_ADDIU, execution::addiu);
    Instruction ADDU( 0x00 , 0x21 ,instructionTypes::R,INS_ADDU, execution::addu);
    Instruction AND(  0x00 , 0x24 ,instructionTypes::R,INS_AND, execution::and_);
    Instruction ANDI( 0x0C , -1   ,instructionTypes::I,INS_ANDI, execution::andi);
    Instruction BEQ(  0x04 , -1   ,instructionTypes::I,INS_BEQ, execution::beq);
    Instruction BLEZ( 0x06 , -1   ,instructionTypes::I,INS_BLEZ, execution::blez);
    Instruction BNE(  0x05 , -1   ,instructionTypes::I,INS_BNE, execution::bne);
    Instruction BGTZ( 0x07 , -1   ,instructionTypes::I,INS_BGTZ, execution::bgtz);
    Instruction DIV(  0x00 , 0x1A , instructionTypes::R,INS_DIV, execution::div);
    Instruction DIVU( 0x00 , 0x1B , instructionTypes::R,INS_DIVU, execution::divu);
    Instruction J(    0x02 , -1   ,instructionTypes::J,INS_J, execution::j);
    Instruction JAL(  0x03 , -1   ,instructionTypes::J,INS_JAL, execution::jal);
    Instruction JALR( 0x00 , 0x09 , instructionTypes::R,INS_JALR, execution::jalr);
    Instruction JR(   0x00 , 0x08 , instructionTypes::R,INS_JR, execution::jr);
    Instruction LB(   0x20 , -1   ,instructionTypes::I,INS_LB, execution::lb);
    Instruction LBU(  0x24 , -1   ,instructionTypes::I,INS_LBU, execution::lbu);
    Instruction LHU(  0x25 , -1   ,instructionTypes::I,INS_LHU, execution::lhu);
    Instruction LUI(  0x0F , -1   ,instructionTypes::I,INS_LUI, execution::lui);
    Instruction LW(   0x23 , -1   ,instructionTypes::I,INS_LW, execution::lw);
    Instruction MFHI( 0x00 , 0x10 , instructionTypes::R,INS_MFHI, execution::mfhi);
    Instruction MTHI( 0x00 , 0x11 , instructionTypes::R,INS_MTHI, execution::mthi);
    Instruction MFLO( 0x00 , 0x12 , instructionTypes::R,INS_MFLO, execution::mflo);
    Instruction MTLO( 0x00 , 0x13 , instructionTypes::R,INS_MTLO, execution::mtlo);
    Instruction MULT( 0x00 , 0x18 , instructionTypes::R,INS_MULT, execution::mult);
    Instruction MULTU(0x00 , 0x19 , instructionTypes::R,INS_MULTU, execution::multu);
    Instruction NOR(  0x00 , 0x27 , instructionTypes::R,INS_NOR, execution::nor);
    Instruction XOR(  0x00 , 0x26 , instructionTypes::R,INS_XOR, execution::xor_);
    Instruction OR(   0x00 , 0x25 , instructionTypes::R,INS_OR, execution::or_);
    Instruction ORI(  0x0D , -1   ,instructionTypes::I,INS_ORI, execution::ori);
    Instruction SB(   0x28 , -1   ,instructionTypes::I,INS_SB, execution::sb);
    Instruction SH(   0x29 , -1   ,instructionTypes::I,INS_SH, execution::sh);
    Instruction SLT(  0x00 , 0x2A , instructionTypes::R,INS_SLT, execution::slt);
    Instruction SLTI( 0x0A , -1   ,instructionTypes::I,INS_SLTI, execution::slti);
    Instruction SLTIU(0x0B , -1   ,instructionTypes::I,INS_SLTIU, execution::sltiu);
    Instruction SLTU( 0x00 , 0x2B , instructionTypes::R,INS_SLTU, execution::sltu);
    Instruction SLL(  0x00 , 0x00 , instructionTypes::R,INS_SLL, execution::sll);
    Instruction SRL(  0x00 , 0x02 , instructionTypes::R,INS_SRL, execution::srl);
    Instruction SRA(  0x00 , 0x03 , instructionTypes::R,INS_SRA, execution::sra);
    Instruction SUB(  0x00 , 0x22 , instructionTypes::R,INS_SUB, execution::sub);
    Instruction SUBU( 0x00 , 0x23 , instructionTypes::R,INS_SUBU, execution::subu);
    Instruction SW(   0x2B , -1   ,instructionTypes::I,INS_SW, execution::sw);

  }
}
