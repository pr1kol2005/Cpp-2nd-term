#include "../point.h"

namespace geometry {
  Point::Point() = default;

  Point::Point(double x, double y) : x_(x), y_(y) {
  }

  Point Point::operator+() const {
    Point result(x_, y_);
    return result;
  }

  Point Point::operator-() const {
    Point result(-x_, -y_);
    return result;
  }

  Vector operator-(Point left, Point right) {
    Vector result(right + (-left));
    return result;
  }

  Point operator+(Point left, Point right) {
    Point result(left.x_ + right.x_, left.y_ + right.y_);
    return result;
  }

  Point Point::operator*(double scalar) const {
    Point result(scalar * x_, scalar * y_);
    return result;
  }

  Point Point::operator/(double scalar) const {
    Point result(scalar / x_, scalar / y_);
    return result;
  }

  IShape& Point::Move(const Vector&) {}
  bool Point::ContainsPoint(const Point&) {}
  bool Point::CrossesSegment(const Segment&) {}
  IShape* Point::Clone() {}
  void Point::ToString() {}
};