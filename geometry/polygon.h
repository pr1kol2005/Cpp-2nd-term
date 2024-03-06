#pragma once

#include "ishape.h"

namespace geometry {
  class Segment : public IShape {
    Point a_;
    Point b_;
    
   public:
    Segment();
    Segment(Point a, Point b);

    IShape& Move(const Vector&) {}
    bool ContainsPoint(const Point&) {}
    bool CrossesSegment(const Segment&) {}
    IShape* Clone() {}
    void ToString() {}
  };
};