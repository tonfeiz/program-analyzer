#pragma once

#include "ControlFlowNode.h"
#include "StateMap.h"
#include "SignStateMap.h"

namespace program_analyzer {
namespace condition {
    
class SignStateMerger {
 public:
  SignStateMapPtr merge(const ControlFlowNode &node);
 private:
  SignStateMapPtr merge(const std::vector<ControlFlowNodePtr> &states);
};

using SignStateMergerPtr = std::shared_ptr<SignStateMerger>;
 
}
}
