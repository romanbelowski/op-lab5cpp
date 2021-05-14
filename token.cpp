#include "token.hpp"

#include <cmath>
#include <sstream>
#include <stdexcept>

using namespace std;

const std::string BINARY_OPERATORS = "+-*/^=";
const std::string TOKENS = BINARY_OPERATORS + "()";

// Повертає тип токена
Type Token::GetType(std::string token) {
  if (BINARY_OPERATORS.find(token) != std::string::npos)
    return BINARY_OPERATOR;
  if (token == "(")
    return LEFT_PARANTHESIS;
  if (token == ")")
    return RIGHT_PARANTHESIS;
  return VALUE;
}

// Повертає приорітет оператора
int Token::GetPrecedence() {
  if (token_ == "=")
    return 1;
  if (token_ == "+" || token_ == "-")
    return 2;
  if (token_ == "*" || token_ == "/")
    return 3;
  if (token_ == "^")
    return 4;
  throw invalid_argument("Спроба отримати приорітет не з оператора");
}

// Повертає асоціативність оператора
Associativity Token::GetAssociativity() {
  if (token_ == "*" || token_ == "/" || token_ == "+" || token_ == "-")
    return LEFT;
  if (token_ == "^")
    return RIGHT;
  throw invalid_argument("Спроба отримати асоціативність не з оператора");
}

// Вивести токен
ostream& operator<<(ostream& os, Token token) {
  return os << token.token_;
}