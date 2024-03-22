#pragma once

#include "ishape.h"

namespace geometry {
class Segment : public IShape {
 public:
  Point a_;
  Point b_;

 public:
  Segment();
  Segment(const Point& a, const Point& b);

  Segment& Move(const Vector& vector) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  Segment* Clone() const override;
  std::string ToString() const override;
  ~Segment() override;
};
};  // namespace geometry