#include "assembler.hpp"
#include <iostream>



namespace Assembler {
  std::string test_asm = 
    "lw $s0, $s0, 0x69\n"
    "test:\n"
    " addi $s0, $s0, 0x69\n"
    " addi $s0, $s0, 0x69\n"
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
    for(int i = 0; i < stripped.length(); i++){
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
           */
          if(stripped[i+2] == '0' && stripped[i+3] == 'x'){
            for(size_t j = i+2; j < stripped.size(); j++){
              if(stripped[j] == '\n'){
                token.type = TokenType::IMMEDIATE;
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
