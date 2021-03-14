#include "stack.hpp"

#include <iostream>

using namespace std;

//  Подвоює розмір стаку
void Stack::doublesize() {
  Token** new_stack = new Token*[size_ * 2];
  for (int i = 0; i < size_; i++) {
    new_stack[i] = stack_[i];
  }
  delete[] stack_;
  stack_ = new_stack;
}

//  Додає елемент на вершину стаку
void Stack::push(Token* item) {
  if (top_ == size_ - 1) {
    //code

  } else {
    top_ = top_ + 1;
    stack_[top_] = item;
  }
}
//  Видаляє елемент з вершини стаку
Token* Stack::pop() {
  Token* temp_;
  temp_ = stack_[top_];
  top_ = top_ - 1;
  return (temp_);
}

//  Перевіряє чи стак порожній
bool Stack::isempty() {
  return (top_ == -1);
}
