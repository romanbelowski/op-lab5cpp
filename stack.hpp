#pragma once
#include <iostream>

#include "token.hpp"

template <typename T>
class Stack {
 private:
  T* stack_;
  void doublesize();
  int top_;
  int size_;

 public:
  void push(T);
  T pop();
  T top();

  bool isempty();
  void display();

  Stack(int size) {
    top_ = -1;
    size_ = size;
    stack_ = new T[size_];
  }

  ~Stack() {
    delete[] stack_;
  }
};

//  Подвоює розмір стаку
template <typename T>
void Stack<T>::doublesize() {
  T* new_stack = new T[size_ * 2];
  for (int i = 0; i < size_; i++) {
    new_stack[i] = stack_[i];
  }
  delete[] stack_;
  stack_ = new_stack;
  size_ = size_ * 2;
}

//  Додає елемент на вершину стаку
template <typename T>
void Stack<T>::push(T item) {
  if (top_ == size_ - 1) {
    doublesize();
  } else {
    top_ = top_ + 1;
    stack_[top_] = item;
  }
}

//  Видаляє елемент з вершини стаку
template <typename T>
T Stack<T>::pop() {
  T temp_;
  temp_ = stack_[top_];
  top_ = top_ - 1;
  return (temp_);
}

//  Бере елемент з вершини стаку
template <typename T>
T Stack<T>::top() {

  return (stack_[top_]);
}

//  Перевіряє чи стак порожній
template <typename T>
bool Stack<T>::isempty() {
  return (top_ == -1);
}

//  Вивести всі елемнти стаку
template <typename T>
void Stack<T>::display() {
  for (int i = 0; i <= top_; i++)
    std::cout << stack_[i] << " ";
  std::cout << std::endl;
}
