#include <iostream>
#include <queue>
#include <string>

#include "ast.hpp"
#include "builder.hpp"

int main(int argc, char* argv[]) {
  Tree* AST = Builder().BuildTree(argv[1]);
  AST->print(0);
  float result = AST->evaluate();
  std::cout << "result = " << result << std::endl;

  return 0;
}