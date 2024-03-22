#include <iostream>
#include <vector>
#include <string>
#include "../ishape.h"
#include "../point.h"
#include "../vector.h"
#include "../line.h"
#include "../ray.h"
#include "../segment.h"
#include "../polygon.h"
#include "../circle.h"

namespace geometry {
bool IsPointOnLineP(const Point& a, const Point& b, const Point& p) {
  Vector ab(a, b);
  Vector ap(a, p);
  if (ab.LengthSquared() != 0) {
    return ab.CrossProduct(ap) == 0;
  }
  return a.ContainsPoint(p);
};

bool IsPointOnSegmentP(const Point& a, const Point& b, const Point& p) {
  Vector ab(a, b);
  Vector ap(a, p);
  if (ab.LengthSquared() != 0) {
    if (!IsPointOnLineP(a, b, p)) {
      return false;
    }
    int64_t scalar_product = ab.ScalarProduct(ap);
    if (scalar_product < 0) {
      return false;
    }
    return scalar_product <= ab.LengthSquared();
  }
  return a.ContainsPoint(p);
};

Polygon::Polygon() = default;

Polygon::Polygon(std::vector<Point> points) : vertices(points), size(static_cast<int64_t>(vertices.size())) {
}

Polygon& Polygon::Move(const Vector& vector) {
  for (int64_t i = 0; i < size; i++) {
    vertices[i].Move(vector);
  }
  return *this;
}

bool Polygon::ContainsPoint(const Point& point) const {
  bool inside = false;
  int64_t j = 0;
  j = size - 1;
  for (int64_t i = 0; i < size; i++) {
    if (((vertices[i].y_ < point.y_ && vertices[j].y_ >= point.y_) ||
         (vertices[j].y_ < point.y_ && vertices[i].y_ >= point.y_)) &&
        (vertices[i].x_ +
             (point.y_ - vertices[i].y_) / (vertices[j].y_ - vertices[i].y_) * (vertices[j].x_ - vertices[i].x_) <
         point.x_)) {
      inside = !inside;
    }
    if (IsPointOnSegmentP(vertices[i], vertices[j], point)) {
      return true;
    }
    j = i;
  }
  return inside;
};

bool Polygon::ContainsPoinWithoutHull(const Point& point) const {
  bool inside = false;
  int64_t j = 0;
  j = size - 1;
  for (int64_t i = 0; i < size; i++) {
    if (((vertices[i].y_ < point.y_ && vertices[j].y_ >= point.y_) ||
         (vertices[j].y_ < point.y_ && vertices[i].y_ >= point.y_)) &&
        (vertices[i].x_ +
             (point.y_ - vertices[i].y_) / (vertices[j].y_ - vertices[i].y_) * (vertices[j].x_ - vertices[i].x_) <
         point.x_)) {
      inside = !inside;
    }
    if (IsPointOnSegmentP(vertices[i], vertices[j], point)) {
      return false;
    }
    j = i;
  }
  return inside;
};

bool Polygon::CrossesSegment(const Segment& segment) const {
  return (ContainsPoint(segment.a_) && !ContainsPoinWithoutHull(segment.b_)) ||
         (!ContainsPoinWithoutHull(segment.a_) && ContainsPoint(segment.b_));
}

Polygon* Polygon::Clone() const {
  auto result = new Polygon(vertices);
  return result;
}

std::string Polygon::ToString() const {
  std::string result = "Polygon(";
  for (int64_t i = 0; i < size; i++) {
    result += vertices[i].ToString();
    if (i != size - 1) {
      result += ", ";
    }
  }
  return result + ")";
}

Polygon::~Polygon() {
  vertices.clear();
};
};  // namespace geometry