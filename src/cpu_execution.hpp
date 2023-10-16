#pragma once
#include "cpu_instructions.hpp"


namespace MipsEmulator {
  namespace CpuExecution {
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
}
