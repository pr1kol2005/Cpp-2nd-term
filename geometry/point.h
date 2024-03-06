#pragma once

#include "ishape.h"

namespace geometry {
  class Point : public IShape {
    double x_;
    double y_;
    
   public:
    Point();
    Point(double x, double y);
    Point operator+() const;
    Point operator-() const;
    friend Vector operator-(Point left, Point right);
    friend Point operator+(Point left, Point right);
    Point operator*(double scalar) const;
    Point operator/(double scalar) const;

    IShape& Move(const Vector&) {}
    bool ContainsPoint(const Point&) {}
    bool CrossesSegment(const Segment&) {}
    IShape* Clone() {}
    void ToString() {}
  };
};
