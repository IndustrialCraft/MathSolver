#pragma once
#include <map>
#include <vector>

#include "ExpressionPair.hpp"
#include "Fraction.hpp"

class EquationSystem {
private:
    std::vector<ExpressionPair> m_equations;
public:
    EquationSystem() {}
    ~EquationSystem() {}
public:
    void addEquation(const ExpressionPair& equation);
    std::map<Variable, Fraction> solve() const;
};