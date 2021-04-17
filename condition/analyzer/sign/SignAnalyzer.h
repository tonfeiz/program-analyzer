#pragma once

#include "ControlFlowNode.h"
#include "ExprAST.h"
#include "SignStateMap.h"
#include "SignStateMerger.h"
#include "Visitor.h"

#include <map>
#include <vector>

namespace program_analyzer {
namespace condition {

class SignAnalyzer : public Visitor {
 public:
  void visit(ControlFlowNodePtr node) const override;

 private:
  void updateStateMap(const ExprASTPtr &expr, SignStateMapPtr stateMap) const;
  bool isAssign(char op) const;
  bool isCmp(char op) const;
  void updateAssignStateMap(const BinaryExprASTPtr &expr, SignStateMapPtr stateMap) const;
  void updateCmpStateMap(const BinaryExprASTPtr &expr, SignStateMapPtr stateMap) const;
  SignState calcExprState(const ExprASTPtr &exprAST, SignStateMapPtr stateMap) const;
  SignState calcBinaryExprState(const BinaryExprASTPtr &binExprAST, SignStateMapPtr stateMap) const;
  SignState getState(const ExprASTPtr &exp, SignStateMapPtr stateMap) const;

  SignStateMergerPtr merger = std::make_shared<SignStateMerger>();
};

}
}
