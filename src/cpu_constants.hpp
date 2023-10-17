#pragma once
#include "stdint.h"

namespace MipsEmulator {
  namespace CpuConstants{
    const uint32_t MEMORY_MAX = 0xF000000;
    const uint32_t REGISTER_ZERO = 0;
    const uint32_t REGISTER_AT = 1;
    const uint32_t REGISTER_V0 = 2;
    const uint32_t REGISTER_V1 = 3;
    const uint32_t REGISTER_A_START = 4;
    const uint32_t REGISTER_A_END = 7;
    const uint32_t REGISTER_T_START = 8;
    const uint32_t REGISTER_T_END = 15;
    const uint32_t REGISTER_S_START = 16;
    const uint32_t REGISTER_S_END = 23;
    const uint32_t REGISTER_K0 = 26; 
    const uint32_t REGISTER_K1 = 27;
    const uint32_t REGISTER_GP = 28;
    const uint32_t REGISTER_STACK_POINTER = 29;
    const uint32_t REGISTER_FRAME_POINTER = 30;
    const uint32_t REGISTER_RETURN_ADDRESS = 31;

    const uint32_t OPCODE_OFF = 26;
    const uint32_t OPCODE_MASK = 0b111111;
    const uint32_t R_TYPE_RS_OFF = 21;
    const uint32_t R_TYPE_RS_MASK = 0b11111;
    const uint32_t R_TYPE_RT_OFF = 16;
    const uint32_t R_TYPE_RT_MASK = 0b11111;
    const uint32_t R_TYPE_RD_OFF = 11;
    const uint32_t R_TYPE_RD_MASK = 0b11111;
    const uint32_t R_TYPE_SHAMT_OFF = 6;
    const uint32_t R_TYPE_SHAMT_MASK = 0b11111;
    const uint32_t R_TYPE_FUNCT_OFF = 0;
    const uint32_t R_TYPE_FUNCT_MASK = 0b111111;

    const uint32_t I_TYPE_RS_OFF = 21;
    const uint32_t I_TYPE_RS_MASK = 0b11111;
    const uint32_t I_TYPE_RT_OFF = 16;
    const uint32_t I_TYPE_RT_MASK = 0b11111;
    const uint32_t I_TYPE_IMM_OFF = 0;
    const uint32_t I_TYPE_IMM_MASK = 0xFFFF;

    const uint32_t J_TYPE_ADDR_OFF = 0;
    const uint32_t J_TYPE_ADDR_MASK = 0x3FFFFFF;

    const uint32_t R_FUNCTION_ADD = 0x20;
    const uint32_t R_FUNCTION_ADDU = 0x21;
    const uint32_t R_FUNCTION_AND = 0x24;
    const uint32_t R_FUNCTION_DIV = 0x1A;
    const uint32_t R_FUNCTION_DIVU = 0x1B;
    const uint32_t R_FUNCTION_JALR = 0x09;
    const uint32_t R_FUNCTION_JR = 0x08;
    const uint32_t R_FUNCTION_MFHI = 0x10;
    const uint32_t R_FUNCTION_MFLO = 0x12;
    const uint32_t R_FUNCTION_MTHI = 0x11;
    const uint32_t R_FUNCTION_MTLO = 0x13;
    const uint32_t R_FUNCTION_MULT = 0x18;
    const uint32_t R_FUNCTION_MULTU = 0x19;
    const uint32_t R_FUNCTION_NOR = 0x27;
    const uint32_t R_FUNCTION_OR = 0x25;
    const uint32_t R_FUNCTION_SLL = 0x00;
    const uint32_t R_FUNCTION_SLLV = 0x04;
    const uint32_t R_FUNCTION_SRLV = 0x06;
    const uint32_t R_FUNCTION_SLT = 0x2A;
    const uint32_t R_FUNCTION_SLTU = 0x2B;
    const uint32_t R_FUNCTION_SRA = 0x03;
    const uint32_t R_FUNCTION_SRAV = 0x07;
    const uint32_t R_FUNCTION_SRL = 0x02;
    const uint32_t R_FUNCTION_SUB = 0x22;
    const uint32_t R_FUNCTION_SUBU = 0x23;
    const uint32_t R_FUNCTION_XOR = 0x26;
    const uint32_t R_FUNCTION_SYSCALL = 0x0C;
    const uint32_t R_FUNCTION_BREAK = 0x0D;

    const uint32_t R_FUNCTIONS[] {
      R_FUNCTION_ADD,
      R_FUNCTION_ADDU,
      R_FUNCTION_AND,
      R_FUNCTION_DIV,
      R_FUNCTION_DIVU,
      R_FUNCTION_JALR,
      R_FUNCTION_JR,
      R_FUNCTION_MFHI,
      R_FUNCTION_MFLO,
      R_FUNCTION_MTHI,
      R_FUNCTION_MTLO,
      R_FUNCTION_MULT,
      R_FUNCTION_MULTU,
      R_FUNCTION_NOR,
      R_FUNCTION_OR,
      R_FUNCTION_SLL,
      R_FUNCTION_SLLV,
      R_FUNCTION_SRLV,
      R_FUNCTION_SLT,
      R_FUNCTION_SLTU,
      R_FUNCTION_SRA,
      R_FUNCTION_SRAV,
      R_FUNCTION_SRL,
      R_FUNCTION_SUB,
      R_FUNCTION_SUBU,
      R_FUNCTION_XOR,
      R_FUNCTION_SYSCALL,
      R_FUNCTION_BREAK
    };

