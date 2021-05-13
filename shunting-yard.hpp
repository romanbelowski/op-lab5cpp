#pragma once
#include <queue>
#include <stack>
#include <string>

#include "token.hpp"

class ShuntingYard {
 private:
  enum State {
    WANT_OPERAND,
    HAVE_OPERAND,
  };

 public:
  std::queue<Token> Infix2Postix(std::queue<Token>& infix);
};