#pragma once

#include <string>
#include <memory>

namespace program_analyzer {
namespace condition {

class Program {
  std::string content_;
  int pos_ = 0;
public:
  bool read(const std::string &name);
  
  char getNextChar();
  
  void reset() {
      pos_ = 0;
  }
};

using ProgramPtr = std::shared_ptr<Program>;
}
}
