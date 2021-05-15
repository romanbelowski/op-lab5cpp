#pragma once
#include <fstream>
#include <iostream>
#include <queue>
#include <string>

#include "ast.hpp"
#include "token.hpp"
class Builder {
 private:
  Node* BuildNode(std::queue<Token> row);
  Tree* BuildTreeByDepth(int depth, std::ifstream& file, std::string& next_line);

 public:
  Tree* BuildTree(std::string path);
};