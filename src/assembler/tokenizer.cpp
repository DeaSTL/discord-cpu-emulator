#include "assembler.hpp"
#include <iostream>



namespace Assembler {
  std::string test_asm = 
    "lw $s0, $s0, 0x69\n"
    "test:\n"
    "#This is a comment\n"
    " addi $s6, $s9, 0x69\n"
    " addi $s4, $s2, -0x69\n"
    " addi $s6, $s9, 420\n"
    " addi $s4, $s2, -420\n"
    "j->test\n";

  std::string stripWhitespace(std::string asm_input){
    std::string stripped;
    for(char c : asm_input){
      if(c != ' '){
        stripped += c;
      }
    }
    return stripped;
  };
  std::vector<token> tokenize(std::string asm_input){
    std::vector<token> tokens;
    std::string stripped = stripWhitespace(asm_input);
    std::string keyword_buffer = "";
    char next_char;
    for(size_t i = 0; i < stripped.length(); i++){
      char current_char = stripped[i];
      token token = {};
      if(current_char != '\n'){
        if(keyword_buffer.length() < asm_input.length()){
          next_char = stripped[i+1];
        }
        if(current_char != ',' &&
           current_char != '$'
        ){
          keyword_buffer += current_char;
        }
        if(current_char == '#'){
          for(size_t j = i; j < stripped.size(); j++){
            if(stripped[j] == '\n'){
              i = j+1;
              break;
            }
          }
        }
        //Parses the instruction
        if(next_char == '$'){
          std::cout << "Checking instruction: " << keyword_buffer << " with hash: " << hash(keyword_buffer) << std::endl;
          switch(hash(keyword_buffer)){
            case InstructionHash::ADDI:
              token.type = TokenType::INSTRUCTION;
              token.value = "addi";
              keyword_buffer = "";
              tokens.push_back(token);
              break;
            case InstructionHash::ADD:
              token.type = TokenType::INSTRUCTION;
              token.value = "add";
              keyword_buffer = "";
              tokens.push_back(token);
              break;
            case InstructionHash::J:
              token.type = TokenType::INSTRUCTION;
              token.value = "j";
              keyword_buffer = "";
              tokens.push_back(token);
              break;
            case InstructionHash::LW:
              token.type = TokenType::INSTRUCTION;
              token.value = "lw";
              keyword_buffer = "";
              tokens.push_back(token);
              break;
          }
        /*
         * Parses the lebel
         * TODO: Record the line number
         */
        }else if(next_char == ':'){
          token.type = TokenType::LABEL;
          token.value = keyword_buffer;
          keyword_buffer = "";
          tokens.push_back(token);
        /*
         * grabs the jump to label
         * by checking for the '->' symbol
         */
        }else if(next_char == '-' && stripped[i+2] == '>'){
          token.type = TokenType::JUMP;
          token.value = keyword_buffer;
          keyword_buffer = "";
          tokens.push_back(token);
          for(size_t j = i+3; j < stripped.size(); j++){
            if(stripped[j] == '\n'){
              token.type = TokenType::LABEL;
              token.value = keyword_buffer;
              keyword_buffer = "";
              tokens.push_back(token);
              i = j;
              break;
            }
            keyword_buffer += stripped[j];
          }
        /*
         * Grabs register keywords
         */
        }else if(next_char == ','){
          token.type = TokenType::REGISTER;
          token.value = keyword_buffer;
          keyword_buffer = "";
          tokens.push_back(token);
          /*
           * Checks for hex values at the end of the line
           * negative values will have a '-' in front of the hex value
           * negative values will be converted to twos complement format
           */
          if((stripped[i+2] == '0' && stripped[i+3] == 'x') ||
            (stripped[i+2] == '-' && stripped[i+3] == '0' && stripped[i+4] == 'x')){
            for(size_t j = i+2; j < stripped.size(); j++){
              if(stripped[j] == '\n'){
                token.type = TokenType::HEX;
                token.value = keyword_buffer;
                keyword_buffer = "";
                tokens.push_back(token);
                i = j;
                break;
              }
              keyword_buffer += stripped[j];
            }
          /*
           * If we find a $ then we can assume it's a not hex and it's
           * a decimal value. Negative values will be converted to twos complement
           */
          }else if(stripped[i+2] != '$'){
            for(size_t j = i+2; j < stripped.size(); j++){
              if(stripped[j] == '\n'){
                token.type = TokenType::DECIMAL;
                token.value = keyword_buffer;
                keyword_buffer = "";
                tokens.push_back(token);
                i = j;
                break;
              }
              keyword_buffer += stripped[j];
            }

          }
        }
      /*
       * If the current character is a 
       * newline then it will reset the keyword buffer
       */
      } else {
        keyword_buffer = "";
      }
    }
    for(token t: tokens){
      t.print();
    }
    return tokens;
  };
}
