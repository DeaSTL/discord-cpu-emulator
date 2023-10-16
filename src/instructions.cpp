#include "cpu.hpp"
#include <iostream>
#include <memory>

namespace MipsEmulator {
  namespace CpuInstructions {
    using std::cout;
    using std::endl;
    using std::string;

    void instruction::print(){
      cout << "Name: " <<this->name << endl;
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
  }
}
