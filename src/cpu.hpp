#pragma once
#include "stdint.h"
#include <string>


#define OPCODE_OFF 26 // + 6
#define OPCODE_MASK 0b111111

#define R_TYPE_RS_OFF 21 // + 5
#define R_TYPE_RS_MASK 0b11111
#define R_TYPE_RT_OFF 16 // + 5
#define R_TYPE_RT_MASK 0b11111
#define R_TYPE_RD_OFF 11 // + 5
#define R_TYPE_RD_MASK 0b11111
#define R_TYPE_SHAMT_OFF 6 // + 5
#define R_TYPE_SHAMT_MASK 0b11111
#define R_TYPE_FUNCT_OFF 0 // + 6
#define R_TYPE_FUNCT_MASK 0b111111

#define I_TYPE_RS_OFF 21 // + 5
#define I_TYPE_RS_MASK 0b11111
#define I_TYPE_RT_OFF 16 // + 5
#define I_TYPE_RT_MASK 0b11111
#define I_TYPE_IMM_OFF 0 // + 16
#define I_TYPE_IMM_MASK 0xFFFF // 16 bits

#define J_TYPE_ADDR_OFF 0 // + 26
#define J_TYPE_ADDR_MASK 0x3FFFFFF // 26 bits

#define R_FUNCTION_ADD 0x20
#define R_FUNCTION_ADDU 0x21
#define R_FUNCTION_AND 0x24
#define R_FUNCTION_DIV 0x1A
#define R_FUNCTION_DIVU 0x1B
#define R_FUNCTION_JALR 0x09
#define R_FUNCTION_JR 0x08
#define R_FUNCTION_MFHI 0x10
#define R_FUNCTION_MFLO 0x12
#define R_FUNCTION_MTHI 0x11
#define R_FUNCTION_MTLO 0x13
#define R_FUNCTION_MULT 0x18
#define R_FUNCTION_MULTU 0x19
#define R_FUNCTION_NOR 0x27
#define R_FUNCTION_OR 0x25
#define R_FUNCTION_SLL 0x00
#define R_FUNCTION_SLT 0x2A
#define R_FUNCTION_SLTU 0x2B
#define R_FUNCTION_SRA 0x03
#define R_FUNCTION_SRL 0x02
#define R_FUNCTION_SUB 0x22
#define R_FUNCTION_SUBU 0x23
#define R_FUNCTION_XOR 0x26


#define J_FUNCTION_J 0x02
#define J_FUNCTION_JAL 0x03

#define I_FUNCTION_ADDI 0x08
#define I_FUNCTION_ADDIU 0x09
#define I_FUNCTION_ANDI 0x0C
#define I_FUNCTION_BEQ 0x04
#define I_FUNCTION_BGTZ 0x07
#define I_FUNCTION_BLEZ 0x06
#define I_FUNCTION_BNE 0x05
#define I_FUNCTION_LB 0x20
#define I_FUNCTION_LBU 0x24
#define I_FUNCTION_LH 0x21
#define I_FUNCTION_LHU 0x25
#define I_FUNCTION_LUI 0x0F
#define I_FUNCTION_LW 0x23
#define I_FUNCTION_LWL 0x22
#define I_FUNCTION_LWR 0x26
#define I_FUNCTION_ORI 0x0D
#define I_FUNCTION_SB 0x28
#define I_FUNCTION_SH 0x29
#define I_FUNCTION_SLTI 0x0A
#define I_FUNCTION_SLTIU 0x0B
#define I_FUNCTION_SW 0x2B

#define INS_ADD 0x1
#define INS_ADDU 0x2
#define INS_AND 0x3
#define INS_DIV 0x4
#define INS_DIVU 0x5
#define INS_JALR 0x6
#define INS_JR 0x7
#define INS_MFHI 0x8
#define INS_MFLO 0x9
#define INS_MTHI 0xA
#define INS_MTLO 0xB
#define INS_MULT 0xC
#define INS_MULTU 0xD
#define INS_NOR 0xE
#define INS_OR 0xF
#define INS_SLL 0x10
#define INS_SLT 0x11
#define INS_SLTU 0x12
#define INS_SRA 0x13
#define INS_SRL 0x14
#define INS_SUB 0x15
#define INS_SUBU 0x16
#define INS_XOR 0x17
#define INS_J 0x18
#define INS_JAL 0x19
#define INS_ADDI 0x1A
#define INS_ADDIU 0x1B
#define INS_ANDI 0x1C
#define INS_BEQ 0x1D
#define INS_BGTZ 0x1E
#define INS_BLEZ 0x1F
#define INS_BNE 0x20
#define INS_LB 0x21
#define INS_LBU 0x22
#define INS_LH 0x23
#define INS_LHU 0x24
#define INS_LUI 0x25
#define INS_LW 0x26
#define INS_LWL 0x27
#define INS_LWR 0x28
#define INS_ORI 0x29
#define INS_SB 0x2A
#define INS_SH 0x2B
#define INS_SLTI 0x2C
#define INS_SLTIU 0x2D
#define INS_SW 0x2E



