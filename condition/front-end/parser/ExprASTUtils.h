#pragma once

#include "ExprAST.h"

namespace program_analyzer {
namespace condition {
  
class ExprASTUtils {
 public:
  static IfExprASTPtr toIfAST(const ExprASTPtr &expr);

  static BinaryExprASTPtr toBinaryAST(const ExprASTPtr &expr);

  static VariableExprASTPtr toVariableAST(const ExprASTPtr &expr);

  static NumberExprASTPtr toNumberAST(const ExprASTPtr &expr);
};

}
}
