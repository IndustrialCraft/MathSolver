#pragma once
#include <variant>
#include <vector>

#include "Expression.hpp"
#include "Fraction.hpp"
#include "Variable.hpp"

class Term {
public:
    class InversablePart {
    public:
        std::variant<Expression, Variable> m_part;
        bool m_inverse;
    public:
        InversablePart(std::variant<Expression, Variable> part, bool inverse) : m_part(part), m_inverse(inverse) {}
    };
private:
    Fraction m_amount;
    std::vector<InversablePart> m_parts;
public:
    Term(Fraction amount, std::vector<InversablePart> parts);
    Term(Fraction amount);
    ~Term();
public:
    Term operator*(const Variable& part) const;
    Term operator/(const Variable& part) const;
    Term operator*(const Expression& part) const;
    Term operator/(const Expression& part) const;
    Term operator*(const Term& other) const;
    Term operator/(const Term& other) const;
    Term operator+(const Fraction& amount) const;
    Term operator-(const Fraction& amount) const;
    Term operator*(const Fraction& amount) const;
    Term operator/(const Fraction& amount) const;
public:
    std::set<Variable> listVariables() const;
    Term replaceVariable(Variable variable, Expression expression) const;
    std::vector<InversablePart> getParts() const;
    int countOccurences(const Variable& var) const;
    Term addInversiblePart(const InversablePart& part) const;
    Fraction getAmount() const;
    bool isSameExceptAmount(const Term& other) const;
    std::string toString(bool ignoreNegativeAmount) const;
    std::vector<Term> simplify() const;
private:
    Term crushOppositeSame() const;
};