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
Circle::Circle() = default;

Circle::Circle(const Point& center, int64_t radius) : center_(center), r_(radius) {
}

Circle& Circle::Move(const Vector& vector) {
  center_.Move(vector);
  return *this;
}

bool Circle::ContainsPoint(const Point& point) const {
  return (point - center_).LengthSquared() <= r_ * r_;
}

bool Circle::ContainsPointWithoutHull(const Point& point) const {
  return (point - center_).LengthSquared() < r_ * r_;
}

bool Circle::CrossesSegment(const Segment& segment) const {
  Vector ab(segment.a_, segment.b_);
  Vector ba(segment.b_, segment.a_);
  Vector ao(segment.a_, center_);
  Vector bo(segment.b_, center_);
  if (ContainsPointWithoutHull(segment.a_) && ContainsPointWithoutHull(segment.b_)) {
    return false;
  }
  if (ao.ScalarProduct(ab) <= 0) {
    return ContainsPoint(segment.a_);
  }
  if (bo.ScalarProduct(ba) <= 0) {
    return ContainsPoint(segment.b_);
  }
  return (ao.CrossProduct(ab) * ao.CrossProduct(ab) <=  ab.LengthSquared() * r_ * r_);
}

Circle* Circle::Clone() const {
  auto result = new Circle(center_, r_);
  return result;
}

std::string Circle::ToString() const {
  return "Circle(" + center_.ToString() + ", " + std::to_string(r_) + ")";
}

Circle::~Circle() = default;
};  // namespace geometry