#pragma once
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>

#include "shunting-yard.hpp"
#include "token.hpp"

extern std::map<std::string, float> VARIABLES;

class Node {
 public:
  Node(){};
  virtual float evaluate() = 0;       // Рекурсивно обчислює через обхід в зворотньому порядку
  virtual void print(int depth) = 0;  // Рекурсивно виводить через сииметричний обхід
};

class NumberNode : public Node {
 private:
  float value_;

 public:
  NumberNode(float value) : value_(value){};
  NumberNode(std::string value) : value_(std::stof(value)){};
  float evaluate() override;
  void print(int depth) override;
};

class VariableNode : public Node {
 private:
  std::string name_;

 public:
  VariableNode(std::string name) : name_(name){};
  float assign(float value);
  float evaluate() override;
  void print(int depth) override;
};

class BinaryOpNode : public Node {
 private:
  std::string operator_;
  Node *left_, *right_;

 public:
  BinaryOpNode(std::string op, Node *left, Node *right) : operator_(op), left_(left), right_(right){};
  float evaluate() override;
  void print(int depth) override;
};

class UnaryOpNode : public Node {
 private:
  std::string operator_;
  Node *left_;

 public:
  UnaryOpNode(std::string op, Node *left) : operator_(op), left_(left){};
  float evaluate() override;
  void print(int depth) override;
};

class Tree {
 private:
  std::vector<Node *> rows_;

 public:
  Tree(){};
  void add_node(Node *node);
  float evaluate();
  void print(int depth);
};

class IfNode : public Node {
 private:
  std::string operator_;
  Node *condition_;
  Tree *then_, *else_;

 public:
  IfNode(Node *condition, Tree *then, Tree *_else) : condition_(condition), then_(then), else_(_else){};
  float evaluate();
  void print(int depth);
};