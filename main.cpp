#include <iostream>

#include "Expression.hpp"
#include "ExpressionPair.hpp"
#include "ExpressionReader.hpp"
#include "Fraction.hpp"
#include "Term.hpp"

int main() {
    // std::cout << (Fraction(15, 10) - Fraction(2, 1)).toString() << std::endl;
    // std::cout << ((Term(Fraction(15, 10)) * Part('a') * Part('b') * Part('c') * Part('b') / Part('b')) / (Term(Fraction(1, 2)) * Part('c'))).simplify().at(0).toString() << std::endl;
    Expression expr1 = ExpressionReader().parse("(x+2)(y-1)-(x+5)(y-2)");
    // expr1 = expr1.simplify();
    Expression expr2 = Expression();
    std::cout << expr1.toString() << std::endl;
    ExpressionPair ep = ExpressionPair(expr1, expr2, ExpressionPair::EOperator::EQUALS).solveFor(Variable('x'));
    std::cout << ep.getFirst().toString() << "=" << ep.getSecond().toString() << std::endl;
    return 0;
}