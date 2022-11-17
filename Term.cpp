#include "Term.hpp"

#include <cassert>
#include <iostream>

Term::Term(Fraction amount, std::vector<InversablePart> parts) : m_amount(amount), m_parts(parts) {}

Term::Term(Fraction amount) : m_amount(amount), m_parts(std::vector<InversablePart>()) {}

Term::~Term() {}

Term Term::operator*(const Variable& part) const {
    std::vector<InversablePart> newVariables(m_parts);
    newVariables.push_back(InversablePart(part, false));
    return Term(m_amount, newVariables);
}
Term Term::operator/(const Variable& part) const {
    std::vector<InversablePart> newVariables(m_parts);
    newVariables.push_back(InversablePart(part, true));
    return Term(m_amount, newVariables);
}
Term Term::operator*(const Expression& part) const {
    return addInversiblePart(InversablePart(part, false));
}
Term Term::operator/(const Expression& part) const {
    return addInversiblePart(InversablePart(part, true));
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
Term Term::replaceVariable(Variable variable, Expression expression) const {
    std::vector<InversablePart> parts;
    for (const auto& part : this->m_parts) {
        if (std::holds_alternative<Variable>(part.m_part)) {
            if (std::get<Variable>(part.m_part) == variable) {
                parts.push_back(InversablePart(expression, part.m_inverse));
            }
        } else {
            parts.push_back(InversablePart(std::get<Expression>(part.m_part).replaceVariable(variable, expression), part.m_inverse));
        }
    }
    return Term(m_amount, parts);
}
std::set<Variable> Term::listVariables() const {
    std::set<Variable> variables;
    for (const auto& part : this->m_parts) {
        if (std::holds_alternative<Variable>(part.m_part)) {
            variables.insert(std::get<Variable>(part.m_part));
        } else {
            auto extracted = std::get<Expression>(part.m_part).listVariables();
            variables.insert(extracted.begin(), extracted.end());
        }
    }
    return variables;
}
std::vector<Term::InversablePart> Term::getParts() const {
    return this->m_parts;
}
int Term::countOccurences(const Variable& var) const {
    int amt = 0;
    for (const auto& part : this->m_parts) {
        if (std::holds_alternative<Variable>(part.m_part)) {
            if (std::get<Variable>(part.m_part) == var) {
                amt += part.m_inverse ? -1 : 1;
            }
        }
    }
    return amt;
}
Fraction Term::getAmount() const {
    return this->m_amount;
}
bool Term::isSameExceptAmount(const Term& other) const {
    return (*this / other).crushOppositeSame().m_parts.size() <= 0;
}
std::vector<Term> Term::simplify() const {
    std::vector<Term> terms;
    terms.push_back(Term(m_amount));
    for (const InversablePart& part : m_parts) {
        if (std::holds_alternative<Variable>(part.m_part)) {
            Variable var = std::get<Variable>(part.m_part);
            for (int i = 0; i < terms.size(); i++) {
                terms.at(i) = terms.at(i).addInversiblePart(part);
            }
        } else if (std::holds_alternative<Expression>(part.m_part)) {
            if (part.m_inverse) {
                throw std::logic_error("dividing not implemented");
            }
            Expression expr = std::get<Expression>(part.m_part).simplify();
            std::vector<Term> newTerms;
            for (const Term& term1 : terms) {
                for (const Term& term2 : expr.getTerms()) {
                    newTerms.push_back(term1 * term2);
                }
            }
            terms = newTerms;
        } else {
            assert(!"this shouldnt happen");
        }
    }
    for (int i = 0; i < terms.size(); i++) terms.at(i) = (terms.at(i).crushOppositeSame());
    return terms;
}
Term Term::addInversiblePart(const InversablePart& part) const {
    std::vector<InversablePart> newVariables(m_parts);
    newVariables.push_back(part);
    return Term(m_amount, newVariables);
}
std::string Term::toString(bool ignoreNegativeAmount) const {
    std::string output;
    if ((!((m_amount == Fraction(1, 1)) || (m_amount == Fraction(-1, 1)))) || m_parts.size() <= 0) {
        output += m_amount.toString(ignoreNegativeAmount);
    }
    bool first = true;
    for (const InversablePart& part : m_parts) {
        if (std::holds_alternative<Variable>(part.m_part))
            output += (part.m_inverse ? "/" : (first ? "" : "*")) + std::get<Variable>(part.m_part).toString();
        else
            output += std::string((part.m_inverse ? "/" : (first ? "" : "*"))) + "(" + std::get<Expression>(part.m_part).toString() + ")";
        first = true;
    }
    return output;
}
Term Term::crushOppositeSame() const {
    std::vector<InversablePart> parts = this->m_parts;
    for (int i = 0; i < parts.size(); i++) {
        InversablePart part1 = parts.at(i);
        for (int j = 0; j < parts.size(); j++) {
            InversablePart part2 = parts.at(j);
            if (std::get<Variable>(part1.m_part) == std::get<Variable>(part2.m_part) && part1.m_inverse != part2.m_inverse) {
                parts.erase(parts.begin() + j);
                parts.erase(parts.begin() + i);
                i--;
                break;
            }
        }
    }
    return Term(m_amount, parts);
}