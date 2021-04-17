#include "SignStateMap.h"

namespace program_analyzer {
namespace straight {

void SignStateMap::update(const std::string &name,
			 SignState state) {
  signMap_[name] = state;
}

SignState SignStateMap::get(const std::string &name) {
  return signMap_[name];
}

std::ostream &operator<<(std::ostream &os, const SignStateMap &signStateMap) {
  for (auto it = signStateMap.signMap_.begin(); it != signStateMap.signMap_.end(); ++it) {
    os << it->first << ":" << it->second << "\n";
  }
  return os;
}

}
}
