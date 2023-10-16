#include "assembler.hpp"
#include "../cpu.hpp"
#include <iostream>
#include <memory>


namespace MipsEmulator {
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


      token.value = tokenizer->keyword_buffer;
      tokenizer->tokens.push_back(token);



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
    void instrToToken(CpuInstructions::instruction instr, std::shared_ptr<Assembler::Tokenizer> tokenizer){
      Assembler::token token;
      token.type = Assembler::INSTRUCTION;
      token.value = instr.name;
      token.line = tokenizer->row;
      token.column = tokenizer->col;
      tokenizer->keyword_buffer = "";
      tokenizer->tokens.push_back(token);
    }
    void parseInstruction(std::shared_ptr<Tokenizer> tokenizer){

      switch(CpuInstructions::hash(tokenizer->keyword_buffer)){
        case CpuInstructions::ADDI.hash:
          instrToToken(CpuInstructions::ADDI,tokenizer);
          break;
        case CpuInstructions::ADD.hash:
          instrToToken(CpuInstructions::ADD,tokenizer);
          break;
        case CpuInstructions::ADDU.hash:
          instrToToken(CpuInstructions::ADDU,tokenizer);
          break;
        case CpuInstructions::AND.hash:
          instrToToken(CpuInstructions::AND,tokenizer);
          break;
        case CpuInstructions::SUB.hash:
          instrToToken(CpuInstructions::SUB,tokenizer);
          break;
        case CpuInstructions::SUBU.hash:
          instrToToken(CpuInstructions::SUBU,tokenizer);
          break;
        case CpuInstructions::LW.hash: 
          instrToToken(CpuInstructions::LW,tokenizer);
          break;
        case CpuInstructions::LB.hash:
          instrToToken(CpuInstructions::LB,tokenizer);
          break;
        case CpuInstructions::LBU.hash:
          instrToToken(CpuInstructions::LBU,tokenizer);
          break;
        case CpuInstructions::LHU.hash:
          instrToToken(CpuInstructions::LHU,tokenizer);
          break;
        case CpuInstructions::SB.hash:
          instrToToken(CpuInstructions::SB,tokenizer);
          break;
        case CpuInstructions::SW.hash:
          instrToToken(CpuInstructions::SW,tokenizer);
          break;
        case CpuInstructions::SH.hash:
          instrToToken(CpuInstructions::SH,tokenizer);
          break;
        case CpuInstructions::J_.hash:
          instrToToken(CpuInstructions::J_,tokenizer);
          break;
        case CpuInstructions::JAL.hash:
          instrToToken(CpuInstructions::JAL,tokenizer);
          break;
        case CpuInstructions::BEQ.hash:
          instrToToken(CpuInstructions::BEQ,tokenizer);
          break;
        case CpuInstructions::BNE.hash:
          instrToToken(CpuInstructions::BNE,tokenizer);
          break;
        case CpuInstructions::SLT.hash:
          instrToToken(CpuInstructions::SLT,tokenizer);
          break;
        case CpuInstructions::SLTI.hash:
          instrToToken(CpuInstructions::SLTI,tokenizer);
          break;
        case CpuInstructions::SLTU.hash:
          instrToToken(CpuInstructions::SLTU,tokenizer);
          break;
        case CpuInstructions::SLTIU.hash:
          instrToToken(CpuInstructions::SLTIU,tokenizer);
          break;
        case CpuInstructions::SLL.hash:
          instrToToken(CpuInstructions::SLL,tokenizer);
          break;
        case CpuInstructions::SRL.hash:
          instrToToken(CpuInstructions::SRL,tokenizer);
          break;
        case CpuInstructions::SRA.hash:
          instrToToken(CpuInstructions::SRA,tokenizer);
          break;
        case CpuInstructions::OR.hash:
          instrToToken(CpuInstructions::OR,tokenizer);
          break;
        case CpuInstructions::XOR.hash:
          instrToToken(CpuInstructions::XOR,tokenizer);
          break;
        case CpuInstructions::NOR.hash:
          instrToToken(CpuInstructions::NOR,tokenizer);
          break;
        case CpuInstructions::ANDI.hash:
          instrToToken(CpuInstructions::ANDI,tokenizer);
          break;
        case CpuInstructions::ORI.hash:
          instrToToken(CpuInstructions::ORI,tokenizer);
          break;
        case CpuInstructions::XORI.hash:
          instrToToken(CpuInstructions::XORI,tokenizer);
          break;
        case CpuInstructions::LUI.hash:
          instrToToken(CpuInstructions::LUI,tokenizer);
          break;
        case CpuInstructions::MFHI.hash:
          instrToToken(CpuInstructions::MFHI,tokenizer);
          break;
        case CpuInstructions::MFLO.hash:
          instrToToken(CpuInstructions::MFLO,tokenizer);
          break;
        case CpuInstructions::MTHI.hash:
          instrToToken(CpuInstructions::MTHI,tokenizer);
          break;
        case CpuInstructions::JR.hash:
          instrToToken(CpuInstructions::JR,tokenizer);
          break;
        case CpuInstructions::JALR.hash:
          instrToToken(CpuInstructions::JALR,tokenizer);
          break;
        case CpuInstructions::MULT.hash:
          instrToToken(CpuInstructions::MULT,tokenizer);
          break;
        case CpuInstructions::MULTU.hash:
          instrToToken(CpuInstructions::MULTU,tokenizer);
          break;
        case CpuInstructions::DIV.hash:
          instrToToken(CpuInstructions::DIV,tokenizer);
          break;
        case CpuInstructions::DIVU.hash:
          instrToToken(CpuInstructions::DIVU,tokenizer);
          break;
        case CpuInstructions::SYSCALL.hash:
          instrToToken(CpuInstructions::SYSCALL,tokenizer);
          break;
        case CpuInstructions::BREAK.hash:
          instrToToken(CpuInstructions::BREAK,tokenizer);
          break;
        default:
          break;
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
              switch(tokenizer->next_char){
                case '$':
                  parseInstruction(tokenizer);
                  break;
                case '-':
                  switch(tokenizer->lines[tokenizer->row][tokenizer->col+2]){
                    case '>':
                      parseInstruction(tokenizer);
                      break;
                  }
                  break;
              }
              break;
          }
          tokenizer->col++;
        }
        nextLine(tokenizer);
      }
      return tokenizer->tokens;
    };
  }
}
