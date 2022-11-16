#pragma once
#include <string>

class Variable {
private:
    char m_symbol;
public:
    Variable(char symbol);
    ~Variable();
public:
    bool operator==(const Variable& other) const;
    bool operator<(const Variable& other) const;
public:
    std::string toString() const;
};