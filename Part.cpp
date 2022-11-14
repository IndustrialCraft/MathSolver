#include "Part.hpp"

#include <iostream>

Part::Part(char symbol) : m_symbol(symbol) {}

Part::~Part() {}

bool Part::operator==(const Part& other) const {
    return this->m_symbol == other.m_symbol;
}

std::string Part::toString() const {
    return std::string() + m_symbol;
}