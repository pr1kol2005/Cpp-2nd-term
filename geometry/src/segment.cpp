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
bool IsPointOnLineS(const Point& a, const Point& b, const Point& p) {
  Vector ab(a, b);
  Vector ap(a, p);
  if (ab.LengthSquared() != 0) {
    return ab.CrossProduct(ap) == 0;
  }
  return a.ContainsPoint(p);
};

bool IsPointOnSegmentS(const Point& a, const Point& b, const Point& p) {
  Vector ab(a, b);
  Vector ap(a, p);
  if (ab.LengthSquared() != 0) {
    if (!IsPointOnLineS(a, b, p)) {
      return false;
    }
    int64_t scalar_product = ab.ScalarProduct(ap);
    if (scalar_product < 0) {
      return false;
    }
    return scalar_product <= ab.LengthSquared();
  }
  return a.ContainsPoint(p);
};

bool IsSegmentCrossesLineS(const Point& a, const Point& b, const Point& c, const Point& d) {
  Vector ab(a, b);
  Vector ac(a, c);
  Vector ad(a, d);
  return ab.CrossProduct(ac) * ab.CrossProduct(ad) <= 0;
};

bool IntersectSegments(const Point& a, const Point& b, const Point& c, const Point& d) {
  Vector ab(a, b);
  Vector ac(a, c);
  Vector ad(a, d);
  Vector cd(c, d);
  Vector ca(c, a);
  Vector cb(c, b);
  if (ab.LengthSquared() != 0 && cd.LengthSquared() != 0) {
    if (IsPointOnSegmentS(a, b, c) || IsPointOnSegmentS(a, b, d) || IsPointOnSegmentS(c, d, a) ||
        IsPointOnSegmentS(c, d, b)) {
      return true;
    }
    if (ab.CrossProduct(ac) == 0 && ab.CrossProduct(ad) == 0 && cd.CrossProduct(ca) == 0 && cd.CrossProduct(cb) == 0) {
      return IsPointOnSegmentS(a, b, c) || IsPointOnSegmentS(a, b, d) ||
             (IsPointOnSegmentS(c, d, a) && IsPointOnSegmentS(c, d, b));
    }
    return IsSegmentCrossesLineS(a, b, c, d) && IsSegmentCrossesLineS(c, d, a, b);
  }
  if (ab.LengthSquared() != 0) {
    return IsPointOnSegmentS(a, b, c);
  }
  if (cd.LengthSquared() != 0) {
    return IsPointOnSegmentS(c, d, a);
  }
  return a.ContainsPoint(c);
};

Segment::Segment() = default;

Segment::Segment(const Point& a, const Point& b) : a_(a), b_(b) {
}

Segment& Segment::Move(const Vector& vector) {
  a_.Move(vector);
  b_.Move(vector);
  return *this;
}

bool Segment::ContainsPoint(const Point& point) const {
  return IsPointOnSegmentS(a_, b_, point);
}

bool Segment::CrossesSegment(const Segment& segment) const {
  return IntersectSegments(a_, b_, segment.a_, segment.b_);
}

Segment* Segment::Clone() const {
  auto result = new Segment(a_, b_);
  return result;
}

std::string Segment::ToString() const {
  return "Segment(" + a_.ToString() + ", " + (b_).ToString() + ")";
}

Segment::~Segment() = default;
};  // namespace geometry