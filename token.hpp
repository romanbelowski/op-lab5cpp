#pragma once
#include <string>

extern const std::string TOKENS;

// Тип токена
enum Type {
  NONE,
  VALUE,              // Число або змінна: 1337, var1
  UNARY_OPERATOR,     // Унарний оператор: -1
  BINARY_OPERATOR,    // Бінарний оператор: 1 + 1, 2 * 2
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
  Type type_;

 public:
  static Type GetType(std::string str);
  Token() : token_(""), type_(NONE){};
  Token(std::string token) : token_(token), type_(GetType(token)){};

  std::string GetToken() { return token_; };  // Повертає
  Type GetType() { return type_; };           // Повертає тип токена
  void SetType(Type type) { type_ = type; };  //
  int GetPrecedence();                        // Повертає приорітет операції
  Associativity GetAssociativity();           // Повертає асоціатиність операції

  friend std::ostream& operator<<(std::ostream& os, Token token);
};
