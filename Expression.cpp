#include "Expression.hpp"

#include <iostream>

Expression::~Expression() {}

Expression Expression::operator+(const Term& term) const {
    std::vector<Term> terms = m_terms;
    terms.push_back(term);
    return Expression(terms);
}
Expression Expression::operator+(const Expression& other) const {
    std::vector<Term> terms = m_terms;
    for (const Term& term : other.m_terms) terms.push_back(term);
    return Expression(terms);
}
Expression Expression::operator-(const Expression& other) const {
    std::vector<Term> terms = m_terms;
    for (const Term& term : other.m_terms) terms.push_back(term * Fraction(-1, 1));
    return Expression(terms);
}
Expression Expression::operator*(const Expression& other) const {
    std::vector<Term> terms;
    for (const Term& term1 : this->m_terms) {
        for (const Term& term2 : other.m_terms) {
            terms.push_back(term1 * term2);
        }
    }
    return Expression(terms);
}
Expression Expression::simplify() const {
    std::vector<Term> terms;
    Expression simplifiedTerms = simplifyTerms();
    for (const Term& term : simplifiedTerms.m_terms) {
        bool found = false;
        for (int i = 0; i < terms.size(); i++) {
            if (term.isSameExceptAmount(terms.at(i))) {
                terms.at(i) = term + terms.at(i).getAmount();
                if (terms.at(i).getAmount().isZero())
                    terms.erase(terms.begin() + i);
                found = true;
                break;
            }
        }
        if (!found) {
            terms.push_back(term);
        }
    }
    return Expression(terms);
}
Expression Expression::simplifyTerms() const {
    std::vector<Term> terms;
    for (const Term& term : m_terms) {
        for (const Term& term2 : term.simplify()) {
            terms.push_back(term2);
        }
    }
    return terms;
}
std::string Expression::toString() const {
    std::string output;
    for (const Term& term1 : this->m_terms) {
        output += "+" + term1.toString();
    }
    return output;
}