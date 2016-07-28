#ifndef SHAPE_H
#define SHAPE_H

#include <Eigen/Dense>

using namespace Eigen;

namespace Raytracer148 {
struct Ray {
  Eigen::Vector3d origin, direction;
};

class Shape;

struct HitRecord {
  Eigen::Vector3d position, normal, hitObjectColor;
  double hitObjectShininess;
  double t;
};

class Shape {
protected:
	Vector3d shapeColor;
	double shininess;
public:
  virtual ~Shape(){}
  virtual HitRecord intersect(const Ray &ray) = 0;
  void setShininess(double shine);
  void setShapeColor(Vector3d shapeColor);
private:
};

}

#endif
