#pragma once

#include "Program.h"

#include <memory>
#include <string>
#include <unordered_set>

namespace program_analyzer {
namespace condition {

class Lexer {
  std::string identifier_;
  std::string keyword_;
  double num;
  
  int currTok_;
  int lastTok_;
  int lastChar_ = ' ';
  
  ProgramPtr program_;

  std::unordered_set<std::string> keywords_ = {"if"};
  
 public:
  Lexer(ProgramPtr program) : program_(program) {}

  int getTok();

  const std::string &identifier() const {
    return identifier_;
  }

  const std::string &keyword() const {
    return keyword_;
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
  int getIdentifierOrKeyword();
  // Keyword: if
  int getKeyword();
  // Number: [0-9]+
  int getNumber();
  
};
using LexerPtr = std::shared_ptr<Lexer>;
  
// The lexer return tokens [0-255] if it is an unknown character, otherwise one of these for known things.
enum Token {
  TokEof = -1,

  //primary
  TokIdentifier = -2,
  TokNumber = -3,

  TokIf = -4,
};

}
}
