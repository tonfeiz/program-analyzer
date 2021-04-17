#include "SignStateMap.h"

#include "Log.h"

namespace program_analyzer {
namespace condition {

using namespace utils;
  
void SignStateMap::update(const std::string &name,
			 SignState state) {
  signMap_[name] = state;
}

SignState SignStateMap::get(const std::string &name) const {
  if (signMap_.find(name) != signMap_.end()) {
    return signMap_.at(name);
  }
  return Unknown;
}

void SignStateMap::merge(const StateMap &other) {
  const SignStateMap *otherMap = dynamic_cast<const SignStateMap *>(&other);
  if (!otherMap) {
    Logger::Error("Can not merge different state map!");
    return ;
  }
  
  for (auto it = otherMap->signMap_.begin(); it != otherMap->signMap_.end(); ++it) {
    if (signMap_.find(it->first) != signMap_.end()) {
      if (signMap_[it->first] != otherMap->get(it->first)) {
	update(it->first, SignState());
      }
    } else {
      update(it->first, it->second);
    }
  }
}
  
std::ostream &operator<<(std::ostream &os, const SignStateMap &signStateMap) {
  for (auto it = signStateMap.signMap_.begin(); it != signStateMap.signMap_.end(); ++it) {
    os << it->first << ":" << it->second << "\n";
  }
  return os;
}

}
}
