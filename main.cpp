#include <iostream>
#include <queue>
#include <string>

#include "ast.hpp"
#include "builder.hpp"

void print_queue(std::queue<Token> q) {
  while (!q.empty()) {
    std::cout << q.front() << " ";
    q.pop();
  }
  std::cout << std::endl;
}

int main(int argc, char* argv[]) {
  // string expression = argv[1];

  Tree* AST = Builder().BuildTree("math.txt");
  float result = AST->evaluate();
  std::cout << "result = " << result << std::endl;

  return 0;
}