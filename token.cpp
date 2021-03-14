#include "token.hpp"

#include <stdexcept>

using namespace std;

const string OPERATORS = "+-*/";

// Перевіряє чи символ є оператором
bool Token::IsOperator(string str) {
  if (OPERATORS.find(str) != string::npos)
    return true;
  return false;
}

int ValueToken::GetValue() {
  return value_;
}

// Повертає приорітет оператора
int OperatorToken::GetPrecedence() {
  switch (operator_) {
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
int OperatorToken::Calculate(ValueToken a, ValueToken b) {
  int x = a.GetValue(),
      y = b.GetValue();
  switch (operator_) {
    case '+':
      return x + y;
    case '-':
      return x - y;
    case '*':
      return x * y;
    case '/':
      return x / y;
    default:
      throw invalid_argument("Отримано невідомий оператор");
  }
}
