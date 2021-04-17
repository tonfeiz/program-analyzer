#include "ExprASTUtils.h"

#include "Log.h"

namespace program_analyzer {
namespace condition {

using namespace utils;
  
IfExprASTPtr ExprASTUtils::toIfAST(const ExprASTPtr &expr) {
  if (expr->type() != IfExpr) {
    Logger::Error("Transfered expression is not if expression");
    return nullptr;
  }
  return std::dynamic_pointer_cast<IfExprAST>(expr);
}
  
BinaryExprASTPtr ExprASTUtils::toBinaryAST(const ExprASTPtr &expr) {
  if (expr->type() != BinaryExpr) {
    Logger::Error("Transfered expression is not binary expression");
    return nullptr;
  }
  return std::dynamic_pointer_cast<BinaryExprAST>(expr);
}

VariableExprASTPtr ExprASTUtils::toVariableAST(const ExprASTPtr &expr) {
  if (expr->type() != Variable) {
    Logger::Error("Transfered expression is not variable expression");
    return nullptr;
  }
  return std::dynamic_pointer_cast<VariableExprAST>(expr);
}

  
NumberExprASTPtr ExprASTUtils::toNumberAST(const ExprASTPtr &expr) {
  if (expr->type() != Number) {
    Logger::Error("Transfered expression is not number expression");
    return nullptr;
  }
  return std::dynamic_pointer_cast<NumberExprAST>(expr);
}
  
}
}
