#include "queue.hpp"
#include "token.hpp"

// Обчислює вираз в інфіксній нотації
float Calculate(Queue<Token> &);

// DEBUG
Queue<Token> ShuntingYard(Queue<Token> &);
float CalculateRPN(Queue<Token> &);
