
#include "parser.hpp"

void RemoveSpaces(std::string& str) {
  size_t pos = str.find_first_of(" \n");
  while (pos != std::string::npos) {
    str.erase(pos, 1);
    pos = str.find_first_of(" \n", pos);
  }
}

std::vector<std::string> Parser::Read(std::string path) {
  std::ifstream file(path);
  std::string line;
  std::vector<std::string> result;
  while (getline(file, line, ';')) {
    RemoveSpaces(line);
    // std::cout << line << std::endl;
    result.push_back(line);
  }
  file.close();
  return result;
}