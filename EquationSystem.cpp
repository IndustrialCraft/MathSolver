#include "EquationSystem.hpp"

#include <iostream>

#include "Term.hpp"

void EquationSystem::addEquation(const ExpressionPair& equation) {
    if (equation.getOperator() != ExpressionPair::EOperator::EQUALS)
        throw std::runtime_error("only equations can be used in equation system");
    this->m_equations.push_back(equation);
}
std::map<Variable, Fraction> EquationSystem::solve() const {
    std::set<Variable> usedVariables;
    for (const auto& equation : m_equations) {
        auto extractedFirst = equation.getFirst().listVariables();
        usedVariables.insert(extractedFirst.begin(), extractedFirst.end());
        auto extractedSecond = equation.getSecond().listVariables();
        usedVariables.insert(extractedSecond.begin(), extractedSecond.end());
    }
    if (usedVariables.size() != m_equations.size())
        throw std::runtime_error("number of variables must be same as equation count");
    std::map<Variable, Expression> calculated;
    std::map<Variable, Fraction> results;
    int i = 0;
    for (Variable var : usedVariables) {
        ExpressionPair pair = m_equations.at(i).solveFor(var);
        if (!pair.isCompletlySolved(var))
            throw std::runtime_error("cannot completly solve equation");
        Expression expr = pair.getSecond();
        for (const auto& pair : calculated) {
            expr = (expr.replaceVariable(pair.first, pair.second)).simplify();
        }
        pair = ExpressionPair(pair.getFirst(), expr, ExpressionPair::EOperator::EQUALS).solveFor(var);
        calculated.insert(std::pair<Variable, Expression>(var, pair.getSecond()));
        i++;
    }
    std::vector<Variable> variables(usedVariables.begin(), usedVariables.end());
    std::reverse(variables.begin(), variables.end());
    i = 0;
    for (const auto& var : variables) {
        Expression expr = calculated.at(var);
        for (const auto& pair : results) {
            expr = expr.replaceVariable(pair.first, Expression() + Term(pair.second)).simplify();
        }
        ExpressionPair ep(Expression() + (Term(Fraction(1, 1)) * var), expr, ExpressionPair::EOperator::EQUALS);
        Expression res = ep.solveFor(var).getSecond();
        results.insert(std::pair<Variable, Fraction>(var, res.getTerms().at(0).getAmount()));
        i++;
    }
    return results;
}