#pragma once

#include "ishape.h"

namespace geometry {
  class Circle : public IShape {
    Point center_;
    double r_;
    
   public:
    Circle();
    Circle(Point center, double radius);

    IShape& Move(const Vector&) {}
    bool ContainsPoint(const Point&) {}
    bool CrossesSegment(const Segment&) {}
    IShape* Clone() {}
    void ToString() {}
  };
};