    const uint32_t J_FUNCTION_J = 0x02;
    const uint32_t J_FUNCTION_JAL = 0x03;

    const uint32_t I_FUNCTION_ADDI = 0x08;
    const uint32_t I_FUNCTION_ADDIU = 0x09;
    const uint32_t I_FUNCTION_ANDI = 0x0C;
    const uint32_t I_FUNCTION_BEQ = 0x04;
    const uint32_t I_FUNCTION_BGTZ = 0x07;
    const uint32_t I_FUNCTION_BLEZ = 0x06;
    const uint32_t I_FUNCTION_BNE = 0x05;
    const uint32_t I_FUNCTION_LB = 0x20;
    const uint32_t I_FUNCTION_LBU = 0x24;
    const uint32_t I_FUNCTION_LH = 0x21;
    const uint32_t I_FUNCTION_LL = 0x30;
    const uint32_t I_FUNCTION_LHU = 0x25;
    const uint32_t I_FUNCTION_LUI = 0x0F;
    const uint32_t I_FUNCTION_LW = 0x23;
    const uint32_t I_FUNCTION_LWL = 0x22;
    const uint32_t I_FUNCTION_LWR = 0x26;
    const uint32_t I_FUNCTION_ORI = 0x0D;
    const uint32_t I_FUNCTION_SB = 0x28;
    const uint32_t I_FUNCTION_SC = 0x38;
    const uint32_t I_FUNCTION_SH = 0x29;
    const uint32_t I_FUNCTION_SLTI = 0x0A;
    const uint32_t I_FUNCTION_SLTIU = 0x0B;
    const uint32_t I_FUNCTION_SW = 0x2B;
    const uint32_t I_FUNCTION_XORI = 0x0E;

    const uint32_t INS_ADD = 0x1;
    const uint32_t INS_ADDU = 0x2;
    const uint32_t INS_AND = 0x3;
    const uint32_t INS_DIV = 0x4;
    const uint32_t INS_DIVU = 0x5;
    const uint32_t INS_JALR = 0x6;
    const uint32_t INS_JR = 0x7;
    const uint32_t INS_MFHI = 0x8;
    const uint32_t INS_MFLO = 0x9;
    const uint32_t INS_MTHI = 0xA;
    const uint32_t INS_MTLO = 0xB;
    const uint32_t INS_MULT = 0xC;
    const uint32_t INS_MULTU = 0xD;
    const uint32_t INS_NOR = 0xE;
    const uint32_t INS_OR = 0xF;
    const uint32_t INS_SLL = 0x10;
    const uint32_t INS_SLLV = 0x11;
    const uint32_t INS_SLT = 0x11;
    const uint32_t INS_SLTU = 0x12;
    const uint32_t INS_SRA = 0x13;
    const uint32_t INS_SC = 0x13;
    const uint32_t INS_SRL = 0x14;
    const uint32_t INS_SUB = 0x15;
    const uint32_t INS_SUBU = 0x16;
    const uint32_t INS_XOR = 0x17;
    const uint32_t INS_J = 0x18;
    const uint32_t INS_JAL = 0x19;
    const uint32_t INS_ADDI = 0x1A;
    const uint32_t INS_ADDIU = 0x1B;
    const uint32_t INS_ANDI = 0x1C;
    const uint32_t INS_BEQ = 0x1D;
    const uint32_t INS_BGTZ = 0x1E;
    const uint32_t INS_BLEZ = 0x1F;
    const uint32_t INS_BNE = 0x20;
    const uint32_t INS_LB = 0x21;
    const uint32_t INS_LBU = 0x22;
    const uint32_t INS_LH = 0x23;
    const uint32_t INS_LHU = 0x24;
    const uint32_t INS_LUI = 0x25;
    const uint32_t INS_LW = 0x26;
    const uint32_t INS_LWL = 0x27;
    const uint32_t INS_LL = 0x28;
    const uint32_t INS_LWR = 0x28;
    const uint32_t INS_ORI = 0x29;
    const uint32_t INS_SB = 0x2A;
    const uint32_t INS_SH = 0x2B;
    const uint32_t INS_SLTI = 0x2C;
    const uint32_t INS_SLTIU = 0x2D;
    const uint32_t INS_SW = 0x2E;
    const uint32_t INS_XORI = 0x2F;
    const uint32_t INS_SYSCALL = 0x30;
    const uint32_t INS_BREAK = 0x31;
    const uint32_t INS_SRAV = 0x32;
    const uint32_t INS_SRLV = 0x33;

  }

}
