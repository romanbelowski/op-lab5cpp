#include <stdio.h>

#include <iostream>
#include <string>

#include "calculate.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "token.hpp"
using namespace std;

void RemoveSpaces(string& str) {
  size_t pos = str.find(' ');
  while (pos != string::npos) {
    str.erase(pos, 1);
    pos = str.find(' ', pos);
  }
}

int main(int argc, char* argv[]) {
  // string expression;
  // expression = argv[1];
  // cout << "-------" << endl;
  // cout << expression << endl;
  // RemoveSpaces(expression);
  // cout << expression << endl;
  // cout << OPERATORS << endl;

  OperatorToken power = OperatorToken("^");
  OperatorToken plus = OperatorToken("+");
  OperatorToken minus = OperatorToken("-");
  OperatorToken times = OperatorToken("*");
  ValueToken two = ValueToken("2");
  ValueToken three = ValueToken("3");
  ValueToken four = ValueToken("4");
  ValueToken five = ValueToken("5");
  ValueToken six = ValueToken("6");
  ValueToken seven = ValueToken("7");

  // Stack<Token*> golang(16);
  Queue<Token*> queue(16);
  queue.enqueue(&two);
  queue.enqueue(&power);
  queue.enqueue(&two);
  queue.enqueue(&plus);
  queue.enqueue(&two);
  queue.enqueue(&power);
  queue.enqueue(&three);
  queue.enqueue(&power);
  queue.enqueue(&four);

  queue.enqueue(&plus);
  queue.enqueue(&four);
  queue.enqueue(&plus);
  queue.enqueue(&five);
  queue.enqueue(&minus);
  queue.enqueue(&six);
  queue.enqueue(&times);
  queue.enqueue(&seven);
  queue.enqueue(&power);
  queue.enqueue(&two);

  queue.display();

  Queue<Token*> res = ShuntingYard(queue);
  res.display();

  cout << CalculateRPN(res) << endl;

  return 0;
}