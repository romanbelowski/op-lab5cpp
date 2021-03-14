#pragma once
#include <string>

extern const std::string OPERATORS;

class Token {
 public:
  Token(){};
  static bool IsOperator(std::string str);

  virtual bool GetIsOperator() { return false; };
};

class OperatorToken : public Token {
 public:
  OperatorToken(std::string token) : operator_(token[0]){};
  int GetPrecedence();
  int Calculate(int, int);
  bool GetIsOperator() { return true; };

 private:
  char operator_;
};

class ValueToken : public Token {
 public:
  ValueToken(std::string token) : value_(stoi(token)){};
  int GetValue() { return value_; };
  bool GetIsOperator() { return false; };

 private:
  float value_;
};
