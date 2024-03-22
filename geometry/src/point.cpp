#include <iostream>
#include <vector>
#include <string>
#include "../ishape.h"
#include "../point.h"
#include "../vector.h"
#include "../line.h"
#include "../ray.h"
#include "../segment.h"
#include "../polygon.h"
#include "../circle.h"

namespace geometry {
bool IsPointOnLine(const Point& a, const Point& b, const Point& p) {
  Vector ab(a, b);
  Vector ap(a, p);
  return ab.CrossProduct(ap) == 0;
};

bool IsPointOnSegment(const Point& a, const Point& b, const Point& p) {
  if (!IsPointOnLine(a, b, p)) {
    return false;
  }
  Vector ab(a, b);
  Vector ap(a, p);
  int64_t scalar_product = ab.ScalarProduct(ap);
  if (scalar_product < 0) {
    return false;
  }
  return scalar_product <= ab.LengthSquared();
};

Point::Point() = default;

Point::Point(int64_t x, int64_t y) : x_(x), y_(y) {
}

Point::Point(const Point& p) : x_(p.x_), y_(p.y_) {
}

Point Point::operator+() const {
  Point result(x_, y_);
  return result;
}

Point Point::operator-() const {
  Point result(-x_, -y_);
  return result;
}

Vector Point::operator-(const Point& other) const {
  Vector result = Vector(other, *this);
  return result;
}

Point& Point::Move(const Vector& vector) {
  x_ += vector.x_;
  y_ += vector.y_;
  return *this;
}

bool Point::ContainsPoint(const Point& point) const {
  return (point.x_ == x_ && point.y_ == y_);
}

bool Point::CrossesSegment(const Segment& segment) const {
  return IsPointOnSegment(segment.a_, segment.b_, *this);
}

Point* Point::Clone() const {
  auto result = new Point(x_, y_);
  return result;
}

std::string Point::ToString() const {
  return "Point(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
}

Point::~Point() = default;
};  // namespace geometry