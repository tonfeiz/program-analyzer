#pragma once

#include <string>

namespace program_analyzer {
namespace straight {

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

}
}
