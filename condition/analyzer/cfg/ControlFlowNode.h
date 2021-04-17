#pragma once

#include "ExprAST.h"
#include "StateMap.h"

#include <memory>
#include <vector>

namespace program_analyzer {
namespace condition {

class ControlFlowNode;
using ControlFlowNodePtr = std::shared_ptr<ControlFlowNode>;
 
class ControlFlowNode {
  std::vector<ControlFlowNodePtr> in_;
  std::vector<ControlFlowNodePtr> out_;
  ExprASTPtr exprAST_;
  StateMapPtr stateMap_;
  bool visited_ = false;
 public:
  ControlFlowNode() : exprAST_(std::make_shared<ExprAST>()) {}
  ControlFlowNode(const ExprASTPtr &exprAST) : exprAST_(exprAST) {}

  void add_out(const ControlFlowNodePtr &node) {
    out_.push_back(node);
  }

  void add_in(const ControlFlowNodePtr &node) {
    in_.push_back(node);
  }

  void setStateMap(const StateMapPtr &stateMap) {
    stateMap_ = stateMap;
  }

  const StateMapPtr &stateMap() const {
    return stateMap_;
  }
  
  const std::vector<ControlFlowNodePtr> &out() const {
    return out_;
  }

  const std::vector<ControlFlowNodePtr> &in() const {
    return in_;
  }

  const ExprASTPtr &exprAST() const {
    return exprAST_;
  }

  bool visited() const {
    return visited_;
  }

  void set_visited(bool visited) {
    visited_ = visited;
  }
};

}
}
