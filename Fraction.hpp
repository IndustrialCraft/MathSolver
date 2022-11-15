#pragma once
#include <stdexcept>
#include <string>

class Fraction {
public:
    class NullDenominatorException : public std::runtime_error {
    public:
        NullDenominatorException() : std::runtime_error("attempting to create null-denominator fraction") {}
    };
private:
    long long m_numerator;
    long long m_denominator;
public:
    Fraction(long long numerator, long long denominator);
    ~Fraction();
public:
    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;
    bool operator==(const Fraction& other) const;
public:
    bool isNegative() const;
    bool isZero() const;
    std::string toString() const;
};