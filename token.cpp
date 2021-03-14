#include "token.hpp"

#include <iostream>

using namespace std;

const string OPERATORS = "+-*/";

Token::Token(string value) {
  token = value;
}

bool Token::IsOperator(string str) {
  if (OPERATORS.find(str) != string::npos)
    return true;
  return false;
}

bool Token::GetIsOperator() {
  return IsOperator(token);
}

int Token::GetPrecedence() {
  if (token == "*" || token == "/")
    return 3;
  if (token == "+" || token == "-")
    return 2;
  return 0;
}

float Token::Calculate(float x, float y) {
  if (GetIsOperator()) {
    if (token == "+")
      return x + y;
    if (token == "-")
      return x - y;
    if (token == "*")
      return x * y;
    if (token == "/")
      return x / y;
  }
}
