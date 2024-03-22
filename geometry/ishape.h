#pragma once

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
  virtual ~IShape() = default;

  virtual IShape& Move(const Vector& vector) = 0;
  virtual bool ContainsPoint(const Point& p) const = 0;
  virtual bool CrossesSegment(const Segment& segment) const = 0;
  virtual IShape* Clone() const = 0;
  virtual std::string ToString() const = 0;
};
};  // namespace geometry
