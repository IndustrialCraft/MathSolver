#pragma once
#include <string>
#include <vector>
class Term;

class Expression {
public:
private:
    std::vector<Term> m_terms;
public:
    Expression(std::vector<Term> terms) : m_terms(terms) {}
    Expression() : m_terms(std::vector<Term>()) {}
    ~Expression();
public:
    Expression operator+(const Term& term) const;
    Expression operator+(const Expression& other) const;
    Expression operator-(const Expression& other) const;
    Expression operator*(const Expression& other) const;
    // todo Expression operator/(const Expression& other) const;
public:
    Expression simplify() const;
    std::string toString() const;
    std::vector<Term> getTerms() const;
private:
    Expression simplifyTerms() const;
};