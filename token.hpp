#pragma once
#include <string>

extern const std::string OPERATORS;

class Token {
 public:
  Token(){};
  static bool IsOperator(std::string str);

  virtual bool GetIsOperator() { return false; };
};

class ValueToken : public Token {
 public:
  ValueToken(std::string token) : value_(stoi(token)){};
  int GetValue() { return value_; };
  bool GetIsOperator() { return false; };

 private:
  float value_;
};

class OperatorToken : public Token {
 public:
  OperatorToken(std::string token) : operator_(token[0]){};
  int Calculate(ValueToken, ValueToken);
  int GetPrecedence();
  bool GetIsOperator() { return true; };

 private:
  char operator_;
};
