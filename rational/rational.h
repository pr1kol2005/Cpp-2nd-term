#pragma once

#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string_view>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
  int numerator_;
  int denominator_;

 public:
  Rational();
  Rational(int integer);  // NOLINT
  Rational(int numerator, int denominator);
  Rational& ReduceFraction();
  int GetNumerator() const;
  int GetDenominator() const;
  void SetNumerator(int numerator);
  void SetDenominator(int denominator);
  friend Rational operator+(Rational left, Rational right);
  friend Rational operator-(Rational left, Rational right);
  friend Rational operator*(Rational left, Rational right);
  friend Rational operator/(Rational left, Rational right);
  friend Rational& operator+=(Rational& left, Rational right);
  friend Rational& operator-=(Rational& left, Rational right);
  friend Rational& operator*=(Rational& left, Rational right);
  friend Rational& operator/=(Rational& left, Rational right);
  friend bool operator<(Rational left, Rational right);
  friend bool operator<=(Rational left, Rational right);
  friend bool operator==(Rational left, Rational right);
  friend bool operator>=(Rational left, Rational right);
  friend bool operator>(Rational left, Rational right);
  Rational operator+() const;
  Rational operator-() const;
  Rational& operator++();
  Rational& operator--();
  Rational operator++(int);
  Rational operator--(int);
  friend std::istream& operator>>(std::istream& is, Rational& fraction);
  friend std::ostream& operator<<(std::ostream& os, const Rational& fraction);
};

int GCD(int a, int b);
