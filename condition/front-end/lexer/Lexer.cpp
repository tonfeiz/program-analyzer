#include "Lexer.h"

#include "Log.h"

#include <cstdlib>
#include <cstdio>

namespace program_analyzer {
namespace condition {

using namespace utils;

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
    return getIdentifierOrKeyword();
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

int Lexer::getIdentifierOrKeyword() {
  // Get complete token first, may be identifier or keyword
  std::string tokenStr;
  tokenStr = lastChar_;
  while (isalnum((lastChar_ = program_->getNextChar())))
    tokenStr += lastChar_;

  // get keyword
  if (keywords_.find(tokenStr) != keywords_.end()) {
    keyword_ = tokenStr;
    return getKeyword();
  }

  // get identifier
  identifier_ = tokenStr;
  return TokIdentifier;
}

int Lexer::getKeyword() {
  if (keyword_ == "if") {
    return TokIf;
  }
  Logger::Error("Unknown keyword");
  return -1000;
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
