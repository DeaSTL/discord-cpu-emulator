#pragma once
#include <string>
#include <vector>
#include <stdint.h>
#include <iostream>




namespace Assembler{
  extern std::string test_asm;
  enum TokenType {
    LABEL,
    INSTRUCTION,
    REGISTER,
    HEX,
    DECIMAL,
    JUMP,
    UNKNOWN
  };
  
  typedef struct token{
    TokenType type;
    std::string value;
    void print(){
      std::cout << "Token: " << value << " Type: ";
      switch(type){
        case LABEL:
          std::cout << "LABEL";
          break;
        case INSTRUCTION:
          std::cout << "INSTRUCTION";
          break;
        case REGISTER:
          std::cout << "REGISTER";
          break;
        case HEX:
          std::cout << "HEX";
          break;
        case DECIMAL:
          std::cout << "DECIMAL";
          break;
        case JUMP:
          std::cout << "JUMP";
          break;
        case UNKNOWN:
          std::cout << "UNKNOWN";
          break;
      };
      std::cout << std::endl;
    };
  } token;
  typedef struct label{
    std::string name;
    uint32_t address;
    std::vector<token> tokens;
  } label;

  constexpr int hash(std::string str){
    int hash = 0;
    int constants[9] = {
      0xdead,
      0xbeef,
      0xDEAF,
      0xbabe5,
      0x1337,
      0x42069,
      0xDEC0DE,
      0xDEFC0,
      0xC0FFEE
    };
    for(size_t i = 0; i < str.length(); i++){
      hash += str[i];
      hash &= (hash << 15);
      hash ^= (hash >> 30);
      hash += str[i];
      hash ^= (constants[i % 9]);
    }
    return hash;
  }
  enum InstructionHash : int {
    ADD = hash("add"),
    ADDI = hash("addi"),
    ADDIU = hash("addiu"),
    ADDU = hash("addu"),
    AND = hash("and"),
    ANDI = hash("andi"),
    BEQ = hash("beq"),
    BLEZ = hash("blez"),
    BNE = hash("bne"),
    BGTZ = hash("bgtz"),
    DIV = hash("div"),
    DIVU = hash("divu"),
    J = hash("j"),
    JAL = hash("jal"),
    JALR = hash("jalr"),
    JR = hash("jr"),
    LB = hash("lb"),
    LBU = hash("lbu"),
    LHU = hash("lhu"),
    LUI = hash("lui"),
    LW = hash("lw"),
    MFHI = hash("mfhi"),
    MTHI = hash("mthi"),
    MFLO = hash("mflo"),
    MTLO = hash("mtlo"),
    MULT = hash("mult"),
    MULTU = hash("multu"),
    NOR = hash("nor"),
    XOR = hash("xor"),
    OR = hash("or"),
    ORI = hash("ori"),
    SB = hash("sb"),
    SH = hash("sh"),
    SLT = hash("slt"),
    SLTI = hash("slti"),
    SLTIU = hash("sltiu"),
    SLTU = hash("sltu"),
    SLL = hash("sll"),
    SRL = hash("srl"),
    SRA = hash("sra"),
    SUB = hash("sub"),
    SUBU = hash("subu"),
    SW = hash("sw"),
    LWL = hash("lwl"),
  };

  /*
   * Tokenizes the given mips32 assembly code to tokens
   */
  std::vector<token> tokenize(std::string);

  


}
