#pragma once
#include <string>

extern const std::string OPERATORS;

class Token {
 public:
  static bool IsOperator(std::string str);

  virtual bool GetIsOperator() { return false; };
  virtual int GetPrecedence() { return 0; };
  virtual std::string GetAsText() { return "Token"; };
};

class ValueToken : public Token {
 public:
  ValueToken(std::string token) : value_(stof(token)){};
  std::string GetAsText();

  float GetValue() { return value_; };
  bool GetIsOperator() { return false; };

 private:
  float value_;
};

class OperatorToken : public Token {
 public:
  OperatorToken(std::string token) : operator_(token[0]){};
  float Calculate(ValueToken, ValueToken);
  int GetPrecedence();
  std::string GetAsText();

  bool GetIsOperator() { return true; };

 private:
  char operator_;
};

std::ostream& operator<<(std::ostream& os, Token& token);
