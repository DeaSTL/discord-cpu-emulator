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
  void instrToToken(Cpu::instruction instr, std::shared_ptr<Assembler::Tokenizer> tokenizer){
    Assembler::token token;
    token.type = Assembler::INSTRUCTION;
    token.value = instr.name;
    token.line = tokenizer->row;
    token.column = tokenizer->col;
    token.print();
    tokenizer->keyword_buffer = "";
    tokenizer->tokens.push_back(token);
  }
  void parseInstruction(std::shared_ptr<Tokenizer> tokenizer){

    switch(Cpu::hash(tokenizer->keyword_buffer)){
      case Cpu::instructions::ADDI.hash:
        instrToToken(Cpu::instructions::ADDI,tokenizer);
        break;
      case Cpu::instructions::ADD.hash:
        instrToToken(Cpu::instructions::ADD,tokenizer);
        break;
      case Cpu::instructions::ADDU.hash:
        instrToToken(Cpu::instructions::ADDU,tokenizer);
        break;
      case Cpu::instructions::AND.hash:
        instrToToken(Cpu::instructions::AND,tokenizer);
        break;
      case Cpu::instructions::SUB.hash:
        instrToToken(Cpu::instructions::SUB,tokenizer);
        break;
      case Cpu::instructions::SUBU.hash:
        instrToToken(Cpu::instructions::SUBU,tokenizer);
        break;
      case Cpu::instructions::LW.hash: 
        instrToToken(Cpu::instructions::LW,tokenizer);
        break;
      case Cpu::instructions::LB.hash:
        instrToToken(Cpu::instructions::LB,tokenizer);
        break;
      case Cpu::instructions::LBU.hash:
        instrToToken(Cpu::instructions::LBU,tokenizer);
        break;
      case Cpu::instructions::LHU.hash:
        instrToToken(Cpu::instructions::LHU,tokenizer);
        break;
      case Cpu::instructions::SB.hash:
        instrToToken(Cpu::instructions::SB,tokenizer);
        break;
      case Cpu::instructions::SW.hash:
        instrToToken(Cpu::instructions::SW,tokenizer);
        break;
      case Cpu::instructions::SH.hash:
        instrToToken(Cpu::instructions::SH,tokenizer);
        break;
      case Cpu::instructions::J_.hash:
        instrToToken(Cpu::instructions::J_,tokenizer);
        break;
      case Cpu::instructions::JAL.hash:
        instrToToken(Cpu::instructions::JAL,tokenizer);
        break;
      case Cpu::instructions::BEQ.hash:
        instrToToken(Cpu::instructions::BEQ,tokenizer);
        break;
      case Cpu::instructions::BNE.hash:
        instrToToken(Cpu::instructions::BNE,tokenizer);
        break;
      case Cpu::instructions::SLT.hash:
        instrToToken(Cpu::instructions::SLT,tokenizer);
        break;
      case Cpu::instructions::SLTI.hash:
        instrToToken(Cpu::instructions::SLTI,tokenizer);
        break;
      case Cpu::instructions::SLTU.hash:
        instrToToken(Cpu::instructions::SLTU,tokenizer);
        break;
      case Cpu::instructions::SLTIU.hash:
        instrToToken(Cpu::instructions::SLTIU,tokenizer);
        break;
      case Cpu::instructions::SLL.hash:
        instrToToken(Cpu::instructions::SLL,tokenizer);
        break;
      case Cpu::instructions::SRL.hash:
        instrToToken(Cpu::instructions::SRL,tokenizer);
        break;
      case Cpu::instructions::SRA.hash:
        instrToToken(Cpu::instructions::SRA,tokenizer);
        break;
      case Cpu::instructions::OR.hash:
        instrToToken(Cpu::instructions::OR,tokenizer);
        break;
      case Cpu::instructions::XOR.hash:
        instrToToken(Cpu::instructions::XOR,tokenizer);
        break;
      case Cpu::instructions::NOR.hash:
        instrToToken(Cpu::instructions::NOR,tokenizer);
        break;
      case Cpu::instructions::ANDI.hash:
        instrToToken(Cpu::instructions::ANDI,tokenizer);
        break;
      case Cpu::instructions::ORI.hash:
        instrToToken(Cpu::instructions::ORI,tokenizer);
        break;
      case Cpu::instructions::XORI.hash:
        instrToToken(Cpu::instructions::XORI,tokenizer);
        break;
      case Cpu::instructions::LUI.hash:
        instrToToken(Cpu::instructions::LUI,tokenizer);
        break;
      case Cpu::instructions::MFHI.hash:
        instrToToken(Cpu::instructions::MFHI,tokenizer);
        break;
      case Cpu::instructions::MFLO.hash:
        instrToToken(Cpu::instructions::MFLO,tokenizer);
        break;
      case Cpu::instructions::MTHI.hash:
        instrToToken(Cpu::instructions::MTHI,tokenizer);
        break;
      case Cpu::instructions::JR.hash:
        instrToToken(Cpu::instructions::JR,tokenizer);
        break;
      case Cpu::instructions::JALR.hash:
        instrToToken(Cpu::instructions::JALR,tokenizer);
        break;
      case Cpu::instructions::MULT.hash:
        instrToToken(Cpu::instructions::MULT,tokenizer);
        break;
      case Cpu::instructions::MULTU.hash:
        instrToToken(Cpu::instructions::MULTU,tokenizer);
        break;
      case Cpu::instructions::DIV.hash:
        instrToToken(Cpu::instructions::DIV,tokenizer);
        break;
      case Cpu::instructions::DIVU.hash:
        instrToToken(Cpu::instructions::DIVU,tokenizer);
        break;
      case Cpu::instructions::SYSCALL.hash:
        instrToToken(Cpu::instructions::SYSCALL,tokenizer);
        break;
      case Cpu::instructions::BREAK.hash:
        instrToToken(Cpu::instructions::BREAK,tokenizer);
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
