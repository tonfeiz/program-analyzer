#pragma once

#include "ControlFlowNode.h"
#include "Visitor.h"

#include <vector>

namespace program_analyzer {
namespace condition {
    
class ControlFlowGraph {
  // start node and end node is for convinence
  ControlFlowNodePtr start_node_;
  ControlFlowNodePtr end_node_;
 public:
  // Construct graph in constructor
  ControlFlowGraph(const std::vector<ExprASTPtr> &exprASTs);

  void accept(const Visitor &visitor);

  const ControlFlowNode &start_node() const {
    return *start_node_;
  }

  const ControlFlowNode &end_node() const {
    return *end_node_;
  }
  
 private:
  // both return constructed nodes
  std::vector<ControlFlowNodePtr> constructIfCFGNode(const std::vector<ControlFlowNodePtr> &last_nodes,
	        				     const ExprASTPtr &expr);
  std::vector<ControlFlowNodePtr> constructCFGNode(const std::vector<ControlFlowNodePtr> &last_nodes,
						   const ExprASTPtr &expr);
};

}
}
