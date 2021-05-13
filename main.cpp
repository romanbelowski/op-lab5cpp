#include <iostream>
#include <string>

#include "shunting-yard.hpp"
#include "token.hpp"

using namespace std;

std::queue<Token> SplitExpression(std::string str);  // Роздляє рядок на чергу токенів

void print_queue(std::queue<Token> q) {
  while (!q.empty()) {
    std::cout << q.front() << " ";
    q.pop();
  }
  std::cout << std::endl;
}

int main(int argc, char* argv[]) {
  // string expression = argv[1];
  string expression = "(2+2)* 4";
  ShuntingYard yard = ShuntingYard();
  std::queue<Token> queue = SplitExpression(expression);

  std::queue<Token> res = yard.Infix2Postix(queue);
  cout << "Reverse polish notation:" << endl;
  print_queue(res);

  return 0;
}

// Видалає пропуски з рядка
void RemoveSpaces(string& str) {
  size_t pos = str.find(' ');
  while (pos != string::npos) {
    str.erase(pos, 1);
    pos = str.find(' ', pos);
  }
}

// Повертає позицію наступного токена-оператора починаючи з start_pos
inline size_t next_token_pos(string str, size_t start_pos) {
  return str.find_first_of(TOKENS, start_pos);
}

// Роздляє рядок на чергу токенів
std::queue<Token> SplitExpression(std::string str) {
  std::queue<Token> result;
  std::string token;
  size_t start_pos = 0, token_pos = next_token_pos(str, 0);

  while (token_pos != std::string::npos) {
    if (next_token_pos(str, start_pos) == start_pos) {
      token = str.substr(token_pos++, 1);  // Токен - оператор
    } else {
      token = str.substr(start_pos, token_pos - start_pos);  // Токен - значення між двома операторами
    }
    result.push(Token(token));
    start_pos = token_pos;
    token_pos = next_token_pos(str, start_pos);
  }
  // Токен - значення в кінці
  if (start_pos < str.size()) {
    token = str.substr(start_pos, std::string::npos);
    result.push(Token(token));
  }

  return result;
}