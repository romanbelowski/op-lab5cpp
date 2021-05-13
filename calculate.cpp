#include "calculate.hpp"

enum State {
  WANT_OPERAND,
  HAVE_OPERAND,
};

// Перетворює вираз з інфіксної нотації в постфіксну
// Перетворює вираз з інфіксної нотації в постфіксну
std::queue<Token> Infix2Postix(std::queue<Token> infix) {
  State state = WANT_OPERAND;
  std::queue<Token> postfix;
  std::stack<Token> operators;

  while (!infix.empty()) {
    Token token = infix.front();
    TypeOfToken type = token.GetType();
    switch (state) {
      case WANT_OPERAND:
        if (type == VALUE) {
          postfix.push(token);
          state = HAVE_OPERAND;
        }
        if (type == BINARY_OPERATOR) {
          type = UNARY_OPERATOR;
          token.SetType(UNARY_OPERATOR);
        }
        if (type == UNARY_OPERATOR || type == LEFT_PARANTHESIS) {
          operators.push(token);
          state = WANT_OPERAND;
        }
        break;
      case HAVE_OPERAND:
        if (type == RIGHT_PARANTHESIS) {
          while (operators.top().GetType() != LEFT_PARANTHESIS) {
            postfix.push(operators.top());
            operators.pop();
          }
          operators.pop();  // Видаляэмо ліву дужку
          state = HAVE_OPERAND;
        }
        if (type == BINARY_OPERATOR) {
          while (!operators.empty()) {
            Token op = operators.top();
            operators.pop();
            if ((op.GetType() != LEFT_PARANTHESIS) && ((op.GetPrecedence() > token.GetPrecedence()) || ((op.GetPrecedence() == token.GetPrecedence()) && (token.GetAssociativity() == LEFT)))) {
              postfix.push(op);
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
    infix.pop();
  }

  while (!operators.empty()) {
    postfix.push(operators.top());
    operators.pop();
  }
  return postfix;
}