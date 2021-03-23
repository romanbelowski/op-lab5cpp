#include "calculate.hpp"

#include "stack.hpp"

using namespace std;

float Calculate(Queue<Token> &tokens) {
  Queue<Token> postfix = ShuntingYard(tokens);
  return CalculateRPN(postfix);
}

// Перетворює вираз з інфіксної нотації в постфіксну
Queue<Token> ShuntingYard(Queue<Token> &infix) {
  Queue<Token> postfix(16);
  Stack<Token> operators(16);

  while (!infix.isempty()) {
    Token token = infix.dequeue();
    switch (token.GetType()) {
      case VALUE:
        postfix.enqueue(token);
        break;
      case OPERATOR:
        while (!operators.isempty()) {
          Token op = operators.pop();
          if ((op.GetPrecedence() > token.GetPrecedence()) || ((op.GetPrecedence() == token.GetPrecedence()) && token.GetAssociativity() == LEFT))  {
            postfix.enqueue(op);
          } else {
            operators.push(op);  // Повертає оператор назад в стак
            break;
          }
        }
        operators.push(token);
        break;
    }
  }
  while (!operators.isempty()) {
    postfix.enqueue(operators.pop());
  }
  return postfix;
}

// Обчислює вираз заданий в постфіксній нотації
float CalculateRPN(Queue<Token> &tokens) {
  Stack<float> values(16);
  float result, x, y;

  while (!tokens.isempty()) {
    Token token = tokens.dequeue();
    TypeOfToken type = token.GetType();

    if (type == VALUE) {
      result = token.GetValue();
    } else if (type == OPERATOR) {
      y = values.pop();
      x = values.pop();
      result = token.Calculate(x, y);
    }

    values.push(result);
  }
  return values.pop();
}
