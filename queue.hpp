#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
class Queue {
 private:
  T* array_;
  int size_, front_, rear_;
  void doublesize();

 public:
  bool is_empty();
  void enqueue(T);
  T dequeue();
  void display();

  Queue(int size) {
    size_ = size;
    front_ = 0;
    rear_ = -1;
    array_ = new T[size];
  }

  ~Queue() {
    delete[] array_;
  }
};

// Перевіряє чи черга порожня
template <typename T>
bool Queue<T>::is_empty() {
  return (front_ > rear_);
}

// Додає елемент в кінець черги
template <typename T>
void Queue<T>::enqueue(T item) {
  if (rear_ == size_ - 1) {
    doublesize();
  }
  array_[++rear_] = item;
}

// Повертає перший елемент з черги
template <typename T>
T Queue<T>::dequeue() {
  if (is_empty()) {
    throw std::out_of_range("Черга пуста");
  }
  return array_[front_++];
}

// Подвоює розмір черги
template <typename T>
void Queue<T>::doublesize() {
  T* new_array = new T[size_ * 2];
  int new_rear = -1;
  for (int i = front_; i <= rear_; i++) {
    new_array[++new_rear] = array_[i];
  }
  delete[] array_;
  array_ = new_array;
  size_ = size_ * 2;
  rear_ = new_rear;
  front_ = 0;
}

// Вивести всі елемнти черги
template <typename T>
void Queue<T>::display() {
  for (int i = front_; i <= rear_; i++)
    std::cout << array_[i] << " ";
  std::cout << std::endl;
}
