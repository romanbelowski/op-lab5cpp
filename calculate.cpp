#include "calculate.hpp"

using namespace std;

Queue<Token *> ShuntingYard(Queue<Token *> &tokens) {
  Queue<Token *> output(16);
  Stack<Token *> operators(16);

  while (!tokens.is_empty()) {
    auto token = tokens.dequeue();
    if (token->GetIsOperator()) {
      while (!operators.is_empty()) {
        auto op = operators.pop();
        if (op->GetPrecedence() >= token->GetPrecedence()) {
          output.enqueue(op);
        } else {
          operators.push(op);
          break;
        }
      }
      operators.push(token);
    } else {
      output.enqueue(token);
    }
  }
  while (!operators.is_empty()) {
    output.enqueue(operators.pop());
  }
  return output;
}
