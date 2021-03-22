#include "token.hpp"

#include <cmath>
#include <sstream>
#include <stdexcept>

using namespace std;

const string OPERATORS = "+-*/";

// Перевіряє чи символ є оператором
bool Token::IsOperator(string str) {
  if (OPERATORS.find(str) != string::npos)
    return true;
  return false;
}

// Повертає асоціативність
// Повертає значення як текст
string ValueToken::GetAsText() {
  ostringstream ss;
  ss << value_;
  return ss.str();
}

// Повертає приорітет оператора
int OperatorToken::GetPrecedence() {
  switch (operator_) {
    case '^':
      return 4;
    case '*':
    case '/':
      return 3;
    case '+':
    case '-':
      return 2;
    default:
      throw invalid_argument("Отримано невідомий оператор");
  }
}

// Обчислює результат бінарного оператора
float OperatorToken::Calculate(float x, float y) {
  switch (operator_) {
    case '+':
      return x + y;
    case '-':
      return x - y;
    case '*':
      return x * y;
    case '/':
      return x / y;
    case '^':
      return pow(x, y);
    default:
      throw invalid_argument("Отримано невідомий оператор");
  }
}

// Повертає оператор як текст
string OperatorToken::GetAsText() {
  return string(1, operator_);
}

// Вивести токен
ostream& operator<<(ostream& os, Token* token) {
  return os << token->GetAsText();
}