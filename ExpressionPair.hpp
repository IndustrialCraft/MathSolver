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
    ExpressionPair solveFor(Variable var);
    Expression getFirst();
    Expression getSecond();
    EOperator getOperator();
private:
    EOperator getOtherOperator();
};