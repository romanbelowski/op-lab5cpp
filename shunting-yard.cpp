#include "shunting-yard.hpp"

// Повертає позицію наступного токена-оператора починаючи з start_pos
inline size_t next_token_pos(std::string str, size_t start_pos) {
  return str.find_first_of(TOKENS, start_pos);
}

// Роздляє рядок на чергу токенів
std::queue<Token> ShuntingYard::SplitExpression(std::string str) {
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

// Перетворює вираз з інфіксної нотації в постфіксну
std::queue<Token> ShuntingYard::Infix2Postix(std::queue<Token>& infix) {
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

// Перетворює вираз з інфіксної нотації в постфіксну
std::queue<Token> ShuntingYard::Process(std::string str) {
  std::queue<Token> queue = SplitExpression(str);
  return Infix2Postix(queue);
}