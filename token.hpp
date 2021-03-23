#pragma once
#include <string>

extern const std::string OPERATORS;

// Тип токена
enum TypeOfToken {
  NONE,
  VALUE,
  FUNCTION,
  INFIX_OPERATOR,     // Бінарний оператор, типу +, *
  PREFIX_OPERATOR,    // Унарний оператор, типу -
  POSTFIX_OPERATOR,   // Унарний оператор, типу !
  LEFT_PARANTHESIS,   // (
  RIGHT_PARANTHESIS,  // )
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
  Token() : token_(""), type_(NONE){};
  Token(std::string token) : token_(token), type_(GetType(token)){};

  TypeOfToken GetType();             // Повертає тип токена
  void SetType(TypeOfToken);         // Встановлює тип токена
  float GetValue();                  // Повертає значення числа
  int GetPrecedence();               // Повертає приорітет операції
  Associativity GetAssociativity();  // Повертає асоціатиність операції
  float Calculate(float, float);     // Обчислює результат бінарного оператора
  float Calculate(float);            // Обчислює результат унарного оператора

  friend std::ostream& operator<<(std::ostream& os, Token token);
};

std::ostream& operator<<(std::ostream& os, Token token);
