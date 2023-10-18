#pragma once
#include <vector>
#include <memory>
#include "assembler.hpp"



namespace MipsEmulator{
  namespace Assembler {
    std::shared_ptr<Analyzer> analyze(std::vector<token> tokens);
  }
}
