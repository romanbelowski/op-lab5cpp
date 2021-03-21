#include "stack.hpp"

#include <iostream>

using namespace std;
/*
//  Подвоює розмір стаку
template<typename T>
void Stack<T>::doublesize() {
  T* new_stack = new T[size_ * 2];
  for (int i = 0; i < size_; i++) {
    new_stack[i] = stack_[i];
  }
  delete[] stack_;
  stack_ = new_stack;
}

//  Додає елемент на вершину стаку
template<typename T>
void Stack<T>::push(T item) {
  if (top_ == size_ - 1) {
    //code

  } else {
    top_ = top_ + 1;
    stack_[top_] = item;
  }
}
//  Видаляє елемент з вершини стаку
template<typename T>
T Stack<T>::pop() {
  T temp_;
  temp_ = stack_[top_];
  top_ = top_ - 1;
  return (temp_);
}

//  Перевіряє чи стак порожній
template<typename T>
bool Stack<T>::isempty() {
  return (top_ == -1);
}
*/