namespace Cpu{
  using std::string;
  enum instructionTypes {
    R,
    I,
    J,
    FR,
    FI
  };
  class Instruction{
    public:
      uint32_t fetch_raw;
      int id;
      uint8_t opcode;
      //R instructions
      uint8_t rs;
      uint8_t rt;
      uint8_t rd;
      uint8_t shamt;
      int8_t funct;
      //I instructions
      uint16_t imm;
      //J instructions
      uint32_t addr;
      //FR instructions
      //Describe the format of the instruction
      uint8_t fmt;
      uint8_t ft;
      uint8_t fs;
      uint8_t fd;
      instructionTypes type;
      bool valid;
      Instruction(uint8_t opcode, int8_t funct, instructionTypes type, int id);
      Instruction();
      void print();
  };
  Instruction* parseRawInstruction(uint32_t raw_instruction);
  class Cpu {
    public:
      // General purpose registers
      // $zero is always 0 $0
      // $at is reserved for the assembler at $1
      // $v0 and $v1 are used for return values $2 and $3
      // $a0-$a3 are used for arguments $4-$7
      // $t0-$t7 are used for temporaries $8-$15
      // $s0-$s7 are used for saved values $16-$23
      // $t8-$t9 are used for temporaries $24-$25
      // $k0-$k1 are reserved for the OS kernel $26-$27
      // $gp is used for global pointer $28
      // $sp is used for stack pointer $29
      // $fp is used for frame pointer $30
      // $ra is used for return address $31
      uint32_t registers_gp[32];
      // Used to keep track of the current position of the program
      uint32_t register_pc;
      // Used to store the higher 32 bits of a 64 bit result
      uint32_t register_hi;
      // Used to store the lower 32 bits of a 64 bit result
      uint32_t register_lo;
      // Used to store the output of of the previous instruction
      uint32_t register_wb;
      /*
       * 0: Fetch output
       * 1: Decode output
       * 2: Execute output
       * 3: Memory access output
       */
      uint32_t pipeline[4];
      // Physical memory
      uint32_t memory[0xF00000]; // 16MB
      // Current instruction being executed
      Instruction* instruction_register;
      /*
       * Initializes the cpu and returns true if successful
       */
      bool start();
      /*
       * steps through the cpu pipeline and returns true if successful
       */
      bool step();


      uint32_t fetch();
      uint32_t decode();
      uint32_t execute();
      uint32_t memoryAccess();
      uint32_t writeBack();
  };
  namespace instructions {
    extern Instruction ADD;
    extern Instruction ADDI;
    extern Instruction ADDIU;
    extern Instruction ADDU;
    extern Instruction AND;
    extern Instruction ANDI;
    extern Instruction BEQ;
    extern Instruction BLEZ;
    extern Instruction BNE;
    extern Instruction BGTZ;
    extern Instruction DIV;
    extern Instruction DIVU;
    extern Instruction J;
    extern Instruction JAL;
    extern Instruction JALR;
    extern Instruction JR;
    extern Instruction LB;
    extern Instruction LBU;
    extern Instruction LHU;
    extern Instruction LUI;
    extern Instruction LW;
    extern Instruction MFHI;
    extern Instruction MTHI;
    extern Instruction MFLO;
    extern Instruction MTLO;
    extern Instruction MULT;
    extern Instruction MULTU;
    extern Instruction NOR;
    extern Instruction XOR;
    extern Instruction OR;
    extern Instruction ORI;
    extern Instruction SB;
    extern Instruction SH;
    extern Instruction SLT;
    extern Instruction SLTI;
    extern Instruction SLTIU;
    extern Instruction SLTU;
    extern Instruction SLL;
    extern Instruction SRL;
    extern Instruction SRA;
    extern Instruction SUB;
    extern Instruction SUBU;
    extern Instruction SW;
  }
}
