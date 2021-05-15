
#include "builder.hpp"

inline bool StartsWith(std::string str, std::string prefix) {
  return str.rfind(prefix, 0) == 0;
}

inline bool Contains(std::string str, std::string substr) {
  return str.find(substr) != std::string::npos;
}

void ungetline(std::string& line, std::ifstream& file) {
  for (size_t i = 0; i <= line.size(); i++) {
    file.unget();
  }
}

Node* Builder::BuildNode(std::queue<Token> row) {
  std::stack<Node*> values;
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
  return values.top();
}

Tree* Builder::BuildTree(std::string path) {
  std::ifstream file(path);
  std::string temp;
  Tree* tree = BuildTreeByDepth(0, file, temp);
  file.close();
  return tree;
}

Tree* Builder::BuildTreeByDepth(int depth, std::ifstream& file, std::string& next_line) {
  std::string line, prefix = std::string(depth * 4, ' ');
  Tree* tree = new Tree();
  ShuntingYard yard = ShuntingYard();

  while (getline(file, line)) {
    if (!StartsWith(line, prefix)) {
      std::cout << "without prefix ->" << line << std::endl;
      ungetline(line, file);
      break;
    }
    if (StartsWith(line, prefix + "if ")) {
      std::cout << "with 'if '     ->" << line << std::endl;
      std::string s_condition = line.substr(4 * depth + 3, line.find(':') - 4 * depth - 3);
      Node* condition = BuildNode(yard.Process(s_condition));
      Tree* then = BuildTreeByDepth(depth + 1, file, line);
      Tree* _else = nullptr;
      if (StartsWith(line, prefix + "else:")) {
        getline(file, line);  // skip line with "else:"
        std::cout << "with 'else:'  ->" << line << std::endl;
        _else = BuildTreeByDepth(depth + 1, file, line);
      }
      tree->add_node(new IfNode(condition, then, _else));
    } else if (line.back() == ';') {
      std::cerr << "with ';'       ->" << line << std::endl;
      std::string row = line.substr(0, line.size() - 1);
      tree->add_node(BuildNode(yard.Process(row)));
    } else {
      std::cerr << "without ';'    ->" << line << std::endl;
    }
  }
  next_line = line;
  return tree;
}