#pragma once

#include "ishape.h"

#include <vector>

namespace geometry {
class Polygon : public IShape {
 public:
  std::vector<Point> vertices;
  int64_t size;

 public:
  Polygon();
  explicit Polygon(std::vector<Point> points);

  Polygon& Move(const Vector& vector) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  Polygon* Clone() const override;
  std::string ToString() const override;
  ~Polygon() override;

  bool ContainsPoinWithoutHull(const Point& point) const;
};
};  // namespace geometry