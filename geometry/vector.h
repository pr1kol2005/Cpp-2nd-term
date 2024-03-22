#pragma once

#include <string>

#include "point.h"

namespace geometry {

class Vector {
 public:
  int64_t x_;
  int64_t y_;

 public:
  Vector();
  Vector(const Point& p1, const Point& p2);
  Vector(int64_t x, int64_t y);

  Vector operator+() const;
  Vector operator-() const;
  friend Vector operator+(const Vector left, const Vector right);
  friend Vector operator-(const Vector left, const Vector right);
  Vector operator*(int64_t scalar) const;
  Vector operator/(int64_t scalar) const;
  friend Vector& operator+=(Vector& left, Vector right);
  friend Vector& operator-=(Vector& left, Vector right);
  friend Vector& operator*=(Vector& vector, int64_t scalar);
  friend Vector& operator/=(Vector& vector, int64_t scalar);
  friend bool operator==(Vector left, Vector right);

  int64_t LengthSquared() const;
  int64_t CrossProduct(const Vector& other) const;
  int64_t ScalarProduct(const Vector& other) const;
  std::string ToString() const;
};
};  // namespace geometry