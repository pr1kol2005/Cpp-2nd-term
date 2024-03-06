#pragma once

#include "ishape.h"

namespace geometry {
  class Ray : public IShape {
    Point a_;
    Point b_;
    
   public:
    Ray();
    Ray(Point a, Point b);

    IShape& Move(const Vector&) {}
    bool ContainsPoint(const Point&) {}
    bool CrossesSegment(const Segment&) {}
    IShape* Clone() {}
    void ToString() {}
  };
};