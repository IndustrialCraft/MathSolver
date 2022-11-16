#include "ExpressionReader.hpp"

#include "Term.hpp"
#include "cctype"

Expression ExpressionReader::parse(std::string input) {
    return parseExpr(input + ")", 0).first;
}

std::pair<Expression, int> ExpressionReader::parseExpr(std::string input, int offset) {
    Expression expr;
    bool first = true;
    bool isSub = false;
    bool isInverse = false;
    Term currentTerm(Fraction(1, 1));
    for (int i = offset; i < input.length(); i++) {
        char ch = input.at(i);
        if (ch == '*')
            continue;
        if (ch == '/') {
            isInverse = true;
            continue;
        }
        if (isdigit(ch)) {
            std::string num = "";
            for (; isdigit(input.at(i)); i++) {
                num = num + input.at(i);
            }
            i--;
            int number = std::stoi(num);
            currentTerm = isInverse ? (currentTerm / Fraction(number, 1)) : (currentTerm * Fraction(number, 1));
            isInverse = false;
            first = false;
        }
        if (isalpha(ch)) {
            currentTerm = isInverse ? (currentTerm / Variable(ch)) : (currentTerm * Variable(ch));
            isInverse = false;
            first = false;
            continue;
        }
        if (ch == '(') {
            std::pair<Expression, int> ePair = parseExpr(input, i + 1);
            currentTerm = isInverse ? (currentTerm / ePair.first) : (currentTerm * ePair.first);
            i = ePair.second;
            isInverse = false;
            first = false;
            continue;
        }
        if (ch == '+') {
            if (!first)
                expr = (expr + (currentTerm * (isSub ? Fraction(-1, 1) : Fraction(1, 1))));
            isSub = false;
            first = false;
            isInverse = false;
            currentTerm = Term(Fraction(1, 1));
            continue;
        }
        if (ch == '-') {
            if (!first)
                expr = (expr + (currentTerm * (isSub ? Fraction(-1, 1) : Fraction(1, 1))));
            isSub = true;
            first = false;
            isInverse = false;
            currentTerm = Term(Fraction(1, 1));
            continue;
        }
        if (ch == ')') {
            if (!first)
                expr = (expr + (currentTerm * (isSub ? Fraction(-1, 1) : Fraction(1, 1))));
            return std::pair<Expression, int>(expr, i);
        }
    }
    throw std::logic_error("exprected )");
}