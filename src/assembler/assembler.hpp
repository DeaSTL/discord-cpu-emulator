#pragma once
#include <string>
#include <vector>
#include <stdint.h>
#include <iostream>




namespace Assembler{
  extern std::string test_asm;
  enum TokenType {
    LABEL,
    INSTRUCTION,
    REGISTER,
    HEX,
    DECIMAL,
    JUMP,
    UNKNOWN
  };


  enum ErrorType {
    SYNTAX,
    MISSING_PARAMETER,
    INVALID_PARAMETER
  };


  typedef struct error {


  }error;
  
  typedef struct token{
    TokenType type;
    std::string value;
    int line;
    int column;
    void print(){
      std::cout << "Token: " << value << " Type: ";
      switch(type){
        case LABEL:
          std::cout << "LABEL";
          break;
        case INSTRUCTION:
          std::cout << "INSTRUCTION";
          break;
        case REGISTER:
          std::cout << "REGISTER";
          break;
        case HEX:
          std::cout << "HEX";
          break;
        case DECIMAL:
          std::cout << "DECIMAL";
          break;
        case JUMP:
          std::cout << "JUMP";
          break;
        case UNKNOWN:
          std::cout << "UNKNOWN";
          break;
      };
      std::cout << " Line: " << line << " Column: " << column << "\n";
    };
  } token;
  typedef struct label{
    std::string name;
    uint32_t address;
    std::vector<token> tokens;
  } label;

  constexpr int hash(std::string str){
    int hash = 0;
    int constants[9] = {
      0xdead,
      0xbeef,
      0xDEAF,
      0xbabe5,
      0x1337,
      0x42069,
      0xDEC0DE,
      0xDEFC0,
      0xC0FFEE
    };
    for(size_t i = 0; i < str.length(); i++){
      hash += str[i];
      hash &= (hash << 15);
      hash ^= (hash >> 30);
      hash += str[i];
      hash ^= (constants[i % 9]);
    }
    return hash;
  }

  /*
   * Tokenizes the given mips32 assembly code to tokens
   */
  std::vector<token> tokenize(std::string);
  typedef struct Tokenizer {
    std::vector<token> tokens;
    std::vector<error> errors;
    //stripped assembly code
    std::string asm_code;
    std::vector<std::string> lines;
    std::string keyword_buffer;
    int col;
    int row;
    char next_char;
    char prev_char;
    char curr_char;
  } Tokenizer;
  /*
   * Checks the sequence of tokens for errors
   * @return a vector of errors
   */
  std::vector<error> analyze(std::vector<token>);
}
