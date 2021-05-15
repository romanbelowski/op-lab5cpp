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
  virtual float evaluate() = 0;
};

class NumberNode : public Node {
 private:
  float value_;

 public:
  NumberNode(float value) : value_(value){};
  NumberNode(std::string value) : value_(std::stof(value)){};
  float evaluate() { return value_; };
};

class VariableNode : public Node {
 private:
  std::string name_;

 public:
  VariableNode(std::string name) : name_(name){};
  float evaluate() { return VARIABLES[name_]; };
  float assign(float value) {
    std::cout << name_ << " = " << value << std::endl;  // DEBUG
    return (VARIABLES[name_] = value);
  };
};

class BinaryOpNode : public Node {
 private:
  std::string operator_;
  Node *left_, *right_;

 public:
  BinaryOpNode(std::string op, Node *left, Node *right) : operator_(op), left_(left), right_(right){};
  float evaluate() {
    if (operator_ == "=")
      return static_cast<VariableNode *>(left_)->assign(right_->evaluate());

    float x = left_->evaluate(), y = right_->evaluate();
    if (operator_ == "+")
      return x + y;
    if (operator_ == "-")
      return x - y;
    if (operator_ == "*")
      return x * y;
    if (operator_ == "/")
      return x / y;
    if (operator_ == "^")
      return pow(x, y);
  };
};

class UnaryOpNode : public Node {
 private:
  std::string operator_;
  Node *left_;

 public:
  UnaryOpNode(std::string op, Node *left) : operator_(op), left_(left){};
  float evaluate() {
    if (operator_ == "-")
      return -1 * left_->evaluate();
  };
};

class Tree {
 private:
  std::vector<Node *> rows_;

 public:
  Tree(){};
  float evaluate() {
    float result;
    for (Node *node : rows_) {
      result = node->evaluate();
    }
    return result;
  }
  void add_node(Node *node) {
    rows_.push_back(node);
  }
};

class IfNode : public Node {
 private:
  std::string operator_;
  Node *condition_;
  Tree *then_, *else_;

 public:
  IfNode(Node *condition, Tree *then, Tree *_else) : condition_(condition), then_(then), else_(_else){};
  float evaluate() {
    if (condition_->evaluate())
      return then_->evaluate();
    if (else_ != nullptr)
      return else_->evaluate();
  };
};