#include <iostream>

#include "Expression.hpp"
#include "ExpressionPair.hpp"
#include "Fraction.hpp"
#include "Term.hpp"

int main() {
    // std::cout << (Fraction(15, 10) - Fraction(2, 1)).toString() << std::endl;
    // std::cout << ((Term(Fraction(15, 10)) * Part('a') * Part('b') * Part('c') * Part('b') / Part('b')) / (Term(Fraction(1, 2)) * Part('c'))).simplify().at(0).toString() << std::endl;
    Expression expr1 = Expression() + (Term(Fraction(2, 1)) * Variable('x')) + (Term(Fraction(-7, 1)));
    Expression expr2 = Expression() + (Term(Fraction(-4, 1)) * Variable('x')) + (Term(Fraction(5, 1)));
    ExpressionPair ep = ExpressionPair(expr1, expr2, ExpressionPair::EOperator::EQUALS).solveFor(Variable('x'));
    std::cout << ep.getFirst().toString() << "=" << ep.getSecond().toString() << std::endl;
    return 0;
}