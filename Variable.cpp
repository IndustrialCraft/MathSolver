#include "Variable.hpp"

#include <iostream>

Variable::Variable(char symbol) : m_symbol(symbol) {}

Variable::~Variable() {}

bool Variable::operator==(const Variable& other) const {
    return this->m_symbol == other.m_symbol;
}

std::string Variable::toString() const {
    return std::string() + m_symbol;
}