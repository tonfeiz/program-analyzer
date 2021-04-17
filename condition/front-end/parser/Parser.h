#pragma once

#include <map>
#include <memory>

#include "Lexer.h"
#include "ExprAST.h"

namespace program_analyzer {
namespace condition {

class Parser {
  LexerPtr lexer_;
  
  std::map<char, int> binOpPrecedence_;

public:
  Parser(LexerPtr lexer, const std::map<char, int> &binOpPrecedence) : lexer_(lexer),
		       					      binOpPrecedence_(binOpPrecedence) {}
 public:
  // numberexpr ::= number
  ExprASTPtr parseNumberExpr(bool positive = true);

  // identifierexpr ::= identifier
  ExprASTPtr parseIdentifierExpr();

  // ifexpr ::= if binExp exp
  IfExprASTPtr parseIfExpr();

  // primary
  //   ::= identifierexpr
  //   ::= numberexpr
  //   ::= ifexpr
  ExprASTPtr parsePrimary();

  // binoprhs ::= ('+' primary)*
  ExprASTPtr parseBinopRHS(int exprPrec,
			   ExprASTPtr lhs);

  // expression ::= primary binoprhs
  ExprASTPtr parseExpression();

  // toplevelexpr ::= expression
  ExprASTPtr parseTopLevelExpr();
 private:
  int getTokPrecedence(int token);
  
};

using ParserPtr = std::shared_ptr<Parser>;
  
}
}
