#include "../vector.h"

namespace geometry {
Vector::Vector() = default;

Vector::Vector(int64_t x, int64_t y) : x_(x), y_(y) {
}

Vector::Vector(const Point& p1, const Point& p2) : x_(p2.x_ - p1.x_), y_(p2.y_ - p1.y_) {
}

Vector Vector::operator+() const {
  Vector result(x_, y_);
  return result;
}

Vector Vector::operator-() const {
  Vector result(-x_, -y_);
  return result;
}

Vector operator+(Vector left, Vector right) {
  Vector result(left.x_ + right.x_, left.y_ + right.y_);
  return result;
}

Vector operator-(Vector left, Vector right) {
  Vector result = left + (-right);
  return result;
}

Vector Vector::operator*(int64_t scalar) const {
  Vector result(x_ * scalar, y_ * scalar);
  return result;
}

Vector Vector::operator/(int64_t scalar) const {
  Vector result(x_ / scalar, y_ / scalar);
  return result;
}

Vector& operator+=(Vector& left, Vector right) {
  left.x_ += right.x_;
  right.y_ += right.y_;
  return left;
}

Vector& operator-=(Vector& left, Vector right) {
  left.x_ -= right.x_;
  right.y_ -= right.y_;
  return left;
}

Vector& operator*=(Vector& vector, int64_t scalar) {
  vector.x_ *= scalar;
  vector.y_ *= scalar;
  return vector;
}

Vector& operator/=(Vector& vector, int64_t scalar) {
  vector.x_ /= scalar;
  vector.y_ /= scalar;
  return vector;
}

bool operator==(Vector left, Vector right) {
  return left.x_ == right.x_ && left.y_ == right.y_;
}

int64_t Vector::LengthSquared() const {
  return x_ * x_ + y_ * y_;
}

int64_t Vector::CrossProduct(const Vector& other) const {
  return x_ * other.y_ - y_ * other.x_;
}

int64_t Vector::ScalarProduct(const Vector& other) const {
  return x_ * other.x_ + y_ * other.y_;
}

std::string Vector::ToString() const {
  return "Vector(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
}
};  // namespace geometry