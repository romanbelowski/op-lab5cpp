#pragma once
#include <string>

extern const std::string TOKENS;

// Тип токена
enum TypeOfToken {
  VALUE,
  OPERATOR,
  FUNCTION,
  LEFT_PARANTHESIS,
  RIGHT_PARANTHESIS,
};

// Асоціативність оператора
enum Associativity {
  LEFT,
  RIGHT,
};

class Token {
 private:
  std::string token_;
  TypeOfToken type_;

 public:
  static TypeOfToken GetType(std::string str);
  Token() : token_("+"), type_(OPERATOR){};
  Token(std::string token) : token_(token), type_(GetType(token)){};

  TypeOfToken GetType();             // Повертає тип токена
  float GetValue();                  // Повертає значення числа
  int GetPrecedence();               // Повертає приорітет операції
  Associativity GetAssociativity();  // Повертає асоціатиність операції
  float Calculate(float, float);     // Обчислює результат бінарного оператора

  friend std::ostream& operator<<(std::ostream& os, Token token);
};

std::ostream& operator<<(std::ostream& os, Token token);
