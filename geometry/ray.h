#pragma once

#include "ishape.h"

namespace geometry {
class Ray : public IShape {
 public:
  Point a_;
  Point b_;

 public:
  Ray();
  Ray(const Point& a, const Point& b);

  Ray& Move(const Vector& vector) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  Ray* Clone() const override;
  std::string ToString() const override;
  ~Ray() override;
};
};  // namespace geometry