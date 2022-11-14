#pragma once
#include <vector>

#include "Fraction.hpp"
#include "Part.hpp"

class Term {
public:
    class InversablePart {
    public:
        Part m_part;
        bool m_inverse;
    public:
        InversablePart(Part part, bool inverse) : m_part(part), m_inverse(inverse) {}
    };
private:
    Fraction m_amount;
    std::vector<InversablePart> m_parts;
public:
    Term(Fraction amount, std::vector<InversablePart> parts);
    Term(Fraction amount);
    ~Term();
public:
    Term operator*(const Part& part) const;
    Term operator/(const Part& part) const;
    Term operator*(const Term& other) const;
    Term operator/(const Term& other) const;
    Term operator+(const Fraction& amount) const;
    Term operator-(const Fraction& amount) const;
    Term operator*(const Fraction& amount) const;
    Term operator/(const Fraction& amount) const;
public:
    Fraction getAmount();
    bool isSameExceptAmount(const Term& other) const;
    std::string toString() const;
    std::vector<Term> simplify() const;
private:
    Term crushOppositeSame() const;
};