#include "Parser.h"

#include <cstdlib>
#include <utility>

#include "Log.h"

namespace program_analyzer {
namespace straight {

using namespace utils;

std::unique_ptr<ExprAST> Parser::parseNumberExpr(bool positive) {
  auto result = std::make_unique<NumberExprAST>(positive ?
						lexer_->number() : -1 * lexer_->number());
  // get next token to continue parse
  lexer_->getTok();
  return std::move(result);
}

std::unique_ptr<ExprAST> Parser::parseIdentifierExpr() {
  std::string id_name = lexer_->identifier();
  lexer_->getTok();
  return std::make_unique<VariableExprAST>(id_name);
}

std::unique_ptr<ExprAST> Parser::parsePrimary() {
  switch (lexer_->currentTok()) {
  default:
    // TODO: Ugly parse negative number method.
    if (lexer_->currentTok() == '-' && lexer_->lastTok() == '=') {
	lexer_->getTok();
        return parseNumberExpr(false);
    }
    Logger::Error("Unknown token when expecting an expression");
    return nullptr;
  case TokIdentifier:
    return parseIdentifierExpr();
  case TokNumber:
    return parseNumberExpr();
  case TokEof:
    return nullptr;
  }
}

std::unique_ptr<ExprAST> Parser::parseExpression() {
  auto lhs = parsePrimary();
  if (!lhs)
    return nullptr;

  return parseBinopRHS(0, std::move(lhs));
}

std::unique_ptr<ExprAST> Parser::parseBinopRHS(int exprPrec,
					 std::unique_ptr<ExprAST> lhs) {
  // If this is a binop, find its precedence. 
  while (true) {
    int tokPrec = getTokPrecedence(lexer_->currentTok());

    // If this is a binop that binds at least as tightly as the current binop,
    // consume it, otherwise we are done
    if (tokPrec < exprPrec)
      return lhs;

    // Okay, we know this is a binop
    int binop = lexer_->currentTok();
    // Get next token to continue parse
    lexer_->getTok(); 

    // Parse the primary expression after the binary operator
    auto rhs = parsePrimary();
    if (!rhs)
      return nullptr;

    // If binop binds less tightly with rhs than the operator after rhs,
    // let the pending operator take rhs as its lhs
    int nextPrec = getTokPrecedence(lexer_->currentTok());
    if (tokPrec < nextPrec) {
      rhs = parseBinopRHS(tokPrec + 1, std::move(rhs));
      if (!rhs)
	return nullptr;
    }

    // Merge lhs/rhs
    lhs = std::make_unique<BinaryExprAST>(binop, std::move(lhs), std::move(rhs));
  }
}

int Parser::getTokPrecedence(int token) {
  if (!isascii(token))
    return -1;

  // Make sure it's a declared binop
  int tokPrec = binOpPrecedence_[token];
  if (tokPrec <= 0)
    return -1;
  return tokPrec;
}

std::unique_ptr<ExprAST> Parser::parseTopLevelExpr() {
  return parseExpression();
}

}
}
