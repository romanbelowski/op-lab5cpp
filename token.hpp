#pragma once
#include <string>

extern const std::string OPERATORS;

class Token {
 public:
  Token(){};
  static bool IsOperator(std::string str);

  virtual bool GetIsOperator() { return false; };
  virtual std::string GetAsText() { return "Token"; };
};

class ValueToken : public Token {
 public:
  ValueToken(std::string token) : value_(stoi(token)){};
  int GetValue();

  bool GetIsOperator() { return false; };
  std::string GetAsText() { return std::to_string(value_); };

 private:
  float value_;
};

class OperatorToken : public Token {
 public:
  OperatorToken(std::string token) : operator_(token[0]){};
  int Calculate(ValueToken, ValueToken);
  int GetPrecedence();

  bool GetIsOperator() { return true; };
  std::string GetAsText() { return std::string(1, operator_); };

 private:
  char operator_;
};
