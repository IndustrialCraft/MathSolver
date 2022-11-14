#pragma once
#include <string>

class Part {
private:
    char m_symbol;
public:
    Part(char symbol);
    ~Part();
public:
    bool operator==(const Part& other) const;
public:
    std::string toString() const;
};