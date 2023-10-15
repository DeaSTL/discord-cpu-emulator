#include "assembler.hpp"
#include "../cpu.hpp"
#include <iostream>
#include <memory>



namespace Assembler {

  void newInstruction(){

  }
  std::string tolower(std::string str){
    std::string lower = "";
    for(char c : str){
      lower += std::tolower(c);
    }
    return lower;
  }

  std::string stripWhitespace(std::string asm_input){
    std::string stripped;
    for(char c : asm_input){
      if(c != ' '){
        stripped += c;
      }
    }
    return stripped;
  };
  std::vector<std::string> toLines(std::string asm_input){
    std::vector<std::string> lines;
    std::string line;
    for(char c : asm_input){
      if(c != '\n'){
        line += c;
      }else{
        lines.push_back(line);
        line = "";
      }
    }
    return lines;
  }
  void nextLine(std::shared_ptr<Tokenizer> tokenizer){
    tokenizer->row++;
    tokenizer->col = 0;
    tokenizer->curr_char = ' ';
    tokenizer->next_char = ' ';
    tokenizer->keyword_buffer = "";
  }
  void nextChar(std::shared_ptr<Tokenizer> tokenizer){
    tokenizer->col++;
    tokenizer->curr_char = tokenizer->lines[tokenizer->row][tokenizer->col];
    tokenizer->next_char = tokenizer->lines[tokenizer->row][tokenizer->col + 1];
    if(tokenizer->col > 0){
      tokenizer->prev_char = tokenizer->lines[tokenizer->row][tokenizer->col - 1];
    }
  }
  void parseComment(std::shared_ptr<Tokenizer> tokenizer){
    for(size_t i = tokenizer->col; i < tokenizer->asm_code.size(); i++){
      if(tokenizer->asm_code[i] == '\n'){
        nextLine(tokenizer);
        break;
      }
    }
  }
  void parseJumpLabel(std::shared_ptr<Tokenizer> tokenizer){
    nextChar(tokenizer);
    nextChar(tokenizer);
    tokenizer->keyword_buffer = "";
    while(tokenizer->col < tokenizer->lines[tokenizer->row].size()){
      tokenizer->keyword_buffer += tokenizer->curr_char;
      std::cout << tokenizer->keyword_buffer << std::endl;
      nextChar(tokenizer);
    }
    token token = {};
    token.type = TokenType::LABEL;
    token.value = tokenizer->keyword_buffer;
    tokenizer->tokens.push_back(token);
  }
  //called when the tokenizer doesn't detect any more registers, we can assume it's a hex value
  void parseHex(std::shared_ptr<Tokenizer> tokenizer){
    tokenizer->keyword_buffer = "";
    //Skips the 0x characters
    nextChar(tokenizer);
    nextChar(tokenizer);
    while(tokenizer->col < tokenizer->lines[tokenizer->row].size()){
      tokenizer->keyword_buffer += tokenizer->curr_char;
      nextChar(tokenizer);
    }
    if(tokenizer->keyword_buffer == ""){
      return;
    }
    token token = {};
    token.type = TokenType::HEX;
    token.value = tokenizer->keyword_buffer;
    tokenizer->tokens.push_back(token);
  }
  void parseDecimal(std::shared_ptr<Tokenizer> tokenizer){
    tokenizer->keyword_buffer = "";
    while(tokenizer->col < tokenizer->lines[tokenizer->row].size()){
      tokenizer->keyword_buffer += tokenizer->curr_char;
      nextChar(tokenizer);
    }
    if(tokenizer->keyword_buffer == ""){
      return;
    }
    token token = {};
    token.type = TokenType::DECIMAL;
    token.value = tokenizer->keyword_buffer;
    tokenizer->tokens.push_back(token);
  }
  //parses the two characters that identify a register
  //Must be called with a empty keyword_buffer
  void parseRegister(std::shared_ptr<Tokenizer> tokenizer){
    tokenizer->keyword_buffer = "";
    //Goes to the next character to start reading the register name
    token token = {};
    token.type = TokenType::REGISTER;
    //skips the $ character
    nextChar(tokenizer);
    //Gets the register name
    tokenizer->keyword_buffer += tokenizer->curr_char;
    nextChar(tokenizer);
    //Gets the register number
    tokenizer->keyword_buffer += tokenizer->curr_char;

    std::cout << "Register: " << tokenizer->keyword_buffer << std::endl;

    token.value = tokenizer->keyword_buffer;
    tokenizer->tokens.push_back(token);
    
    std::cout << "Next Char: " << tokenizer->next_char << std::endl;


    if(tokenizer->next_char != '$'){
      nextChar(tokenizer);
      switch(tokenizer->curr_char){
        case '0':
          switch(tokenizer->next_char){
            case 'x':
              parseHex(tokenizer);
              break;
            default:
              parseDecimal(tokenizer);
              break;
          }
          break;
        default:
          parseDecimal(tokenizer);
          break;
      }
    }

  }
  std::vector<token> tokenize(std::string asm_input){
    std::cout << "Tokenizing:\n" << asm_input << std::endl;
    Tokenizer _tokenizer = {};
    std::shared_ptr<Tokenizer> tokenizer = std::make_shared<Tokenizer>(_tokenizer);
    tokenizer->asm_code = stripWhitespace(asm_input);
    tokenizer->asm_code = tolower(tokenizer->asm_code);
    tokenizer->lines = toLines(tokenizer->asm_code);
    tokenizer->tokens = {};
    tokenizer->row = 0;
    tokenizer->col = 0;
    tokenizer->keyword_buffer = "";
    tokenizer->next_char = ' ';
    tokenizer->curr_char = ' ';
    while(tokenizer->row < tokenizer->lines.size()){
      while(tokenizer->col < tokenizer->lines[tokenizer->row].size()){
        tokenizer->curr_char = tokenizer->lines[tokenizer->row][tokenizer->col];
        tokenizer->next_char = tokenizer->lines[tokenizer->row][tokenizer->col+1];
        if(tokenizer->col > 0){
          tokenizer->prev_char = tokenizer->lines[tokenizer->row][tokenizer->col-1];
        }
        //Other Code
        switch(tokenizer->curr_char){
          case '#':
            parseComment(tokenizer);
            break;
          case '-':
            switch(tokenizer->next_char){
              case '>':
                parseJumpLabel(tokenizer);
                break;
            }
            break;
          case '$':
            parseRegister(tokenizer);
            break;
          default:
            tokenizer->keyword_buffer += tokenizer->curr_char;
            switch(hash(tokenizer->keyword_buffer)){
              case Cpu::instructions::ADDI.hash:
                tokenizer->tokens.push_back(Cpu::instruction::toToken(Cpu::instructions::ADDI,tokenizer));
                break;
              case Cpu::instructions::ADD.hash:
                tokenizer->tokens.push_back(Cpu::instruction::toToken(Cpu::instructions::ADD,tokenizer));
                break;
              case Cpu::instructions::SUB.hash:
                tokenizer->tokens.push_back(Cpu::instruction::toToken(Cpu::instructions::SUB,tokenizer));
                break;
              case Cpu::instructions::LW.hash: 
                tokenizer->tokens.push_back(Cpu::instruction::toToken(Cpu::instructions::LW,tokenizer));
                break;
              case Cpu::instructions::SW.hash:
                tokenizer->tokens.push_back(Cpu::instruction::toToken(Cpu::instructions::SW,tokenizer));
                break;
              case Cpu::instructions::J_.hash:
                tokenizer->tokens.push_back(Cpu::instruction::toToken(Cpu::instructions::J_,tokenizer));
                break;
            }
        }
        tokenizer->col++;
      }
      std::cout << tokenizer->keyword_buffer << std::endl;
      nextLine(tokenizer);
    }
    return tokenizer->tokens;
  };
}
