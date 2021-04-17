#include "Lexer.h"

#include <cstdlib>
#include <cstdio>

namespace program_analyzer {
namespace straight {

int Lexer::getTok() {
  lastTok_ = currTok_;
  currTok_ = getTokCore();
  return currTok_;
}

int Lexer::getTokCore() {
  // Skip any whitespace
  while (isspace(lastChar_))
    lastChar_ = program_->getNextChar();

  if (isalpha(lastChar_)) {
    return getIdentifier();
  }

  if (isdigit(lastChar_)) {
    return getNumber();
  }

  // Check for end of file. Don't eat the EOF
  if (lastChar_ == EOF)
    return TokEof;

  // Otherwise, just return the character as its ascii value.
  int ThisChar = lastChar_;
  lastChar_ = program_->getNextChar();
  return ThisChar;
}

int Lexer::getIdentifier() {
  identifier_ = lastChar_;
  while (isalnum((lastChar_ = program_->getNextChar())))
    identifier_ += lastChar_;

  return TokIdentifier;
}

int Lexer::getNumber() {
  std::string numStr;
  do {
    numStr += lastChar_;
    lastChar_ = program_->getNextChar();
  } while (isdigit(lastChar_));

  num = strtod(numStr.c_str(), nullptr);
  return TokNumber;
}

}
}
