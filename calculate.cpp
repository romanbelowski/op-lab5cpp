#include "calculate.hpp"

#include "stack.hpp"

using namespace std;

float Calculate(Queue<Token *> &tokens) {
  Queue<Token *> postfix = ShuntingYard(tokens);
  return CalculateRPN(postfix);
}

// Перетворює вираз з інфіксної нотації в постфіксну
Queue<Token *> ShuntingYard(Queue<Token *> &infix) {
  Queue<Token *> postfix(16);
  Stack<Token *> operators(16);

  while (!infix.is_empty()) {
    auto token = infix.dequeue();
    if (token->GetIsOperator()) {
      while (!operators.is_empty()) {
        auto op = operators.pop();
        if (op->GetPrecedence() >= token->GetPrecedence()) {
          postfix.enqueue(op);
        } else {
          operators.push(op);
          break;
        }
      }
      operators.push(token);
    } else {
      postfix.enqueue(token);
    }
  }
  while (!operators.is_empty()) {
    postfix.enqueue(operators.pop());
  }
  return postfix;
}

// Обчислює вираз заданий в постфіксній нотації
float CalculateRPN(Queue<Token *> &tokens) {
  Stack<float> values(16);
  float x, y;
  while (!tokens.is_empty()) {
    auto token = tokens.dequeue();
    if (token->GetIsOperator()) {
      y = values.pop();
      x = values.pop();
      values.push(token->Calculate(x, y));
    } else {
      values.push(token->GetValue());
    }
  }
  return values.pop();
}
