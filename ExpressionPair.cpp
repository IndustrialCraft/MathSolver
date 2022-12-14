#include "ExpressionPair.hpp"

#include "Term.hpp"

ExpressionPair::ExpressionPair(Expression first, Expression second, EOperator mathOperator) : m_first(first), m_second(second), m_operator(mathOperator) {}

ExpressionPair::~ExpressionPair() {}

ExpressionPair ExpressionPair::solveFor(Variable var) const {
    Expression first = this->m_first.simplify();
    Expression second = this->m_second.simplify();
    EOperator mathOperator = this->m_operator;
    while (true) {
        bool skip = false;
        for (const Term& term : first.getTerms()) {
            if (term.countOccurences(var) == 0) {
                first = (first + (term * Fraction(-1, 1))).simplify();
                second = (second + (term * Fraction(-1, 1))).simplify();
                skip = true;
                break;
            }
        }
        if (skip)
            continue;
        for (const Term& term : second.getTerms()) {
            if (term.countOccurences(var) != 0) {
                first = (first + (term * Fraction(-1, 1))).simplify();
                second = (second + (term * Fraction(-1, 1))).simplify();
                skip = true;
                break;
            }
        }
        break;
        if (!skip)
            break;
    }
    while (true) {
        for (const Term& term : first.getTerms()) {
            for (const auto& part : term.getParts()) {
                Variable v = std::get<Variable>(part.m_part);
                if (!(v == var)) {
                    if (part.m_inverse) {
                        first = first * (Term(Fraction(1, 1)) * v);
                        second = second * (Term(Fraction(1, 1)) * v);
                    } else {
                        first = first / (Term(Fraction(1, 1)) * v);
                        second = second / (Term(Fraction(1, 1)) * v);
                    }
                    goto next;
                }
            }
        }
        break;
    next:
        continue;
    }
    if (first.getTerms().size() > 0) {
        Fraction onLeft = first.getTerms().at(0).getAmount();
        if (onLeft.isNegative())
            mathOperator = getOtherOperator();
        first = first / Term(onLeft);
        second = second / Term(onLeft);
    }
    return ExpressionPair(first, second, mathOperator);
}

ExpressionPair::EOperator ExpressionPair::getOtherOperator() const {
    switch (m_operator) {
        case EOperator::EQUALS:
            return EOperator::EQUALS;
        case EOperator::LESS:
            return EOperator::GREATER;
        case EOperator::LESS_EQ:
            return EOperator::GREATER_EQ;
        case EOperator::GREATER:
            return EOperator::LESS;
        case EOperator::GREATER_EQ:
            return EOperator::LESS_EQ;
    }
    throw std::logic_error("this shouldnt happen");
}
bool ExpressionPair::isCompletlySolved(Variable var) const {
    if (m_first.getTerms().size() != 1)
        return false;
    Term term = m_first.getTerms().at(0);
    if (!(term.getAmount() == Fraction(1, 1)))
        return false;
    if (term.getParts().size() != 1)
        return false;
    if (term.getParts().at(0).m_inverse)
        return false;
    if (!std::holds_alternative<Variable>(term.getParts().at(0).m_part))
        return false;
    return std::get<Variable>(term.getParts().at(0).m_part) == var;
}
Expression ExpressionPair::getFirst() const {
    return this->m_first;
}
Expression ExpressionPair::getSecond() const {
    return this->m_second;
}
ExpressionPair::EOperator ExpressionPair::getOperator() const {
    return this->m_operator;
}