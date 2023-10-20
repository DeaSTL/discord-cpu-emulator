#pragma once
#include <string>
#include <vector>
#include <stdint.h>
#include <iostream>
#include "../cpu.hpp"



namespace MipsEmulator{
  namespace Assembler{
    enum TokenType {
      LABEL,
      INSTRUCTION,
      REGISTER,
      HEX,
      DECIMAL,
      UNKNOWN
    };


    enum ErrorType {
      SYNTAX,
      MISSING_PARAMETER,
      INVALID_PARAMETER,
      TOO_MANY_PARAMETERS,
      INVALID_REGISTER,
      INVALID_TOKEN,
      INVALID_LABEL,
      INVALID_INSTRUCTION,
    };


    typedef struct error {
      ErrorType type;
      int line;
      int column;
      std::string message;
      void print(){
        std::cout << "Error: " << message << " Type: ";
        switch(type){
          case SYNTAX:
            std::cout << "SYNTAX";
            break;
          case MISSING_PARAMETER:
            std::cout << "MISSING_PARAMETER";
            break;
          case INVALID_PARAMETER:
            std::cout << "INVALID_PARAMETER";
            break;
          case TOO_MANY_PARAMETERS:
            std::cout << "TOO_MANY_PARAMETERS";
            break;
        };
        std::cout << " Line: " << line << " Column: " << column << "\n";
      };
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
      std::vector<CpuInstructions::instruction> instructions;
    } label;
    /*
     * used for keeping track of the current state of the analyzer
     */
    typedef struct Analyzer {
      std::vector<token> tokens;
      std::vector<error> errors;
      std::vector<label> labels;
      std::vector<CpuInstructions::instruction> instructions;
      void print(){
        std::cout << "Analyzer: \n";
        std::cout << "Tokens: \n";
        for(Assembler::token token : tokens){
          token.print();
        }
        std::cout << "Errors: \n";
        for(error error : errors){
          error.print();
        }
        std::cout << "Labels: \n";
        for(label label : labels){
          std::cout << "Name: " << label.name << " Address: " << label.address << "\n";
        }
        std::cout << "Instructions: \n";
        for(CpuInstructions::instruction instruction : instructions){
          instruction.print();
          std::cout << "------------------\n";
        }

      }
    } Analyzer;

    /*
     * Checks the sequence of tokens for errors
     * @return a vector of errors
     */
    std::shared_ptr<Analyzer> analyze(std::vector<token>);


    /*
     * Hashes a string to a 32 bit integer
     * @param str the string to hash
     * @return the hashed string
     */
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
      void print(){
        std::cout << "Tokenizer: \n";
        std::cout << "Tokens: \n";
        for(auto token : tokens){
          token.print();
        }
        std::cout << "Errors: \n";
        for(auto error : errors){
          error.print();
        }
        std::cout << "Asm Code: \n";
        std::cout << asm_code << "\n";
        std::cout << "Lines: \n";
        for(auto line : lines){
          std::cout << line << "\n";
        }
        std::cout << "Keyword Buffer: \n";
        std::cout << keyword_buffer << "\n";
        std::cout << "Col: " << col << "\n";
        std::cout << "Row: " << row << "\n";
        std::cout << "Next Char: " << next_char << "\n";
        std::cout << "Prev Char: " << prev_char << "\n";
        std::cout << "Curr Char: " << curr_char << "\n";
      };
    } Tokenizer;
  }
}
