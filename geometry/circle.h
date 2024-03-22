#pragma once

#include "ishape.h"

namespace geometry {
class Circle : public IShape {
 public:
  Point center_;
  int64_t r_;

 public:
  Circle();
  Circle(const Point& center, int64_t radius);

  Circle& Move(const Vector& vector) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  Circle* Clone() const override;
  std::string ToString() const override;
  ~Circle() override;

  bool ContainsPointWithoutHull(const Point& point) const;
};
};  // namespace geometry