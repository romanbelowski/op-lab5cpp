#pragma once
#include <queue>
#include <stack>
#include <string>

#include "token.hpp"

class ShuntingYard {
 private:
  std::string RemoveSpaces(std::string str);
  std::queue<Token> SplitExpression(std::string str);
  std::queue<Token> Infix2Postix(std::queue<Token>& infix);

  enum State {
    WANT_OPERAND,
    HAVE_OPERAND,
  };

 public:
  std::queue<Token> Process(std::string str);
};