#include "token.hpp"

#include <cmath>
#include <sstream>
#include <stdexcept>

using namespace std;

const string TOKENS = "+-*/^()";
const string OPERATORS = "+-*/^";

// Перевіряє чи символ є деяким типом операторів
bool IsSubOperator(string str, string tokens) {
  if (str != "" && tokens.find(str) != string::npos)
    return true;
  return false;
}

// Повертає тип токена
TypeOfToken Token::GetType(string token) {
  if (IsSubOperator(token, OPERATORS))
    return OPERATOR;
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

// Повертає значення числа
float Token::GetValue() {
  if (type_ != VALUE)
    throw invalid_argument("Спроба отримати значення не з VALUE");
  return stof(token_);
}

// Повертає приорітет оператора
int Token::GetPrecedence() {
  if (type_ != OPERATOR)
    throw invalid_argument("Спроба отримати приорітет не з OPERATOR");
  if (token_ == "*" || token_ == "/")
    return 3;
  if (token_ == "+" || token_ == "-")
    return 2;
}

// Повертає асоціативність оператора
Associativity Token::GetAssociativity() {
  if (type_ != OPERATOR)
    throw invalid_argument("Спроба отримати асоціативність не з OPERATOR");
  if (token_ == "*" || token_ == "/" || token_ == "+" || token_ == "-")
    return LEFT;
  if (token_ == "^")
    return RIGHT;
}

// Обчислює результат бінарного оператора
float Token::Calculate(float x, float y) {
  if (type_ != OPERATOR)
    throw invalid_argument("Спроба отримати результат не з OPERATOR");
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

// Вивести токен
ostream& operator<<(ostream& os, Token token) {
  return os << token.token_;
}