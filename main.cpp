#include <iostream>

#include "Expression.hpp"
#include "Fraction.hpp"
#include "Term.hpp"

int main() {
    // std::cout << (Fraction(15, 10) - Fraction(2, 1)).toString() << std::endl;
    // std::cout << ((Term(Fraction(15, 10)) * Part('a') * Part('b') * Part('c') * Part('b') / Part('b')) / (Term(Fraction(1, 2)) * Part('c'))).simplify().at(0).toString() << std::endl;
    Expression expr1 = Expression() + (Term(Fraction(1, 1)) * Part('a')) + (Term(Fraction(1, 1)) * Part('b'));
    Expression expr2 = Expression() + (Term(Fraction(1, 1)) * Part('a')) + (Term(Fraction(1, 1)) * Part('b'));
    std::cout << (expr1 * expr2).simplify().toString() << std::endl;
    return 0;
}