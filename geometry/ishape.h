#pragma once

#include "vector.h"

namespace geometry {
  class Point;
  class Segment;
  class Line;
  class Ray;
  class Polygon;
  class Circle;
  class Vector;

  class IShape {
   public:
    virtual IShape& Move(const Vector&) {}
    virtual bool ContainsPoint(const Point&) {}
    virtual bool CrossesSegment(const Segment&) {}
    virtual IShape* Clone() {}
    virtual void ToString() {}
  };
};
