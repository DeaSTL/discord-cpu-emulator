#include "assembler.hpp"


namespace MipsEmulator{
  namespace Assembler {
    /*
     * Finds register, decimal, and hex tokens and considers those as paramters
     * returns the count of those parameters
     */
    int getParameterCount(size_t i, std::shared_ptr<Analyzer> analyzer){
      int parameter_count = 0;
      for(size_t j = i + 1; j < analyzer->tokens.size(); j++){

        if(analyzer->tokens[j].type == TokenType::REGISTER || analyzer->tokens[j].type == TokenType::DECIMAL || analyzer->tokens[j].type == TokenType::HEX){
          parameter_count++;
        }
        else{
          return parameter_count;
          break;
        }
      }
      return parameter_count;
    }
    /*
     * Checks if the parameter count is correct
     * returns true if there is an error and also pushes a new error to the analyzer
     */
    bool checkForParameterCountErrors(std::shared_ptr<Analyzer> analyzer,int token_index, int paramter_count, int expected_paramters){
      if(paramter_count < expected_paramters){
        analyzer->errors.push_back(error{
            .type = ErrorType::MISSING_PARAMETER, 
            .line = analyzer->tokens[token_index].line, 
            .column = analyzer->tokens[token_index].column, 
            .message = "Missing parameter"
            });
        return true;
      }
      else if(paramter_count > expected_paramters){
        analyzer->errors.push_back(error{
            .type = ErrorType::TOO_MANY_PARAMETERS, 
            .line = analyzer->tokens[token_index].line, 
            .column = analyzer->tokens[token_index].column, 
            .message = "Too many parameters"
            });
        return true;
      }
      return false;
    }
    std::shared_ptr<Analyzer> analyze(std::vector<token> tokens){
      std::shared_ptr<Analyzer> analyzer(new Analyzer());
      for(token t : tokens){
        analyzer->tokens.push_back(t);
      }

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
                size_t parameter_count = getParameterCount(i, analyzer);

                std::cout << "Parameter count: " << parameter_count << std::endl;
                /*
                 * Breaks out of loop and throws syntax error
                 * if there are too few or too many parameters
                 */
                if(checkForParameterCountErrors(analyzer, i, parameter_count, 3)){
                  i += parameter_count;
                  break;
                }else{
                  uint8_t rs = CpuInstructions::parseRegister(tokens[i + 1].value);
                  uint8_t rt = CpuInstructions::parseRegister(tokens[i + 2].value);
                  uint8_t imm = CpuInstructions::parseImmediate(tokens[i + 3].value);

                  std::cout << "rs: " << (int)rs << std::endl;
                  std::cout << "rt: " << (int)rt << std::endl;
                  std::cout << "imm: " << (int)imm << std::endl;

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
