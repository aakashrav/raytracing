#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

namespace Raytracer148 {
class Sphere : public Shape {
public:
    Sphere(Eigen::Vector3d &center, double radius, Eigen::Vector3d color) : c(center), r(radius) {shapeColor = color;};
    virtual HitRecord intersect(const Ray &ray);

private:
    Eigen::Vector3d c;
    double r;
};

class Plane : public Shape {
public:
   	Plane(Eigen::Vector3d vert1, Eigen::Vector3d vert2, Eigen::Vector3d vert3, Eigen::Vector3d vert4,
      Eigen::Vector3d color) : 
   		v1(vert1), v2(vert2), v3(vert3), v4(vert4) {shapeColor = color;};
    virtual HitRecord intersect(const Ray &ray);
    Vector3d getSurfaceNormal(Vector3d v1, Vector3d v2, Vector3d v3);

private:
	Eigen::Vector3d v1;
	Eigen::Vector3d v2;
	Eigen::Vector3d v3;
	Eigen::Vector3d v4;
};

}

#endif
