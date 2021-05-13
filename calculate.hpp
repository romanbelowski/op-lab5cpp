#pragma once
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>

#include "token.hpp"

// Shunting Yard
std::queue<Token> Infix2Postix(std::queue<Token> infix);
