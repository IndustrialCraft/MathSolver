#include "Fraction.hpp"

#include <cassert>
#include <numeric>

Fraction::Fraction(long long numerator, long long denominator) {
    if (denominator == 0) {
        throw new Fraction::NullDenominatorException();
    }
    int multiplier = denominator < 0 ? -1 : 1;
    long long gcd = std::gcd(numerator, denominator);
    this->m_numerator = numerator / gcd * multiplier;
    this->m_denominator = denominator / gcd * multiplier;
}

Fraction::~Fraction() {}
Fraction Fraction::operator+(const Fraction& other) const {
    long long lcm = std::lcm(this->m_denominator, other.m_denominator);
    return Fraction((this->m_numerator * (lcm / this->m_denominator)) + (other.m_numerator * (lcm / other.m_denominator)), lcm);
}
Fraction Fraction::operator-(const Fraction& other) const {
    long long lcm = std::lcm(this->m_denominator, other.m_denominator);
    return Fraction((this->m_numerator * (lcm / this->m_denominator)) - (other.m_numerator * (lcm / other.m_denominator)), lcm);
}
Fraction Fraction::operator*(const Fraction& other) const {
    return Fraction(this->m_numerator * other.m_numerator, this->m_denominator * other.m_denominator);
}
Fraction Fraction::operator/(const Fraction& other) const {
    return Fraction(this->m_numerator * other.m_denominator, this->m_denominator * other.m_numerator);
}
bool Fraction::operator==(const Fraction& other) const {
    return this->m_numerator == other.m_numerator && this->m_denominator == other.m_denominator;
}
bool Fraction::isNegative() const {
    return this->m_numerator < 0;
}
bool Fraction::isZero() const {
    return this->m_numerator == 0;
}
long long Fraction::getNumberator() const {
    return this->m_numerator;
}
long long Fraction::getDenominator() const {
    return this->m_denominator;
}
std::string Fraction::toString(bool ignoreNegative) const {
    std::string output;
    output += std::to_string(ignoreNegative ? abs(m_numerator) : m_numerator);
    if (m_denominator != 1) {
        output += "/" + std::to_string(m_denominator);
    }
    return output;
}
