#include "PrintVisitor.h"

#include <iostream>

namespace program_analyzer {
namespace condition {
  
void PrintVisitor::visit(const ControlFlowNode &node) const {
  std::cout << node.exprAST()->type() << std::endl;  
}

}
}
