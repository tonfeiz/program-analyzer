#pragma once

#include <map>
#include <memory>

#include "Lexer.h"
#include "ExprAST.h"

namespace program_analyzer {
namespace straight {

class Parser {
  std::unique_ptr<Lexer> lexer_;
  
  std::map<char, int> binOpPrecedence_;

public:
  Parser(std::unique_ptr<Lexer> lexer, std::map<char, int> binOpPrecedence) : lexer_(std::move(lexer)),
									       binOpPrecedence_(binOpPrecedence) {}
 public:
  // numberexpr ::= number
  std::unique_ptr<ExprAST> parseNumberExpr(bool positive = true);

  // identifierexpr ::= identifier
  std::unique_ptr<ExprAST> parseIdentifierExpr();

  // primary
  //   ::= identifierexpr
  //   ::= numberexpr
  std::unique_ptr<ExprAST> parsePrimary();

  // binoprhs ::= ('+' primary)*
  std::unique_ptr<ExprAST> parseBinopRHS(int exprPrec,
					   std::unique_ptr<ExprAST> lhs);

  // expression ::= primary binoprhs
  std::unique_ptr<ExprAST> parseExpression();

  // toplevelexpr ::= expression
  std::unique_ptr<ExprAST> parseTopLevelExpr();
 private:
  int getTokPrecedence(int token);
  
};

}
}
