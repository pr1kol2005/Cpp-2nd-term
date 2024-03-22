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
bool IsPointOnLineL(const Point& a, const Point& b, const Point& p) {
  Vector ab(a, b);
  Vector ap(a, p);
  if (ab.LengthSquared() != 0) {
    return ab.CrossProduct(ap) == 0;
  }
  return a.ContainsPoint(p);
};

bool IsSegmentCrossesLineL(const Point& a, const Point& b, const Point& c, const Point& d) {
  Vector ab(a, b);
  Vector ac(a, c);
  Vector ad(a, d);
  return ab.CrossProduct(ac) * ab.CrossProduct(ad) <= 0;
};

Line::Line() = default;

Line::Line(const Point& a, const Point& b) : a_(a), b_(b) {
}

Line& Line::Move(const Vector& vector) {
  a_.Move(vector);
  b_.Move(vector);
  return *this;
}

bool Line::ContainsPoint(const Point& point) const {
  return IsPointOnLineL(a_, b_, point);
}

bool Line::CrossesSegment(const Segment& segment) const {
  return IsSegmentCrossesLineL(a_, b_, segment.a_, segment.b_);
}

Line* Line::Clone() const {
  Line* result = new Line(a_, b_);
  return result;
}

std::string Line::ToString() const {
  return "Line(" + std::to_string(a_.y_ - b_.y_) + ", " + std::to_string(b_.x_ - a_.x_) + ", " +
         std::to_string(a_.x_ * b_.y_ - a_.y_ * b_.x_) + ")";
}

Line::~Line() = default;
};  // namespace geometry