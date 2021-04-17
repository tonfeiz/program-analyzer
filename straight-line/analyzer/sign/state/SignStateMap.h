#pragma once

#include <map>
#include <string>
#include <iostream>

#include "SignState.h"
#include "StateMap.h"

namespace program_analyzer {
namespace straight {

class SignStateMap : public StateMap {
  std::map<std::string, SignState> signMap_;
public:

  void update(const std::string &name, SignState s);
  SignState get(const std::string &name);

  // TODO: better ways to output
  friend std::ostream &operator<<(std::ostream &os, const SignStateMap &signMap);

};

}
}
