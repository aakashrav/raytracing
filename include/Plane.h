#ifndef PLANE_H
#define PLANE_H

#include "Shape.h"

namespace Raytracer148 {
class Plane : public Shape {

public:
   	Plane(Eigen::Vector3d normal_to_plane, Eigen::Vector3d point,
      Eigen::Vector3d color, Eigen::Vector3d vert1, Eigen::Vector3d vert2,
      Eigen::Vector3d vert3, Eigen::Vector3d vert4, double shine) : 
   		normal(normal_to_plane), pointOnPlane(point), v1(vert1), v2(vert2),
      v3(vert3), v4(vert4) {shapeColor = color; shininess = shine; };
    virtual HitRecord intersect(const Ray &ray);
    // Vector3d getSurfaceNormal(Vector3d v1, Vector3d v2, Vector3d v3);

private:
	Eigen::Vector3d normal;
  Eigen::Vector3d pointOnPlane;
  Eigen::Vector3d v1;
  Eigen::Vector3d v2;
  Eigen::Vector3d v3;
  Eigen::Vector3d v4;
  bool InsidePlane(Eigen::Vector3d point);

};
}

#endif
