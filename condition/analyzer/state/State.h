#pragma once

#include <memory>

namespace program_analyzer {
namespace condition {

class State {
public:
  virtual ~State() = default;
};

using StatePtr = std::shared_ptr<State>;
}
}
