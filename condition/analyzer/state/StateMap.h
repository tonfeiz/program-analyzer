#pragma once

#include <memory>

namespace program_analyzer {
namespace condition {

class StateMap {
public:
  virtual ~StateMap() = default;
  virtual void merge(const StateMap &other) = 0;
};

using StateMapPtr = std::shared_ptr<StateMap>;
  
}
}
