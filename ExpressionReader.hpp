#pragma once
#include <string>

#include "Expression.hpp"

class ExpressionReader {
public:
    Expression parse(std::string input);
private:
    std::pair<Expression, int> parseExpr(std::string input, int offset);
};