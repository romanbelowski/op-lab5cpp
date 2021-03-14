#include <stdio.h>

#include <iostream>
#include <string>

#include "token.hpp"
using namespace std;

void RemoveSpaces(string& str) {
  size_t pos = str.find(' ');
  while (pos != string::npos) {
    str.erase(pos, 1);
    pos = str.find(' ', pos);
  }
}

int main(int argc, char* argv[]) {
  string expression;
  expression = argv[1];
  cout << "-------" << endl;
  cout << expression << endl;
  RemoveSpaces(expression);
  cout << expression << endl;
  cout << OPERATORS << endl;

  OperatorToken plus = OperatorToken("+");
  ValueToken five = ValueToken("5");
  ValueToken ten = ValueToken("10");

  cout << plus.Calculate(five, ten) << endl;

  return 0;
}