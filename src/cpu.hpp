#pragma once
#include "stdint.h"
#include "cpu_constants.hpp"
#include "cpu_instructions.hpp"




namespace MipsEmulator {
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
      uint32_t memory[CpuConstants::MEMORY_MAX]; // 16MB
      // Current instruction being executed
      CpuInstructions::instruction* instruction_register;
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

}
