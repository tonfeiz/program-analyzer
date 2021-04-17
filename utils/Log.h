#pragma once

#include <memory>
#include <cstdio>

namespace program_analyzer {
namespace utils {

class Logger {
 public:
  static void Error(const char *str) {
    fprintf(stderr, "Error: %s\n", str);
  }
};

}
}
