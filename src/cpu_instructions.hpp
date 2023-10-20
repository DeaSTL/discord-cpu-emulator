#pragma once
#include <string>
#include <stdint.h>
#include <vector>
#include <memory>
#include <iostream>


namespace MipsEmulator{
  class Cpu;
  namespace CpuInstructions{
    enum InstructionType {
      R,
      I, // Requires rs, rt and imm
      J,
      FR,
      FI,
      INVALID
    };
    enum Register {
      ZERO,
      AT,
      V0,
      V1,
      A0,
      A1,
      A2,
      A3,
      T0,
      T1,
      T2,
      T3,
      T4,
      T5,
      T6,
      T7,
      S0,
      S1,
      S2,
      S3,
      S4,
      S5,
      S6,
      S7,
      T8,
      T9,
      K0,
      K1,
      GP,
      SP,
      FP,
      RA,
      INVALID_REGISTER
    };
    struct instruction {
      std::string name {""};
      uint32_t id {0};
      InstructionType type {INVALID};
      uint32_t raw_instruction{0};
      const int hash;
      uint8_t opcode{0};
      uint8_t rs{0};
      uint8_t rt{0};
      uint8_t rd{0};
      uint8_t shamt{0};
      uint8_t funct{0};
      uint16_t imm{0};
      uint32_t addr{0};
      uint8_t fmt{0};
      uint8_t ft{0};
      uint8_t fs{0};
      uint8_t fd{0};
      bool valid{false};
      void execute(std::shared_ptr<Cpu> cpu);
      void print(){
        std::cout << "Instruction: " << name << " ";
        std::cout << "Type: " << type << " ";
        std::cout << "Raw instruction: " << raw_instruction << " ";
        std::cout << "Opcode: " << opcode << std::endl;
        std::cout << "Rs: " << rs << " ";
        std::cout << "Rt: " << rt << " ";
        std::cout << "Rd: " << rd << " ";
        std::cout << "Shamt: " << shamt << std::endl;
        std::cout << "Funct: " << funct << " ";
        std::cout << "Imm: " << imm << " ";
        std::cout << "Addr: " << addr << " ";
        std::cout << "Fmt: " << fmt << std::endl;
        std::cout << "Ft: " << ft << " ";
        std::cout << "Fs: " << fs << " ";
        std::cout << "Fd: " << fd << " ";
        std::cout << "Valid: " << valid << std::endl;
      }
    };
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
        hash ^= (hash << 15);
        hash ^= (hash >> 30);
        hash += str[i];
        hash ^= (constants[i % 9]);
        hash %= 0x100000000;
      }
      return hash;
    }
    std::shared_ptr<instruction> parseInstruction(std::string instruction);
    Register parseRegister(std::string reg);
    int32_t parseImmediate(std::string imm);

    std::shared_ptr<instruction> parseRawInstruction(uint32_t raw_instruction);
    constexpr instruction ADD = {.name = "add",.type = InstructionType::R,.hash=hash("add"),.opcode = 0,.funct = 32};
    constexpr instruction ADDI = {.name = "addi",.type = InstructionType::I,.hash=hash("addi"),.opcode = 8};
    constexpr instruction ADDIU = {.name = "addiu",.type = InstructionType::I,.hash=hash("addiu"),.opcode = 9};
    constexpr instruction ADDU = {.name = "addu",.type = InstructionType::R,.hash=hash("addu"),.opcode = 0,.funct = 33};
    constexpr instruction AND = {.name = "and",.type = InstructionType::R,.hash=hash("and"),.opcode = 0,.funct = 36};
    constexpr instruction ANDI = {.name = "andi",.type = InstructionType::I,.hash=hash("andi"),.opcode = 12};
    constexpr instruction BEQ{.name = "beq",.type = InstructionType::I,.hash=hash("beq"),.opcode = 4};
    constexpr instruction BLEZ{.name = "blez",.type = InstructionType::I,.hash=hash("blez"),.opcode = 6};
    constexpr instruction BNE{.name = "bne",.type = InstructionType::I,.hash=hash("bne"),.opcode = 5};
    constexpr instruction BGTZ{.name = "bgtz",.type = InstructionType::I,.hash=hash("bgtz"),.opcode = 7};
    constexpr instruction DIV{.name = "div",.type = InstructionType::R,.hash=hash("div"),.opcode = 0,.funct = 26};
    constexpr instruction DIVU{.name = "divu",.type = InstructionType::R,.hash=hash("divu"),.opcode = 0,.funct = 27};
    constexpr instruction J_{.name = "j",.type = InstructionType::J,.hash=hash("j"),.opcode = 2};
    constexpr instruction JAL{.name = "jal",.type = InstructionType::J,.hash=hash("jal"),.opcode = 3};
    constexpr instruction JALR{.name = "jalr",.type = InstructionType::R,.hash=hash("jalr"),.opcode = 0,.funct = 9};
    constexpr instruction JR{.name = "jr",.type = InstructionType::R,.hash=hash("jr"),.opcode = 0,.funct = 8};
    constexpr instruction LB{.name = "lb",.type = InstructionType::I,.hash=hash("lb"),.opcode = 32};
    constexpr instruction LBU{.name = "lbu",.type = InstructionType::I,.hash=hash("lbu"),.opcode = 36};
    constexpr instruction LHU{.name = "lhu",.type = InstructionType::I,.hash=hash("lhu"),.opcode = 37};
    constexpr instruction LUI{.name = "lui",.type = InstructionType::I,.hash=hash("lui"),.opcode = 15};
    constexpr instruction LW{.name = "lw",.type = InstructionType::I,.hash=hash("lw"),.opcode = 35};
    constexpr instruction LWL{.name = "lwl",.type = InstructionType::I,.hash=hash("lwl"),.opcode = 34};
    constexpr instruction LWR{.name = "lwr",.type = InstructionType::I,.hash=hash("lwr"),.opcode = 38};
    constexpr instruction LL{.name = "ll",.type = InstructionType::I,.hash=hash("ll"),.opcode = 48};
    constexpr instruction MFHI{.name = "mfhi",.type = InstructionType::R,.hash=hash("mfhi"),.opcode = 0,.funct = 16};
    constexpr instruction MTHI{.name = "mthi",.type = InstructionType::R,.hash=hash("mthi"),.opcode = 0,.funct = 17};
    constexpr instruction MFLO{.name = "mflo",.type = InstructionType::R,.hash=hash("mflo"),.opcode = 0,.funct = 18};
    constexpr instruction MTLO{.name = "mtlo",.type = InstructionType::R,.hash=hash("mtlo"),.opcode = 0,.funct = 19};
    constexpr instruction MULT{.name = "mult",.type = InstructionType::R,.hash=hash("mult"),.opcode = 0,.funct = 24};
    constexpr instruction MULTU{.name = "multu",.type = InstructionType::R,.hash=hash("multu"),.opcode = 0,.funct = 25};
    constexpr instruction NOR{.name = "nor",.type = InstructionType::R,.hash=hash("nor"),.opcode = 0,.funct = 39};
    constexpr instruction XOR{.name = "xor",.type = InstructionType::R,.hash=hash("xor"),.opcode = 0,.funct = 38};
    constexpr instruction XORI{.name = "xori",.type = InstructionType::I,.hash=hash("xori"),.opcode = 14};
    constexpr instruction OR{.name = "or",.type = InstructionType::R,.hash=hash("or"),.opcode = 0,.funct = 37};
    constexpr instruction ORI{.name = "ori",.type = InstructionType::I,.hash=hash("ori"),.opcode = 13};
    constexpr instruction SB{.name = "sb",.type = InstructionType::I,.hash=hash("sb"),.opcode = 40};
    constexpr instruction SH{.name = "sh",.type = InstructionType::I,.hash=hash("sh"),.opcode = 41};
    constexpr instruction SLT{.name = "slt",.type = InstructionType::R,.hash=hash("slt"),.opcode = 0,.funct = 42};
    constexpr instruction SLTI{.name = "slti",.type = InstructionType::I,.hash=hash("slti"),.opcode = 10};
    constexpr instruction SLTIU{.name = "sltiu",.type = InstructionType::I,.hash=hash("sltiu"),.opcode = 11};
    constexpr instruction SLTU{.name = "sltu",.type = InstructionType::R,.hash=hash("sltu"),.opcode = 0,.funct = 43};
    constexpr instruction SLL{.name = "sll",.type = InstructionType::R,.hash=hash("sll"),.opcode = 0,.funct = 0};
    constexpr instruction SRL{.name = "srl",.type = InstructionType::R,.hash=hash("srl"),.opcode = 0,.funct = 2};
    constexpr instruction SRA{.name = "sra",.type = InstructionType::R,.hash=hash("sra"),.opcode = 0,.funct = 3};
    constexpr instruction SUB{.name = "sub",.type = InstructionType::R,.hash=hash("sub"),.opcode = 0,.funct = 34};
    constexpr instruction SUBU{.name = "subu",.type = InstructionType::R,.hash=hash("subu"),.opcode = 0,.funct = 35};
    constexpr instruction SW{.name = "sw",.type = InstructionType::I,.hash=hash("sw"),.opcode = 43};
    constexpr instruction SWR{.name = "swr",.type = InstructionType::I,.hash=hash("swr"),.opcode = 38};
    constexpr instruction SWL{.name = "swl",.type = InstructionType::I,.hash=hash("swl"),.opcode = 36};
    constexpr instruction SC{.name = "sc",.type = InstructionType::I,.hash=hash("sc"),.opcode = 56};
    constexpr instruction CACHE{.name = "cache",.type = InstructionType::I,.hash=hash("cache"),.opcode = 47};
    constexpr instruction SYSCALL{.name = "syscall",.type = InstructionType::R,.hash=hash("syscall"),.opcode = 0,.funct = 12};
    constexpr instruction BREAK{.name = "break",.type = InstructionType::R,.hash=hash("break"),.opcode = 0,.funct = 13};
    const std::vector<instruction> all = {
      ADD,
      ADDI,
      ADDIU,
      ADDU,
      AND,
      ANDI,
      BEQ,
      BGTZ,
      BLEZ,
      BNE,
      DIV,
      DIVU,
      J_,
      JAL,
      JALR,
      JR,
      LB,
      LBU,
      LHU,
      LUI,
      LW,
      LWL,
      LWR,
      LL,
      MFHI,
      MTHI,
      MFLO,
      MTLO,
      MULT,
      MULTU,
      NOR,
      XOR,
      XORI,
      OR,
      ORI,
      SB,
      SH,
      SLT,
      SLTI,
      SLTIU,
      SLTU,
      SLL,
      SRL,
      SRA,
      SUB,
      SUBU,
      SW,
      SWL,
      SWR,
      SC,
      CACHE,
      SYSCALL,
      BREAK
    };
    constexpr instruction getInstruction(std::string name){
      for(size_t i = 0;i < all.size();i++){
        if(all[i].name == name){
          return instruction{
            .name = all[i].name,
            .type = all[i].type,
            .hash = all[i].hash,
            .opcode = all[i].opcode,
            .funct = all[i].funct
          };
        }
      }
      return instruction{};
    }
  }
}
