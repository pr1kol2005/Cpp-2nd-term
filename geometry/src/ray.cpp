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
bool IsPointOnLineR(const Point& a, const Point& b, const Point& p) {
  Vector ab(a, b);
  Vector ap(a, p);
  if (ab.LengthSquared() != 0) {
    return ab.CrossProduct(ap) == 0;
  }
  return a.ContainsPoint(p);
};

bool IsPointOnRay(const Point& a, const Point& b, const Point& p) {
  if (!IsPointOnLineR(a, b, p)) {
    return false;
  }
  Vector ab(a, b);
  Vector ap(a, p);
  if (ab.LengthSquared() != 0) {
    return ab.ScalarProduct(ap) >= 0;
  }
  return a.ContainsPoint(p);
};

bool IsSegmentCrossesRay(const Point& a, const Point& b, const Point& c, const Point& d) {
  if (IsPointOnRay(a, b, c) || IsPointOnRay(a, b, d)) {
    return true;
  }
  Vector ab(a, b);
  Vector ac(a, c);
  Vector ad(a, d);
  Vector cd(c, d);
  Vector ca(c, a);
  Vector cb(c, b);
  if (ab.LengthSquared() != 0 && cd.LengthSquared() != 0) {
    return ((ab.CrossProduct(ac) * ab.CrossProduct(ad) <= 0) && (cd.CrossProduct(ca) * cd.CrossProduct(cb) <= 0));
  }
  if (ab.LengthSquared() != 0) {
    return IsPointOnRay(a, b, c);
  }
  if (cd.LengthSquared() != 0) {
    return Segment(c, d).ContainsPoint(a);
  }
  return a.ContainsPoint(c);
};

Ray::Ray() = default;

Ray::Ray(const Point& a, const Point& b) : a_(a), b_(b) {
}

Ray& Ray::Move(const Vector& vector) {
  a_.Move(vector);
  b_.Move(vector);
  return *this;
}

bool Ray::ContainsPoint(const Point& point) const {
  return IsPointOnRay(a_, b_, point);
}

bool Ray::CrossesSegment(const Segment& segment) const {
  return IsSegmentCrossesRay(a_, b_, segment.a_, segment.b_);
}

Ray* Ray::Clone() const {
  Ray* result = new Ray(a_, b_);
  return result;
}

std::string Ray::ToString() const {
  return "Ray(" + a_.ToString() + ", " + (b_ - a_).ToString() + ")";
}

Ray::~Ray() = default;
};  // namespace geometry