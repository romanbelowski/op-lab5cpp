#include "ast.hpp"

std::map<std::string, float> VARIABLES;

float NumberNode::evaluate() {
  return value_;
}

void NumberNode::print(int depth) {
  std::cout << std::string(depth * 2, ' ') << value_ << std::endl;
}

float VariableNode::evaluate() {
  return VARIABLES[name_];
}

float VariableNode::assign(float value) {
  std::cout << name_ << " = " << value << std::endl;  // DEBUG
  return (VARIABLES[name_] = value);
};

void VariableNode::print(int depth) {
  std::cout << std::string(depth * 2, ' ') << name_ << std::endl;
}

float BinaryOpNode::evaluate() {
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
}

void BinaryOpNode::print(int depth) {
  left_->print(depth + 1);
  std::cout << std::string(depth * 2, ' ') << operator_ << std::endl;
  right_->print(depth + 1);
}

float UnaryOpNode::evaluate() {
  if (operator_ == "-")
    return -1 * left_->evaluate();
}

void UnaryOpNode::print(int depth) {
  left_->print(depth + 1);
  std::cout << std::string(depth * 2, ' ') << operator_ << std::endl;
}

float IfNode::evaluate() {
  if (condition_->evaluate())
    return then_->evaluate();
  if (else_ != nullptr)
    return else_->evaluate();
}

void IfNode::print(int depth) {
  std::cout << std::string(depth * 2, ' ') << "if" << std::endl;
  condition_->print(depth + 1);
  then_->print(depth + 1);
  else_->print(depth + 1);
}

float WhileNode::evaluate() {
  float result;
  while (condition_->evaluate()){
    result = body_->evaluate();
  }
  return result;
}

void WhileNode::print(int depth){} 


float Tree::evaluate() {
  float result;
  for (Node *node : rows_) {
    result = node->evaluate();
  }
  return result;
}

void Tree::print(int depth) {
  for (Node *node : rows_) {
    std::cout << std::string(depth * 2, ' ') << "T" << std::endl;
    node->print(depth + 1);
  }
}

void Tree::add_node(Node *node) {
  rows_.push_back(node);
}