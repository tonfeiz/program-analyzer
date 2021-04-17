#include "SignStateMerger.h"

namespace program_analyzer {
namespace condition {
    
SignStateMapPtr SignStateMerger::merge(const ControlFlowNode &node) {
  return merge(node.in());
}

SignStateMapPtr SignStateMerger::merge(const std::vector<ControlFlowNodePtr> &nodes) {
  SignStateMapPtr signStateMap = std::make_shared<SignStateMap>();
  for (const auto &node : nodes) {
    signStateMap->merge(*(node->stateMap()));
  }
  return signStateMap;
}

}
}
