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
  Tree(std::vector<std::string> rows) {
    ShuntingYard yard = ShuntingYard();
    for (const std::string row : rows) {
      add_row(yard.Process(row));
    }
  };

  float evaluate() {
    float result;
    for (Node *node : rows_) {
      result = node->evaluate();
    }
    return result;
  }
  void add_row(std::queue<Token> row) {
    std::stack<Node *> values;
    Node *result, *x, *y;

    while (!row.empty()) {
      Token token = row.front();
      Type type = token.GetType();

      row.pop();

      switch (type) {
        case VALUE:
          if (std::isdigit(token.GetToken()[0]))
            result = new NumberNode(token.GetToken());
          else
            result = new VariableNode(token.GetToken());
          break;
        case BINARY_OPERATOR:
          y = values.top();
          values.pop();
          x = values.top();
          values.pop();
          result = new BinaryOpNode(token.GetToken(), x, y);
          break;
        case UNARY_OPERATOR:
          x = values.top();
          values.pop();
          result = new UnaryOpNode(token.GetToken(), x);
          break;
      }
      values.push(result);
    }
    // std::cout << "TOP -> " << values.top()->evaluate() << std::endl;  // DEBUG
    rows_.push_back(values.top());
  }
};