#include "rational.h"

Rational::Rational() : numerator_(0), denominator_(1) {
}

Rational::Rational(int integer) : numerator_(integer), denominator_(1) {
}

Rational::Rational(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {
  if (denominator == 0) {
    throw RationalDivisionByZero();
  }
  ReduceFraction();
}

Rational& Rational::ReduceFraction() {
  int common_divisor = GCD(abs(numerator_), abs(denominator_));
  numerator_ = (denominator_ / abs(denominator_)) * (numerator_ / common_divisor);
  denominator_ = abs(denominator_ / common_divisor);
  return *this;
}

int Rational::GetNumerator() const {
  return numerator_;
}

int Rational::GetDenominator() const {
  return denominator_;
}

void Rational::SetNumerator(int numerator) {
  numerator_ = numerator;
  ReduceFraction();
}

void Rational::SetDenominator(int denominator) {
  if (denominator == 0) {
    throw RationalDivisionByZero();
  }
  denominator_ = denominator;
  ReduceFraction();
}

Rational operator+(Rational left, Rational right){
  Rational result(left.numerator_ * right.denominator_ + right.numerator_ * left.denominator_,
                  left.denominator_ * right.denominator_);
  return result;
}

Rational operator-(Rational left, Rational right){
  Rational result(left.numerator_ * right.denominator_ - right.numerator_ * left.denominator_,
                  left.denominator_ * right.denominator_);
  return result;
}

Rational operator*(Rational left, Rational right){
  Rational result(left.numerator_ * right.numerator_, left.denominator_ * right.denominator_);
  return result;
}

Rational operator/(Rational left, Rational right){
  if (right.numerator_ == 0) {
    throw RationalDivisionByZero();
  }
  Rational result(left.numerator_ * right.denominator_, left.denominator_ * right.numerator_);
  return result;
}

Rational& operator+=(Rational& left, Rational right) {
  left.numerator_ = left.numerator_ * right.denominator_ + right.numerator_ * left.denominator_;
  left.denominator_ = left.denominator_ * right.denominator_;
  return left.ReduceFraction();
}

Rational& operator-=(Rational& left, Rational right) {
  left.numerator_ = left.numerator_ * right.denominator_ - right.numerator_ * left.denominator_;
  left.denominator_ = left.denominator_ * right.denominator_;
  return left.ReduceFraction();
}

Rational& operator*=(Rational& left, Rational right) {
  left.numerator_ = left.numerator_ * right.numerator_;
  left.denominator_ = left.denominator_ * right.denominator_;
  return left.ReduceFraction();
}

Rational& operator/=(Rational& left, Rational right) {
  if (right.numerator_ == 0) {
    throw RationalDivisionByZero();
  }
  left.numerator_ = left.numerator_ * right.denominator_;
  left.denominator_ = left.denominator_ * right.numerator_;
  return left.ReduceFraction();
}

bool operator<(Rational left, Rational right) {
  return left.numerator_ * right.denominator_ < left.denominator_ * right.numerator_;
}

bool operator<=(Rational left, Rational right) {
  return left.numerator_ * right.denominator_ <= left.denominator_ * right.numerator_;
}

bool operator==(Rational left, Rational right) {
  return left.numerator_ * right.denominator_ == left.denominator_ * right.numerator_;
}

bool operator>=(Rational left, Rational right) {
  return left.numerator_ * right.denominator_ >= left.denominator_ * right.numerator_;
}

bool operator>(Rational left, Rational right) {
  return left.numerator_ * right.denominator_ > left.denominator_ * right.numerator_;
}

Rational Rational::operator+() const {
  Rational result(numerator_, denominator_);
  return result;
}

Rational Rational::operator-() const {
  Rational result(-numerator_, denominator_);
  return result;
}

Rational& Rational::operator++() {
  numerator_ += denominator_;
  return (*this);
}

Rational& Rational::operator--() {
  numerator_ -= denominator_;
  return (*this);
}

Rational Rational::operator++(int) {
  Rational old_value = *this;
  numerator_ += denominator_;
  return old_value;
}

Rational Rational::operator--(int) {
  Rational old_value = *this;
  numerator_ -= denominator_;
  return old_value;
}

std::istream& operator>>(std::istream& is, Rational& fraction) {
  int numerator = 0;
  int denominator = 1;
  char divider = ' ';
  is >> numerator;
  if (is.peek() == '/') {
    is >> divider >> denominator;
  }
  if (denominator == 0) {
    throw RationalDivisionByZero();
  }
  fraction.numerator_ = numerator;
  fraction.denominator_ = denominator;
  fraction.ReduceFraction();
  return is;
}

std::ostream& operator<<(std::ostream& os, const Rational& fraction) {
  if (fraction.denominator_ == 1) {
    return os << fraction.numerator_;
  }
  return os << fraction.numerator_ << "/" << fraction.denominator_;
}

int GCD(int a, int b) {
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}