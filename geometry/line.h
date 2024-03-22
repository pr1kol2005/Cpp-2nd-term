#pragma once

#include "ishape.h"

namespace geometry {
class Line : public IShape {
 public:
  Point a_;
  Point b_;

 public:
  Line();
  Line(const Point& a, const Point& b);

  Line& Move(const Vector& vector) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  Line* Clone() const override;
  std::string ToString() const override;
  ~Line() override;
};
};  // namespace geometry