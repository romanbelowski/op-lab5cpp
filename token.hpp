#pragma once
#include <string>

extern const std::string TOKENS;

// Тип токена
enum TypeOfToken {
  NONE,
  VALUE,
  UNARY_OPERATOR,     // Унарний оператор: -69
  BINARY_OPERATOR,    // Бінарний оператор: 1 + 1
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
  int GetPrecedence();               // Повертає приорітет операції
  Associativity GetAssociativity();  // Повертає асоціатиність операції

  friend std::ostream& operator<<(std::ostream& os, Token token);
};
