#pragma once

#include "Visitor.h"

namespace program_analyzer {
namespace condition {
    
class PrintVisitor : public Visitor {
public:
  void visit(ControlFlowNodePtr node) const override;
};

}
}
