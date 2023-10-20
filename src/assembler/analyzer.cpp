#include "assembler.hpp"
#include "cpu_instructions.hpp"




namespace MipsEmulator::Assembler{
  /*
   * Finds register, decimal, and hex tokens and considers those as paramters
   * returns the count of those parameters
   */
  int getParameterCount(size_t i, std::shared_ptr<Analyzer> analyzer){
    int parameter_count = 0;
    for(size_t j = i + 1; j < analyzer->tokens.size(); j++){
      if(analyzer->tokens[j].type == TokenType::REGISTER ||
          analyzer->tokens[j].type == TokenType::DECIMAL ||
          analyzer->tokens[j].type == TokenType::HEX ||
          analyzer->tokens[j].type == TokenType::LABEL){
        if(analyzer->instructions.size() > 0){
          analyzer->instructions.back().print();
        }
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
  bool checkForParameterCountErrors(std::shared_ptr<Analyzer> analyzer,int token_index, int parameter_count, int expected_paramters){
    if(parameter_count < expected_paramters){
      analyzer->errors.push_back(error{
          .type = ErrorType::MISSING_PARAMETER, 
          .line = analyzer->tokens[token_index].line, 
          .column = analyzer->tokens[token_index].column, 
          .message = "Missing parameter expected " + std::to_string(expected_paramters) + " parameters" + " got " + std::to_string(parameter_count)
          });
      return true;
    }
    else if(parameter_count > expected_paramters){
      analyzer->errors.push_back(error{
          .type = ErrorType::TOO_MANY_PARAMETERS, 
          .line = analyzer->tokens[token_index].line, 
          .column = analyzer->tokens[token_index].column, 
          .message = "Too many parameters expected " + std::to_string(expected_paramters) + " parameters" + " got " + std::to_string(parameter_count)
          });
      return true;
    }
    return false;
  }
  label getLabel(std::string name, std::shared_ptr<Analyzer> analyzer){
    for(label l : analyzer->labels){
      if(l.name == name){
        return l;
      }
    }
    return label{};
  }
  std::shared_ptr<Analyzer> analyze(std::vector<token> tokens){
    std::shared_ptr<Analyzer> analyzer(new Analyzer());
    //copies provided tokens to the analyzer
    for(token t : tokens){
      analyzer->tokens.push_back(t);
    }

    for(size_t i = 0; i < tokens.size(); i++){
      switch(tokens[i].type){
        case UNKNOWN:
          {
            analyzer->errors.push_back(error{
                .type = ErrorType::INVALID_TOKEN, 
                .line = tokens[i].line, 
                .column = tokens[i].column, 
                .message = "Unknown token"
                });
            break;
          }
        case HEX:
          {
            analyzer->errors.push_back(error{
                .type = ErrorType::INVALID_TOKEN, 
                .line = tokens[i].line, 
                .column = tokens[i].column, 
                .message = "Hex values are not supported here"
                });
            break;
          }
        case DECIMAL:
          {
            analyzer->errors.push_back(error{
                .type = ErrorType::INVALID_TOKEN, 
                .line = tokens[i].line, 
                .column = tokens[i].column, 
                .message = "Decimal values are not supported here"
                });
            break;
          }
        case REGISTER:
          {
            analyzer->errors.push_back(error{
                .type = ErrorType::INVALID_TOKEN, 
                .line = tokens[i].line, 
                .column = tokens[i].column, 
                .message = "Register values are not supported here"
                });
            break;
          }
        case LABEL:
          {
            std::cout << "Adding Label: " << analyzer->instructions.size() << std::endl;
            Assembler::label current_label{.name = tokens[i].value, .address = (uint32_t)analyzer->instructions.size() + 1};
            analyzer->labels.push_back(current_label);
            break;
          }
        case INSTRUCTION:
          {
            CpuInstructions::instruction current_instruction = CpuInstructions::getInstruction(tokens[i].value);
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
                  i += parameter_count - 1;
                  break;
                }else{
                  CpuInstructions::Register rs = CpuInstructions::parseRegister(tokens[i + 1].value);
                  CpuInstructions::Register rt = CpuInstructions::parseRegister(tokens[i + 2].value);
                  uint32_t imm = CpuInstructions::parseImmediate(tokens[i + 3].value);


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
                break;
              }
              case CpuInstructions::InstructionType::R:
              {
                //TODO: I DON'T FUCKING KNOW WHY i + 1 IS REQUIRED
                size_t parameter_count = getParameterCount(i + 1, analyzer);
                std::cout << "R Instruction" << std::endl;
                if(checkForParameterCountErrors(analyzer, i, parameter_count, 3)){
                  i += parameter_count;
                  break;
                }else{
                  CpuInstructions::Register rs = CpuInstructions::parseRegister(tokens[i + 1].value);
                  CpuInstructions::Register rt = CpuInstructions::parseRegister(tokens[i + 2].value);
                  CpuInstructions::Register rd = CpuInstructions::parseRegister(tokens[i + 3].value);

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
                  if(rd == CpuInstructions::Register::INVALID_REGISTER){
                    analyzer->errors.push_back(error{
                        .type = ErrorType::INVALID_REGISTER, 
                        .line = tokens[i + 3].line, 
                        .column = tokens[i + 3].column, 
                        .message = "Invalid rd register"
                        });
                    i+= parameter_count;
                    break;
                  }

                  current_instruction.rs = rs;
                  current_instruction.rt = rt;
                  current_instruction.rd = rd;
                  analyzer->instructions.push_back(current_instruction);
                  i += parameter_count;
                }
                break;
              }
              case CpuInstructions::InstructionType::J:
              {
                size_t parameter_count = getParameterCount(i, analyzer);
                if(checkForParameterCountErrors(analyzer, i, parameter_count, 1)){
                  i += parameter_count;
                  break;
                }else{
                  uint32_t address = getLabel(tokens[i + 1].value, analyzer).address;
                  current_instruction.addr = address;
                  analyzer->instructions.push_back(current_instruction);
                  i += parameter_count;
                }
                break;
              }
              case CpuInstructions::InstructionType::FI:
              {
                analyzer->errors.push_back(error{
                    .type = ErrorType::INVALID_INSTRUCTION, 
                    .line = tokens[i].line, 
                    .column = tokens[i].column, 
                    .message = "Currenly not supported yet"
                    });
                break;
              }
              case CpuInstructions::InstructionType::FR:
              {
                analyzer->errors.push_back(error{
                    .type = ErrorType::INVALID_INSTRUCTION, 
                    .line = tokens[i].line, 
                    .column = tokens[i].column, 
                    .message = "Currenly not supported yet"
                    });
                break;
              }
              case CpuInstructions::InstructionType::INVALID:
              {
                analyzer->errors.push_back(error{
                    .type = ErrorType::INVALID_INSTRUCTION, 
                    .line = tokens[i].line, 
                    .column = tokens[i].column, 
                    .message = "Invalid instruction"
                    });
                break;
              }
            }
          }
      }
    }
    return analyzer;
  }
}
