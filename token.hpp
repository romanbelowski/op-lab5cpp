#include <string>

extern const std::string OPERATORS;

class Token {
 public:
  bool IsOperator(std::string str);
  Token(std::string str);
  bool GetIsOperator();
  int GetPrecedence();
  float GetValue();
  bool IsValue();
  float Calculate(float, float);

 private:
  std::string token;
};
