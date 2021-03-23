#include <iostream>
#include <string>

#include "calculate.hpp"
#include "queue.hpp"
#include "token.hpp"

using namespace std;

Queue<Token> SplitExpression(string);  // Роздляє рядок на чергу токенів

int main(int argc, char* argv[]) {
  string expression = argv[1];
  //string expression = "(2+3)/5";
  Queue<Token> queue = SplitExpression(expression);

  queue.display();

  Queue<Token> res = ShuntingYard(queue);
  res.display();

   cout << CalculateRPN(res) << endl;

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

// Повертає позицію і розмір наступного оператора
size_t next_op(string str, size_t start_pos, size_t* size) {
  size_t operator_pos = str.find_first_of(TOKENS, start_pos),
         function_pos = str.find("sqrt", start_pos),
         result_pos = min(operator_pos, function_pos);

  if (result_pos == string::npos) {
    *size = string::npos;
  } else if (result_pos == operator_pos) {
    *size = 1;
  } else if (result_pos == function_pos) {
    *size = 4;
  }
  return result_pos;
}

// Роздляє рядок на чергу токенів
Queue<Token> SplitExpression(string str) {
  RemoveSpaces(str);
  Queue<Token> out(16);
  string token;
  size_t start_pos = 0, op_size, op_pos = next_op(str, start_pos, &op_size);
  while (op_pos != string::npos) {
    // Число між операторами
    if (start_pos < op_pos) {
      token = str.substr(start_pos, op_pos - start_pos);
      out.enqueue(Token(token));
    }

    // Оператор
    token = str.substr(op_pos, op_size);
    out.enqueue(Token(token));

    start_pos = op_pos + op_size;
    op_pos = next_op(str, start_pos, &op_size);
  }

  // Число в кінці
  if (start_pos < str.size()) {
    token = str.substr(start_pos, string::npos);
    out.enqueue(Token(token));
  }

  return out;
}