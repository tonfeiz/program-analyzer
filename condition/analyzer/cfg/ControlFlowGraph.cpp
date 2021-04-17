#include "ControlFlowGraph.h"

#include "ExprASTUtils.h"

#include <deque>

namespace program_analyzer {
namespace condition {
  
ControlFlowGraph::ControlFlowGraph(const std::vector<ExprASTPtr> &exprASTs) {
  start_node_ = std::make_shared<ControlFlowNode>();
  end_node_ = std::make_shared<ControlFlowNode>();

  // start with start node
  std::vector<ControlFlowNodePtr> last_nodes = {start_node_};

  for (auto &expr : exprASTs) {
    switch (expr->type()) {
    case IfExpr:
      last_nodes = constructIfCFGNode(last_nodes, expr);
      break;
    default:
      last_nodes = constructCFGNode(last_nodes, expr);
      break;
    }
  }

  // last node should point to end node
  for (auto node : last_nodes) {
    node->add_out(end_node_);
    end_node_->add_in(node);
  }
}

std::vector<ControlFlowNodePtr> ControlFlowGraph::constructIfCFGNode(const std::vector<ControlFlowNodePtr> &last_nodes,
								     const ExprASTPtr &expr) {
  IfExprASTPtr ifExpr = ExprASTUtils::toIfAST(expr);
  
  // If expression should construct two nodes.
  // Condition node points to body and next expression
  // Body node points to next expression
  ControlFlowNodePtr bodyNode = std::make_shared<ControlFlowNode>(ifExpr->body());
  
  ControlFlowNodePtr conditionNode = std::make_shared<ControlFlowNode>(ifExpr->condition());
  conditionNode->add_out(bodyNode);
  bodyNode->add_in(conditionNode);
  
  for (auto node : last_nodes) {
    node->add_out(conditionNode);
    conditionNode->add_in(node);
  }

  return {conditionNode, bodyNode};
}

std::vector<ControlFlowNodePtr> ControlFlowGraph::constructCFGNode(const std::vector<ControlFlowNodePtr> &last_nodes,
								   const ExprASTPtr &expr) {
  ControlFlowNodePtr node = std::make_shared<ControlFlowNode>(expr);

  for (auto last_node : last_nodes) {
    last_node->add_out(node);
    node->add_in(last_node);
  }

  return {node};
}

void ControlFlowGraph::accept(const Visitor &visitor) {
  // traverse graph
  // using bfs
  std::deque<ControlFlowNodePtr> queue;
  queue.push_back(start_node_);
  while (!queue.empty()) {
    ControlFlowNodePtr node = queue.front();
    queue.pop_front();
    visitor.visit(node);
    node->set_visited(true);
    for (const auto &n : node->out()) {
      // If next node's input has not been visited, it shouldn't be added to the queue
      // Otherwise the node may be visited multiple times
      bool all_in_visited = true;
      for (const auto &in : n->in()) {
	if (!in->visited()) {
	  all_in_visited = false;
	  break;
	}
      }
      if (all_in_visited) {
	queue.push_back(n);
      }

    }
  }
}

}
}
