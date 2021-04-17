#pragma once

#include <map>
#include <vector>

#include "ExprAST.h"
#include "SignStateMap.h"

namespace program_analyzer {
namespace straight {

class SignAnalyzer {
  SignStateMap stateMap_;
 public:
  void analyze(const std::vector<ExprASTPtr> &exprASTs);

  const SignStateMap &state() const {
    return stateMap_;
  }
  
 private:
  BinaryExprAST* toAssignExp(ExprAST *exprAST);
  VariableExprAST *toVarExp(ExprAST *exprAST);
  SignState calcExprState(ExprAST *exprAST);
  SignState calcBinaryExprState(BinaryExprAST *binExprAST);
  SignState getState(ExprAST *exp);
};

}
}
