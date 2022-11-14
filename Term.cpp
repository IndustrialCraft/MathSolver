#include "Term.hpp"

#include <iostream>

Term::Term(Fraction amount, std::vector<InversablePart> parts) : m_amount(amount), m_parts(parts) {}

Term::Term(Fraction amount) : m_amount(amount), m_parts(std::vector<InversablePart>()) {}

Term::~Term() {}

Term Term::operator*(const Part& part) const {
    std::vector<InversablePart> newParts(m_parts);
    newParts.push_back(InversablePart(part, false));
    return Term(m_amount, newParts);
}
Term Term::operator/(const Part& part) const {
    std::vector<InversablePart> newParts(m_parts);
    newParts.push_back(InversablePart(part, true));
    return Term(m_amount, newParts);
}
Term Term::operator*(const Term& other) const {
    std::vector<InversablePart> parts = m_parts;
    for (const InversablePart& part : other.m_parts) parts.push_back(part);
    return Term(m_amount * other.m_amount, parts);
}
Term Term::operator/(const Term& other) const {
    std::vector<InversablePart> parts = m_parts;
    for (const InversablePart& part : other.m_parts) parts.push_back(InversablePart(part.m_part, !part.m_inverse));
    return Term(m_amount / other.m_amount, parts);
}
Term Term::operator+(const Fraction& amount) const {
    return Term(m_amount + amount, m_parts);
}
Term Term::operator-(const Fraction& amount) const {
    return Term(m_amount - amount, m_parts);
}
Term Term::operator*(const Fraction& amount) const {
    return Term(m_amount * amount, m_parts);
}
Term Term::operator/(const Fraction& amount) const {
    return Term(m_amount / amount, m_parts);
}
Fraction Term::getAmount() {
    return this->m_amount;
}
bool Term::isSameExceptAmount(const Term& other) const {
    return (*this / other).crushOppositeSame().m_parts.size() <= 0;
}
std::vector<Term> Term::simplify() const {
    std::vector<Term> terms;
    terms.push_back(this->crushOppositeSame());
    return terms;
}
std::string Term::toString() const {
    std::string output = m_amount.toString();
    for (const InversablePart& part : m_parts) {
        output += (part.m_inverse ? "/" : "*") + part.m_part.toString();
    }
    return output;
}
Term Term::crushOppositeSame() const {
    std::vector<InversablePart> parts = this->m_parts;
    for (int i = 0; i < parts.size(); i++) {
        InversablePart part1 = parts.at(i);
        for (int j = 0; j < parts.size(); j++) {
            InversablePart part2 = parts.at(j);
            if (part1.m_part == part2.m_part && part1.m_inverse != part2.m_inverse) {
                parts.erase(parts.begin() + j);  // sus
                parts.erase(parts.begin() + i);
                break;
            }
        }
    }
    return Term(m_amount, parts);
}