#pragma once

#include "ishape.h"

namespace geometry {
  class Line : public IShape {
    Point a_;
    Point b_;
    
   public:
    Line();
    Line(Point a, Point b);

    IShape& Move(const Vector&) {}
    bool ContainsPoint(const Point&) {}
    bool CrossesSegment(const Segment&) {}
    IShape* Clone() {}
    void ToString() {}
  };
};