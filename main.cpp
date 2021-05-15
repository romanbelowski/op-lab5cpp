#include <iostream>
#include <queue>
#include <string>

#include "parser.hpp"
#include "shunting-yard.hpp"
#include "token.hpp"
#include "tokens.hpp"

// using namespace std;

void print_queue(std::queue<Token> q) {
  while (!q.empty()) {
    std::cout << q.front() << " ";
    q.pop();
  }
  std::cout << std::endl;
}

int main(int argc, char* argv[]) {
  // string expression = argv[1];
  Parser parser = Parser();

  //     std::string expression = "a= 2*-(1 + 1)";
  // ShuntingYard yard = ShuntingYard();
  // std::queue<Token> queue = yard.Parse(expression);

  // std::cout << "Reverse polish notation:" << std::endl;
  // print_queue(queue);

  Tree tree = Tree(parser.Read("math.txt"));
  float result = tree.evaluate();
  std::cout << "result = " << result << std::endl;
  // tree.add_row(queue);
  // tree.evaluate();

  return 0;
}