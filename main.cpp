#include <iostream>
#include <string>

#include "shunting-yard.hpp"
#include "token.hpp"

void print_queue(std::queue<Token> q) {
  while (!q.empty()) {
    std::cout << q.front() << " ";
    q.pop();
  }
  std::cout << std::endl;
}

void RemoveSpaces(std::string& str);

int main(int argc, char* argv[]) {
  // string expression = argv[1];
  std::string expression = "(2+2)* 4";
  RemoveSpaces(expression);
  ShuntingYard yard = ShuntingYard();
  std::queue<Token> res = yard.Process(expression);
  std::cout << "Reverse polish notation:" << std::endl;
  print_queue(res);

  return 0;
}

// Видалає пропуски з рядка
void RemoveSpaces(std::string& str) {
  size_t pos = str.find(' ');
  while (pos != std::string::npos) {
    str.erase(pos, 1);
    pos = str.find(' ', pos);
  }
}
