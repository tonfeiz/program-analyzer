#include "SignAnalyzer.h"

#include "ExprASTUtils.h"
#include "Log.h"

namespace program_analyzer {
namespace condition {

using namespace utils;

void SignAnalyzer::visit(ControlFlowNodePtr node) const {
  SignStateMapPtr stateMap = merger->merge(*node);

  updateStateMap(node->exprAST(), stateMap);

  node->setStateMap(stateMap);
}

void SignAnalyzer::updateStateMap(const ExprASTPtr &expr, SignStateMapPtr stateMap) const {
  BinaryExprASTPtr binAST = ExprASTUtils::toBinaryAST(expr);
  if (!binAST) {
    // error
    return ;
  }
  
  if (isAssign(binAST->op())) {
    updateAssignStateMap(binAST, stateMap);
  } else if (isCmp(binAST->op())) {
    updateCmpStateMap(binAST, stateMap);
  } else {
    Logger::Error("Operation not found");
  }
}

bool SignAnalyzer::isAssign(char op) const {
  return '=' == op;
}

bool SignAnalyzer::isCmp(char op) const {
  return '<' == op || '>' == op;
}
  
void SignAnalyzer::updateAssignStateMap(const BinaryExprASTPtr &equalAST, SignStateMapPtr stateMap) const {
  // Every LHS must be variable
  VariableExprASTPtr varAST = ExprASTUtils::toVariableAST(equalAST->lhs());
  if (!varAST) {
    // error
    return ;
  }
  
  // Every RHS must be variable or number or OpExp
  SignState state = calcExprState(equalAST->rhs(), stateMap);
  
  stateMap->update(varAST->name(), state);
}
  
SignState SignAnalyzer::calcExprState(const ExprASTPtr &exprAST, SignStateMapPtr stateMap) const {
  // number or variable or OpExp(+, -, *, etc...)
  switch (exprAST->type()) {
  case Number:
    {
      NumberExprASTPtr numAST = ExprASTUtils::toNumberAST(exprAST);
      return SignState(numAST->num());
    }
  case Variable:
    {
      VariableExprASTPtr varAST = ExprASTUtils::toVariableAST(exprAST); 
      return stateMap->get(varAST->name());
    }
  case BinaryExpr:
    {
      BinaryExprASTPtr binAST = ExprASTUtils::toBinaryAST(exprAST);
      return calcBinaryExprState(binAST, stateMap);
    }
  default:
    Logger::Error("Unknown expression type");
    return SignState();
  }
}

SignState SignAnalyzer::calcBinaryExprState(const BinaryExprASTPtr &binAST, SignStateMapPtr stateMap) const {
  // only +-* is allowed
  switch (binAST->op()) {
  case '+':
    return getState(binAST->lhs(), stateMap) + getState(binAST->rhs(), stateMap);
  case '-':
    return getState(binAST->lhs(), stateMap) - getState(binAST->rhs(), stateMap);
  case '*':
    return getState(binAST->lhs(), stateMap) * getState(binAST->rhs(), stateMap);
  default:
    Logger::Error("Unknown binary op type");
    return SignState();
  }
}

SignState SignAnalyzer::getState(const ExprASTPtr &exp, SignStateMapPtr stateMap) const {
  switch (exp->type()) {
  case Variable:
    {
      VariableExprASTPtr varExp = ExprASTUtils::toVariableAST(exp);
      return stateMap->get(varExp->name());
    }
  case Number:
    {
      NumberExprASTPtr numExp = ExprASTUtils::toNumberAST((exp));
      return SignState(numExp->num());
    }
  default:
    Logger::Error("Get state besides variable and number");
    return SignState();
  }
}

void SignAnalyzer::updateCmpStateMap(const BinaryExprASTPtr &binAST, SignStateMapPtr stateMap) const {
  // Do nothing for compare expression
  return ;
}
  
}
}
