#pragma once

#include <memory>

namespace program_analyzer {
namespace straight {

// Used for tagged class, which is not very good?
enum ExprType {
  Number,
  Variable,
  BinaryExpr
};

// ExprAST - Base class for all expression nodes. 
class ExprAST {
 public:
  virtual ExprType type() = 0;
  virtual ~ExprAST() = default;
};

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

// BinaryExprAST - Expression class for a binary operator
class BinaryExprAST : public ExprAST {
  char op_;
  std::unique_ptr<ExprAST> lhs_, rhs_;
 public:
  BinaryExprAST(char op, std::unique_ptr<ExprAST> lhs,
		std::unique_ptr<ExprAST> rhs)
    : op_(op), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}
  
  ExprType type() override {
    return BinaryExpr;
  }

  char op() const {
    return op_;
  }

  const std::unique_ptr<ExprAST> &lhs() const {
    return lhs_;
  }

  const std::unique_ptr<ExprAST> &rhs() const {
    return rhs_;
  }
};

using ExprASTPtr = std::unique_ptr<ExprAST>;

}
}
