#pragma once

#include "ishape.h"

namespace geometry {
class Point : public IShape {
 public:
  int64_t x_;
  int64_t y_;

 public:
  Point();
  Point(int64_t x, int64_t y);
  Point(const Point& p);
  Point operator+() const;
  Point operator-() const;
  Vector operator-(const Point& other) const;

  Point& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Point* Clone() const override;
  std::string ToString() const override;
  ~Point() override;
};
};  // namespace geometry
