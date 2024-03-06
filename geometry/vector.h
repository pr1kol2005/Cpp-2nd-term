#pragma once

#include "point.h"

namespace geometry {
  class Vector {
    Point arrow_;

   public:
    Vector();
    Vector(Point point);

    Vector operator+() const;
    Vector operator-() const;
    friend Vector operator+(Vector left, Vector right);
    friend Vector operator-(Vector left, Vector right);
    Vector operator*(double scalar) const;
    Vector operator/(double scalar) const;
    friend Vector& operator+=(Vector& left, Vector right);
    friend Vector& operator-=(Vector& left, Vector right);
    friend Vector& operator*=(Vector& vector, double scalar);
    friend Vector& operator/=(Vector& vector, double scalar);
    friend bool operator==(Vector left, Vector right);
  };
};