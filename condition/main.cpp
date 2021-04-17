#include "analyzer/cfg/ControlFlowGraph.h"
#include "analyzer/cfg/PrintVisitor.h"
#include "analyzer/sign/SignAnalyzer.h"
#include "front-end/parser/Parser.h"

#include <iostream>

using namespace program_analyzer::condition;

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "usage: ProgramAnalyzer [program file path]" << std::endl;
    return 0;
  }
  
  // read program
  ProgramPtr program = std::make_shared<Program>();
  if (!program->read(argv[1])) {
    return -1;
  }

  // Set lexer to the first token
  LexerPtr lexer = std::make_shared<Lexer>(program);
  lexer->getTok();

  // set parser
  ParserPtr parser = std::make_shared<Parser>(lexer,
					    std::map<char, int>{
							      {'=', 10},
							      {'<', 15},
							      {'>', 15},
							      {'+', 20},
							      {'-', 20},
							      {'*', 40}
							    });


  // generate ASTs from parser
  std::vector<ExprASTPtr> exprASTs;
  while (true) {
    if (auto exprAST = parser->parseTopLevelExpr()) {
      exprASTs.push_back(exprAST);
    } else {
      break;
    }
  }

  VisitorPtr signAnalyzer = std::make_shared<SignAnalyzer>();
  ControlFlowGraph cfg(exprASTs);
  cfg.accept(*signAnalyzer);

  SignStateMapPtr finalStateMap = std::dynamic_pointer_cast<SignStateMap>(cfg.end_node().stateMap());
  std::cout << *finalStateMap << std::endl;
}
