#pragma once

#include <map>
#include <memory>
#include <string>
#include <iostream>

#include "SignState.h"
#include "StateMap.h"

namespace program_analyzer {
namespace condition {

class SignStateMap : public StateMap {
  std::map<std::string, SignState> signMap_;
public:
  void merge(const StateMap &other) override;
  
  void update(const std::string &name, SignState s);
  SignState get(const std::string &name) const;

  // TODO: better ways to output
  friend std::ostream &operator<<(std::ostream &os, const SignStateMap &signMap);

};

using SignStateMapPtr = std::shared_ptr<SignStateMap>;
  
}
}
