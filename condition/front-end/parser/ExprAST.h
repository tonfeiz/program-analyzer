#pragma once

#include <memory>

namespace program_analyzer {
namespace condition {

// Used for tagged class, which is not very good?
enum ExprType {
  Number,
  Variable,
  BinaryExpr,
  IfExpr,
  Empty
};

// ExprAST - Base class for all expression nodes. 
class ExprAST {
 public:
  virtual ExprType type() {
    return Empty;
  }
  virtual ~ExprAST() = default;
};
using ExprASTPtr = std::shared_ptr<ExprAST>;
  
// NumberExprAST - Expression class for numeric literals like "1.0". 
class NumberExprAST : public ExprAST {
  double val_;
 public:
  NumberExprAST(double val) : val_(val) {}
  
  ExprType type() override {
    return Number;
  }

  double num() const {
    return val_;
  }
};
using NumberExprASTPtr = std::shared_ptr<NumberExprAST>;
  
// VariableExprAST - Expression class for referencing a variable, like "a".
class VariableExprAST : public ExprAST {
  std::string name_;
 public:
  VariableExprAST(const std::string &name) : name_(name) {}
  
  ExprType type() override {
    return Variable;
  }

  const std::string &name() const {
    return name_;
  }
};
using VariableExprASTPtr = std::shared_ptr<VariableExprAST>;
  
// BinaryExprAST - Expression class for a binary operator
class BinaryExprAST : public ExprAST {
  char op_;
  ExprASTPtr lhs_, rhs_;
 public:
  BinaryExprAST(char op, ExprASTPtr lhs,
		ExprASTPtr rhs)
    : op_(op), lhs_(lhs), rhs_(rhs) {}
  
  ExprType type() override {
    return BinaryExpr;
  }

  char op() const {
    return op_;
  }

  const ExprASTPtr &lhs() const {
    return lhs_;
  }

  const ExprASTPtr &rhs() const {
    return rhs_;
  }
};
using BinaryExprASTPtr = std::shared_ptr<BinaryExprAST>;
  
// IfExprAST - Expression class for "if" expression
class IfExprAST : public ExprAST {
  BinaryExprASTPtr condition_;
  ExprASTPtr body_;  
 public:
  IfExprAST(BinaryExprASTPtr condition, 
            ExprASTPtr body) : condition_(condition), body_(body) {}

  ExprType type() override {
    return IfExpr;
  }

  const BinaryExprASTPtr &condition() const {
    return condition_;
  }

  const ExprASTPtr &body() const {
    return body_;
  }

  BinaryExprASTPtr mutable_condition() {
    return condition_;
  }

  ExprASTPtr mutable_body() {
    return body_;
  }
};
using IfExprASTPtr = std::shared_ptr<IfExprAST>;



}
}
