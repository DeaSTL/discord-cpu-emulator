#include <memory>
#include "cpu.hpp"


namespace Cpu {
  namespace execution {
    /*
     * Adds the contents of two registers and stores the result in the destination register.
     * @rd The destination register.
     * @rs The first source register.
     * @rt The second source register.
     * @example add $t0, $t1, $t2
     */
    void add(std::shared_ptr<Cpu> cpu) {
      cpu->registers_gp[cpu->instruction_register->rd] = 
        (int32_t)cpu->registers_gp[cpu->instruction_register->rs] +
        (int32_t)cpu->registers_gp[cpu->instruction_register->rt];
    }
    /*
     * Adds a register and a signed immediate value and stores the result in a register.
     * @rt The destination register.
     * @rs The first source register.
     * @imm The immediate value.
     * @example addi $t0, $t1, -100
     */
    void addi(std::shared_ptr<Cpu> cpu) {
      cpu->registers_gp[cpu->instruction_register->rt] = 
        cpu->registers_gp[cpu->instruction_register->rs] +
        cpu->instruction_register->imm;
    }
    /*
     * Adds a two registers containing unsigned values and stores the result in a register.
     * @rd The destination register.
     * @rs The first source register.
     * @rt The second source register.
     * @example addu $t0, $t1, $t2
     */
    void addu(std::shared_ptr<Cpu> cpu) {
      cpu->registers_gp[cpu->instruction_register->rd] = 
        cpu->registers_gp[cpu->instruction_register->rs] +
        cpu->registers_gp[cpu->instruction_register->rt];

    }
    /*
     * Adds a adds a imm 16 bit unsigned value to a register and stores the result in a register.
     * @rt The destination register.
     * @rs The first source register.
     * @imm The immediate value.
     * @example addiu $t0, $t1, 100
     */
    void addiu(std::shared_ptr<Cpu> cpu) {
      cput->registers_gp[cpu->instruction_register->rt] = 
        cpu->registers_gp[cpu->instruction_register->rs] +
        cpu->instruction_register->imm;

    }
    void and_(std::shared_ptr<Cpu> cpu) {

    }
    void div(std::shared_ptr<Cpu> cpu) {

    }
    void divu(std::shared_ptr<Cpu> cpu) {

    }
    void jalr(std::shared_ptr<Cpu> cpu) {

    }
    void jr(std::shared_ptr<Cpu> cpu) {

    }
    void mfhi(std::shared_ptr<Cpu> cpu) {

    }
    void mthi(std::shared_ptr<Cpu> cpu) {

    }
    void mflo(std::shared_ptr<Cpu> cpu) {

    }
    void mtlo(std::shared_ptr<Cpu> cpu) {

    }
    void mult(std::shared_ptr<Cpu> cpu) {

    }
    void multu(std::shared_ptr<Cpu> cpu) {

    }
    void nor(std::shared_ptr<Cpu> cpu) {

    }
    void xor_(std::shared_ptr<Cpu> cpu) {

    }
    void or_(std::shared_ptr<Cpu> cpu) {

    }
    void slt(std::shared_ptr<Cpu> cpu) {

    }
    void sltu(std::shared_ptr<Cpu> cpu) {

    }
    void sll(std::shared_ptr<Cpu> cpu) {

    }
    void srl(std::shared_ptr<Cpu> cpu) {

    }
    void sra(std::shared_ptr<Cpu> cpu) {

    }
    void sub(std::shared_ptr<Cpu> cpu) {

    }
    void subu(std::shared_ptr<Cpu> cpu) {

    }
    void j(std::shared_ptr<Cpu> cpu) {

    }
    void jal(std::shared_ptr<Cpu> cpu) {

    }
    void slti(std::shared_ptr<Cpu> cpu) {

    }
    void sltiu(std::shared_ptr<Cpu> cpu) {

    }
    void andi(std::shared_ptr<Cpu> cpu) {

    }
    void ori(std::shared_ptr<Cpu> cpu) {

    }
    void lui(std::shared_ptr<Cpu> cpu) {

    }
    void sw(std::shared_ptr<Cpu> cpu) {

    }
    void swl(std::shared_ptr<Cpu> cpu) {

    }
    void beq(std::shared_ptr<Cpu> cpu) {

    }
    void bne(std::shared_ptr<Cpu> cpu) {

    }
    void bgtz(std::shared_ptr<Cpu> cpu) {

    }
    void blez(std::shared_ptr<Cpu> cpu) {

    }
    void lb(std::shared_ptr<Cpu> cpu) {

    }
    void lbu(std::shared_ptr<Cpu> cpu) {

    }
    void lh(std::shared_ptr<Cpu> cpu) {

    }
    void lhu(std::shared_ptr<Cpu> cpu) {

    }
    void lw(std::shared_ptr<Cpu> cpu) {

    }
    void lwl(std::shared_ptr<Cpu> cpu) {

    }
    void lwr(std::shared_ptr<Cpu> cpu) {

    }
    void sb(std::shared_ptr<Cpu> cpu) {

    }
    void sh(std::shared_ptr<Cpu> cpu) {

    }
  }
}
