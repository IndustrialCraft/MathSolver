#pragma once
#include "Expression.hpp"
#include "Variable.hpp"

class ExpressionPair {
public:
    enum EOperator {
        EQUALS,
        LESS,
        GREATER,
        LESS_EQ,
        GREATER_EQ,
    };
private:
    Expression m_first;
    Expression m_second;
    EOperator m_operator;
public:
    ExpressionPair(Expression first, Expression second, EOperator mathOperator);
    ~ExpressionPair();
public:
    bool isCompletlySolved(Variable var) const;
    ExpressionPair solveFor(Variable var) const;
    Expression getFirst() const;
    Expression getSecond() const;
    EOperator getOperator() const;
private:
    EOperator getOtherOperator() const;
};