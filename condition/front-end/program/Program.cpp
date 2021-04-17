#include "Program.h"

#include "Log.h"

#include <fstream>
#include <sstream>

namespace program_analyzer {
namespace condition {

using namespace utils;

bool Program::read(const std::string &filename) {
  // open file
  std::ifstream ifs;
  ifs.open(filename.c_str());
  if (!ifs) {
    Logger::Error("Open file failed");
    return false;
  }

  // set content
  std::stringstream ss;
  ss << ifs.rdbuf();
  content_ = ss.str();

  // close file
  ifs.close();

  return true;
}

char Program::getNextChar() {
    if (pos_ == content_.size() - 1) {
        return EOF;
    }
    return content_[pos_++];
}

}
}
