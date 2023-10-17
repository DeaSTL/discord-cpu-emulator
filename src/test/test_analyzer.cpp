#include <catch2/catch_test_macros.hpp>
#include "../assembler/assembler.hpp"
#include "../assembler/analyzer.hpp"
#include "test_analyzer.hpp"


namespace MipsEmulator{
  namespace Test::Analyzer{
    TEST_CASE("Test Analyzer", "[analyzer]"){
      REQUIRE(1 == 1);
    }
  }
}
