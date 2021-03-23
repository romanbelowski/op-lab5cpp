#include "token.hpp"

#include <cmath>
#include <sstream>
#include <stdexcept>

using namespace std;

const string OPERATORS = "+-*/^()";

// Перевіряє чи символ є оператором
bool IsOperator(string str) {
  if (str != "" && OPERATORS.find(str) != string::npos)
    return true;
  return false;
}

// Повертає тип токена
TypeOfToken Token::GetType(string token) {
  if (IsOperator(token))
    return INFIX_OPERATOR;
  if (token == "(")
    return LEFT_PARANTHESIS;
  if (token == ")")
    return RIGHT_PARANTHESIS;
  return VALUE;
}

// Повертає тип токена
TypeOfToken Token::GetType() {
  return type_;
}

// Встановлює тип токена
void Token::SetType(TypeOfToken type) {
  type_ = type;
}

// Повертає значення числа
float Token::GetValue() {
  if (type_ != VALUE)
    throw invalid_argument("Спроба отримати значення не зі значення");
  return stof(token_);
}

// Повертає приорітет оператора
int Token::GetPrecedence() {
  switch (type_) {
    case INFIX_OPERATOR:
      if (token_ == "*" || token_ == "/")
        return 3;
      if (token_ == "+" || token_ == "-")
        return 2;
      break;
    case PREFIX_OPERATOR:
      if (token_ == "-")
        return 3;
      break;
    default:
      throw invalid_argument("Спроба отримати приорітет не з оператора");
  }
}

// Повертає асоціативність оператора
Associativity Token::GetAssociativity() {
  switch (type_) {
    case INFIX_OPERATOR:
      if (token_ == "*" || token_ == "/" || token_ == "+" || token_ == "-")
        return LEFT;
      if (token_ == "^")
        return RIGHT;
      break;
    case PREFIX_OPERATOR:
      if (token_ == "-")
        return RIGHT;
      break;
    default:
      throw invalid_argument("Спроба отримати асоціативність не з оператора");
  }
}

// Обчислює результат бінарного оператора
float Token::Calculate(float x, float y) {
  if (type_ != INFIX_OPERATOR)
    throw invalid_argument("Спроба отримати результат не з оператора");
  if (token_ == "+")
    return x + y;
  if (token_ == "-")
    return x - y;
  if (token_ == "*")
    return x * y;
  if (token_ == "/")
    return x / y;
  if (token_ == "^")
    return pow(x, y);
}

// Обчислює результат унарного оператора
float Token::Calculate(float x) {
  switch (type_) {
    case PREFIX_OPERATOR:
      if (token_ == "-")
        return -x;
      break;
    default:
      throw invalid_argument("Спроба отримати результат не з оператора");
  }
}

// Вивести токен
ostream& operator<<(ostream& os, Token token) {
  return os << token.token_;
}