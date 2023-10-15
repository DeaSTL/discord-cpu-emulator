#pragma once
#include "assembler/assembler.hpp"
#include "stdint.h"
#include <string>
#include <memory>
#include "cpu_constants.hpp"





namespace Cpu{

  using std::string;
  class Cpu;

  enum InstructionType {
    R,
    I,
    J,
    FR,
    FI,
    INVALID
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
    void print();
    static Assembler::token toToken(instruction instr, std::shared_ptr<Assembler::Tokenizer> tokenizer){
      Assembler::token token;
      token.type = Assembler::INSTRUCTION;
      token.value = instr.name;
      token.line = tokenizer->row;
      token.column = tokenizer->col;
      tokenizer->keyword_buffer = "";
      return token;
    }
  };
  std::shared_ptr<instruction> parseRawInstruction(uint32_t raw_instruction);
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
      uint32_t memory[MEMORY_MAX]; // 16MB
      // Current instruction being executed
      instruction* instruction_register;
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

      Cpu();
      ~Cpu();
  };
  namespace execution {
    void add(std::shared_ptr<Cpu> cpu);
    void addu(std::shared_ptr<Cpu> cpu);
    void and_(std::shared_ptr<Cpu> cpu);
    void div(std::shared_ptr<Cpu> cpu);
    void divu(std::shared_ptr<Cpu> cpu);
    void jalr(std::shared_ptr<Cpu> cpu);
    void jr(std::shared_ptr<Cpu> cpu);
    void mfhi(std::shared_ptr<Cpu> cpu);
    void mflo(std::shared_ptr<Cpu> cpu);
    void mthi(std::shared_ptr<Cpu> cpu);
    void mtlo(std::shared_ptr<Cpu> cpu);
    void mult(std::shared_ptr<Cpu> cpu);
    void multu(std::shared_ptr<Cpu> cpu);
    void nor(std::shared_ptr<Cpu> cpu);
    void or_(std::shared_ptr<Cpu> cpu);
    void sll(std::shared_ptr<Cpu> cpu);
    void sllv(std::shared_ptr<Cpu> cpu);
    void slt(std::shared_ptr<Cpu> cpu);
    void sltu(std::shared_ptr<Cpu> cpu);
    void sra(std::shared_ptr<Cpu> cpu);
    void srav(std::shared_ptr<Cpu> cpu);
    void srl(std::shared_ptr<Cpu> cpu);
    void srlv(std::shared_ptr<Cpu> cpu);
    void sub(std::shared_ptr<Cpu> cpu);
    void subu(std::shared_ptr<Cpu> cpu);
    void xor_(std::shared_ptr<Cpu> cpu);
    void addi(std::shared_ptr<Cpu> cpu);
    void addiu(std::shared_ptr<Cpu> cpu);
    void andi(std::shared_ptr<Cpu> cpu);
    void beq(std::shared_ptr<Cpu> cpu);
    void bgez(std::shared_ptr<Cpu> cpu);
    void bgezal(std::shared_ptr<Cpu> cpu);
    void bgtz(std::shared_ptr<Cpu> cpu);
    void blez(std::shared_ptr<Cpu> cpu);
    void bltz(std::shared_ptr<Cpu> cpu);
    void bltzal(std::shared_ptr<Cpu> cpu);
    void bne(std::shared_ptr<Cpu> cpu);
    void lb(std::shared_ptr<Cpu> cpu);
    void lbu(std::shared_ptr<Cpu> cpu);
    void lh(std::shared_ptr<Cpu> cpu);
    void lhu(std::shared_ptr<Cpu> cpu);
    void lui(std::shared_ptr<Cpu> cpu);
    void lw(std::shared_ptr<Cpu> cpu);
    void lwl(std::shared_ptr<Cpu> cpu);
    void lwr(std::shared_ptr<Cpu> cpu);
    void ori(std::shared_ptr<Cpu> cpu);
    void sb(std::shared_ptr<Cpu> cpu);
    void sh(std::shared_ptr<Cpu> cpu);
    void slti(std::shared_ptr<Cpu> cpu);
    void sltiu(std::shared_ptr<Cpu> cpu);
    void sw(std::shared_ptr<Cpu> cpu);
    void swl(std::shared_ptr<Cpu> cpu);
    void swr(std::shared_ptr<Cpu> cpu);
    void xori(std::shared_ptr<Cpu> cpu);
    void j(std::shared_ptr<Cpu> cpu);
    void jal(std::shared_ptr<Cpu> cpu);
  }
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

  namespace instructions {
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
    constexpr instruction MFHI{.name = "mfhi",.type = InstructionType::R,.hash=hash("mfhi"),.opcode = 0,.funct = 16};
    constexpr instruction MTHI{.name = "mthi",.type = InstructionType::R,.hash=hash("mthi"),.opcode = 0,.funct = 17};
    constexpr instruction MFLO{.name = "mflo",.type = InstructionType::R,.hash=hash("mflo"),.opcode = 0,.funct = 18};
    constexpr instruction MTLO{.name = "mtlo",.type = InstructionType::R,.hash=hash("mtlo"),.opcode = 0,.funct = 19};
    constexpr instruction MULT{.name = "mult",.type = InstructionType::R,.hash=hash("mult"),.opcode = 0,.funct = 24};
    constexpr instruction MULTU{.name = "multu",.type = InstructionType::R,.hash=hash("multu"),.opcode = 0,.funct = 25};
    constexpr instruction NOR{.name = "nor",.type = InstructionType::R,.hash=hash("nor"),.opcode = 0,.funct = 39};
    constexpr instruction XOR{.name = "xor",.type = InstructionType::R,.hash=hash("xor"),.opcode = 0,.funct = 38};
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
  }
}
