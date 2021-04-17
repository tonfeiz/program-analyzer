#pragma once

#include "Program.h"

#include <memory>
#include <string>

namespace program_analyzer {
namespace straight {

class Lexer {
  std::string identifier_;
  double num;
  
  int currTok_;
  int lastTok_;
  int lastChar_ = ' ';
  
  std::unique_ptr<Program> program_;
  
 public:
  Lexer(std::unique_ptr<Program> program) : program_(std::move(program)) {}

  int getTok();

  const std::string &identifier() const {
    return identifier_;
  }
  
  double number() const {
    return num;
  }

  int currentTok() const {
    return currTok_;
  }

  int lastTok() const {
    return lastTok_;
  }
 private:
  int getTokCore();
  // Identifier: [a-zA-Z][a-zA-Z0-9]*
  int getIdentifier();
  // Number: [0-9]+
  int getNumber();
  
};

// The lexer return tokens [0-255] if it is an unknown character, otherwise one of these for known things.
enum Token {
  TokEof = -1,

  //primary
  TokIdentifier = -2,
  TokNumber = -3,
};

}
}
