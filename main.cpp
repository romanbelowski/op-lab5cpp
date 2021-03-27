#include <iostream>
#include <string>

#include "calculate.hpp"
#include "queue.hpp"
#include "token.hpp"

using namespace std;

Queue<Token> SplitExpression(string);  // Роздляє рядок на чергу токенів

int main(int argc, char* argv[]) {
  string expression = argv[1];
  // string expression = "(2+2)* 4";
  Queue<Token> queue = SplitExpression(expression);

  cout << "Infix notation:" << endl;
  queue.display();

  Queue<Token> res = ShuntingYard(queue);
  cout << "Reverse polish notation:" << endl;
  res.display();

  cout << "Result: " << CalculateRPN(res) << endl;

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
Queue<Token> SplitExpression(string str) {
  RemoveSpaces(str);
  Queue<Token> out(16);
  string token;
  size_t start_pos = 0, token_pos = next_token_pos(str, 0);

  while (token_pos != string::npos) {
    if (next_token_pos(str, start_pos) == start_pos) {
      // Токен - оператор
      token = str.substr(token_pos++, 1);
      out.enqueue(Token(token));
    } else {
      // Токен - значення між двома операторами
      token = str.substr(start_pos, token_pos - start_pos);
      out.enqueue(Token(token));
    }
    start_pos = token_pos;
    token_pos = next_token_pos(str, start_pos);
  }

  if (start_pos < str.size()) {
    // Токен - значення в кінці
    token = str.substr(start_pos, string::npos);
    out.enqueue(Token(token));
  }

  return out;
}