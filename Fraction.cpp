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

std::string Fraction::toString() const {
    return "(" + std::to_string(m_numerator) + "/" + std::to_string(m_denominator) + ")";
}
