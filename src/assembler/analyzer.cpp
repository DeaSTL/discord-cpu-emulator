#include "assembler.hpp"


namespace MipsEmulator{
  namespace Assembler {
    std::shared_ptr<Analyzer> analyze(std::vector<token> tokens){
      std::shared_ptr<Analyzer> analyzer(new Analyzer());
      analyzer->tokens = tokens;

      for(size_t i = 0; i < tokens.size(); i++){
        switch(tokens[i].type){
          case LABEL:
          {
            Assembler::label current_label{.name = tokens[i].value, .address = (uint32_t)analyzer->instructions.size()};
            analyzer->labels.push_back(current_label);
            break;
          }
          case INSTRUCTION:
          {
            CpuInstructions::instruction current_instruction = CpuInstructions::getInstruction(tokens[i].value);
            std::cout << "Instruction: " << tokens[i].value << std::endl;
            switch(current_instruction.type){
              case CpuInstructions::InstructionType::I:
              {
                std::cout << "Instruction type: I" << std::endl;
                int parameter_count = 0;
                for(size_t j = i + 1; j < tokens.size(); j++){
                  if(tokens[j].type == TokenType::REGISTER || tokens[j].type == TokenType::DECIMAL || tokens[j].type == TokenType::HEX){
                    parameter_count++;
                  }
                  else{
                    break;
                  }
                }
                std::cout << "Parameter count: " << parameter_count << std::endl;
                /*
                 * Breaks out of loop and throws syntax error
                 * if there are too few or too many parameters
                 */
                if(parameter_count < 3){
                  analyzer->errors.push_back(error{
                      .type = ErrorType::MISSING_PARAMETER, 
                      .line = tokens[i].line, 
                      .column = tokens[i].column, 
                      .message = "Missing parameter"
                      });
                  i += parameter_count;
                  break;
                }
                /*
                 * Breaks out of loop and throws syntax error
                 * if there are too few or too many parameters
                 */
                else if(parameter_count > 3){
                  analyzer->errors.push_back(error{
                      .type = ErrorType::TOO_MANY_PARAMETERS, 
                      .line = tokens[i].line, 
                      .column = tokens[i].column, 
                      .message = "Too many parameters"
                      });
                  i += parameter_count;
                  break;
                }
                else{
                  uint8_t rs = CpuInstructions::parseRegister(tokens[i + 1].value);
                  uint8_t rt = CpuInstructions::parseRegister(tokens[i + 2].value);
                  uint8_t imm = CpuInstructions::parseImmediate(tokens[i + 3].value);

                  if(rs == CpuInstructions::Register::INVALID_REGISTER){
                    analyzer->errors.push_back(error{
                        .type = ErrorType::INVALID_REGISTER, 
                        .line = tokens[i + 1].line, 
                        .column = tokens[i + 1].column, 
                        .message = "Invalid rs register"
                        });
                    i+= parameter_count;
                    break;
                  }
                  if(rt == CpuInstructions::Register::INVALID_REGISTER){
                    analyzer->errors.push_back(error{
                        .type = ErrorType::INVALID_REGISTER, 
                        .line = tokens[i + 2].line, 
                        .column = tokens[i + 2].column, 
                        .message = "Invalid rt register"
                        });
                    i+= parameter_count;
                    break;
                  }
                  current_instruction.rs = rs;
                  current_instruction.rt = rt;
                  current_instruction.imm = imm;
                  analyzer->instructions.push_back(current_instruction);
                  i += parameter_count;
                }
              }
              case CpuInstructions::InstructionType::J:
              {
              }
              case CpuInstructions::InstructionType::R:
              {
              }
              case CpuInstructions::InstructionType::INVALID:
              {
              }
            }
          }
        }
      }
      return analyzer;
    }
  }
}
