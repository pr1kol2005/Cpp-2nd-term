#include "../vector.h"

namespace geometry {
  Vector::Vector() = default;

  Vector::Vector(Point point) : arrow_(point) {}

  Vector Vector::operator+() const {
    Vector result(arrow_);
    return result;
  }

  Vector Vector::operator-() const {
    Vector result(-arrow_);
    return result;
  }

  Vector operator+(Vector left, Vector right) {
    Vector result(Point(left.arrow_ + right.arrow_));
    return result;
  }

  Vector operator-(Vector left, Vector right) {
    Vector result = left + (-right);
    return result;
  }

  Vector Vector::operator*(double scalar) const {
    Vector result(arrow_ * scalar);
    return result;
  }

  Vector Vector::operator/(double scalar) const {
    Vector result(arrow_ / scalar);
    return result;
  }

  Vector& operator+=(Vector& left, Vector right) {
    left.arrow_ = left.arrow_ + right.arrow_;
    return left;
  }

  Vector& operator-=(Vector& left, Vector right) {
    left.arrow_ = left.arrow_ + right.arrow_;
    return left;
  }

  Vector& operator*=(Vector& vector, double scalar) {
    vector.arrow_ = vector.arrow_ * scalar;
    return vector;
  }

  Vector& operator/=(Vector& vector, double scalar) {
    vector.arrow_ = vector.arrow_ / scalar;
    return vector;
  }

  bool operator==(Vector left, Vector right) {
    return left.arrow_ == right.arrow_;
  }
}