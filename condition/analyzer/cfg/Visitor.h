#pragma once

#include "ControlFlowNode.h"

namespace program_analyzer {
namespace condition {
  
class Visitor {
 public:
  virtual void visit(ControlFlowNodePtr node) const = 0;
};

using VisitorPtr = std::shared_ptr<Visitor>;

}
}
