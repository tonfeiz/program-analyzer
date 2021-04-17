#include "front-end/parser/Parser.h"
#include "analyzer/sign/SignAnalyzer.h"

#include <iostream>

using namespace program_analyzer::straight;

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "usage: ProgramAnalyzer [program file path]" << std::endl;
    return 0;
  }
  
  // read program
  std::unique_ptr<Program> program = std::make_unique<Program>();
  if (!program->read(argv[1])) {
    return -1;
  }

  // Set lexer to the first token
  std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(std::move(program));
  lexer->getTok();

  // set parser
  std::unique_ptr<Parser> parser = std::make_unique<Parser>(std::move(lexer),
							    std::map<char, int>{
							      {'=', 10}, 
							      {'+', 20},
							      {'-', 20},
							      {'*', 40}
							    });

  // set analyzer
  std::unique_ptr<SignAnalyzer> signAnalyzer = std::make_unique<SignAnalyzer>();

  // generate ASTs from parser
  std::vector<ExprASTPtr> exprASTs;
  while (true) {
    if (auto exprAST = parser->parseTopLevelExpr()) {
      exprASTs.push_back(std::move(exprAST));
    } else {
      break;
    }
  }

  // analyze and output
  signAnalyzer->analyze(exprASTs);
  std::cout << signAnalyzer->state();
}
