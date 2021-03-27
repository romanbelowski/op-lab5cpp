#include "calculate.hpp"

#include "stack.hpp"

using namespace std;

float Calculate(Queue<Token> &tokens) {
  Queue<Token> postfix = ShuntingYard(tokens);
  return CalculateRPN(postfix);
}

enum StateShuntingYard {
  WANT_OPERAND,
  HAVE_OPERAND,
};

// Перетворює вираз з інфіксної нотації в постфіксну
Queue<Token> ShuntingYard(Queue<Token> &infix) {
  StateShuntingYard state = WANT_OPERAND;
  Queue<Token> postfix(16);
  Stack<Token> operators(16);

  while (!infix.isempty()) {
    Token token = infix.dequeue();
    TypeOfToken type = token.GetType();
    switch (state) {
      case WANT_OPERAND:
        if (type == VALUE) {
          postfix.enqueue(token);
          state = HAVE_OPERAND;
        }
        if (type == INFIX_OPERATOR || type == LEFT_PARANTHESIS) {
          if (type == INFIX_OPERATOR)
            token.SetType(PREFIX_OPERATOR);
          operators.push(token);
          state = WANT_OPERAND;
        }
        break;
      case HAVE_OPERAND:
        if (type == POSTFIX_OPERATOR) {
          postfix.enqueue(token);
          state = HAVE_OPERAND;
        }
        if (type == RIGHT_PARANTHESIS) {
          if (operators.isempty()) {
            cerr << "Mismatched parentheses" << endl;
            exit(1);
          }
          while (operators.top().GetType() != LEFT_PARANTHESIS) {
            if (operators.isempty()) {
              cerr << "Mismatched parentheses" << endl;
              exit(1);
            }
            postfix.enqueue(operators.pop());
          }
          operators.pop();  // Видаляэмо ліву дужку
          state = HAVE_OPERAND;
        }
        if (type == INFIX_OPERATOR) {
          while (!operators.isempty()) {
            Token op = operators.pop();
            if ((op.GetType() != LEFT_PARANTHESIS) && ((op.GetPrecedence() > token.GetPrecedence()) || ((op.GetPrecedence() == token.GetPrecedence()) && (token.GetAssociativity() == LEFT)))) {
              postfix.enqueue(op);
            } else {
              operators.push(op);  // Повертає оператор назад в стак
              break;
            }
          }
          operators.push(token);
          state = WANT_OPERAND;
        }
        break;
    }
  }

  while (!operators.isempty()) {
    if (operators.top().GetType() == LEFT_PARANTHESIS || operators.top().GetType() == RIGHT_PARANTHESIS) {
      cerr << "Mismatched parentheses" << endl;
      exit(1);
    }
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

    switch (type) {
      case VALUE:
        result = token.GetValue();
        break;
      case INFIX_OPERATOR:
        y = values.pop();
        x = values.pop();
        result = token.Calculate(x, y);
        break;
      case PREFIX_OPERATOR:
        x = values.pop();
        result = token.Calculate(x);
        break;
    }
    values.push(result);
  }
  return values.pop();
}
