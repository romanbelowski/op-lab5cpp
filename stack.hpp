#pragma once
#include <string>

#include "token.hpp"

class Stack {
 private:
  Token** stack_;
  void doublesize();
  int top_;
  int size_;
  void delete_stack(Token** stack);

 public:
  void push(Token*);
  Token* pop();
  bool isempty();
  Stack() {
    top_ = -1;
    size_ = 16;
    stack_ = new Token*[size_];
  }

  ~Stack() {
    delete[] stack_;
  }
};
