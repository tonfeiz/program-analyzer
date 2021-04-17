#include "SignAnalyzer.h"

#include "Log.h"

namespace program_analyzer {
namespace straight {

using namespace utils;

void SignAnalyzer::analyze(const std::vector<ExprASTPtr> &exprASTs) {
  // Every expression must be "assign" expression
  for (const ExprASTPtr &exprAst : exprASTs) {
    BinaryExprAST *equalAST = toAssignExp(exprAst.get());
    if (!equalAST) {
      // error
      return ;
    }

    // Every LHS must be variable
    VariableExprAST *varAST = toVarExp(equalAST->lhs().get());
    if (!varAST) {
      // error
      return ;
    }
    
    // Every RHS must be variable or number or OpExp
    SignState state = calcExprState(equalAST->rhs().get());
    
    stateMap_.update(varAST->name(), state);
  }
}

BinaryExprAST* SignAnalyzer::toAssignExp(ExprAST *exprAST) {
  BinaryExprAST *binAST = dynamic_cast<BinaryExprAST *>(exprAST);
  if (!binAST || binAST->op() != '=') {
    Logger::Error("Expression is not assignment");
    return nullptr;
  }
  return binAST;
}

VariableExprAST *SignAnalyzer::toVarExp(ExprAST *exprAST) {
  VariableExprAST *varAST = dynamic_cast<VariableExprAST *>(exprAST);
  if (!varAST || varAST->type() != Variable) {
    Logger::Error("Expression is not variable");
    return nullptr;
  }
  return varAST;
}

SignState SignAnalyzer::calcExprState(ExprAST *exprAST) {
  // number or variable or OpExp(+, -, *, etc...)
  switch (exprAST->type()) {
  case Number:
    {
      NumberExprAST *numAST = dynamic_cast<NumberExprAST *>(exprAST);
      return SignState(numAST->num());
    }
  case Variable:
    {
      VariableExprAST *varAST = dynamic_cast<VariableExprAST *>(exprAST); 
      return stateMap_.get(varAST->name());
    }
  case BinaryExpr:
    {
      BinaryExprAST *binAST = dynamic_cast<BinaryExprAST *>(exprAST);
      return calcBinaryExprState(binAST);
    }
  default:
    Logger::Error("Unknown expression type");
    return SignState();
  }
}

SignState SignAnalyzer::calcBinaryExprState(BinaryExprAST *binAST) {
  // only +-* is allowed
  switch (binAST->op()) {
  case '+':
    return getState(binAST->lhs().get()) + getState(binAST->rhs().get());
  case '-':
    return getState(binAST->lhs().get()) - getState(binAST->rhs().get());
  case '*':
    return getState(binAST->lhs().get()) * getState(binAST->rhs().get());
  default:
    Logger::Error("Unknown binary op type");
    return SignState();
  }
}

SignState SignAnalyzer::getState(ExprAST *exp) {
  switch (exp->type()) {
  case Variable:
    {
      VariableExprAST *varExp = dynamic_cast<VariableExprAST *>(exp);
      return stateMap_.get(varExp->name());
    }
  case Number:
    {
      NumberExprAST *numExp = dynamic_cast<NumberExprAST *>(exp);
      return SignState(numExp->num());
    }
  default:
    Logger::Error("Get state besides variable and number");
    return SignState();
  }
}

}
}
