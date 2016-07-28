#include "Plane.h"
#include <limits>
#include <iostream>
#include <cmath>

using namespace Raytracer148;
using namespace Eigen;
using namespace std;

HitRecord Plane::intersect(const Ray & ray) {

    HitRecord result;
    result.t = -1;

    // Ray-Plane intersection algorithm; inspiration from: 
    // http://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
    double denom = normal.normalized().dot(ray.direction.normalized());
    if (abs(denom) > 1e-6) { 
        Vector3d p0l0 = (pointOnPlane - ray.origin).normalized(); 
        double time_hit = (p0l0.dot(normal))/denom;
        Vector3d position_hit = ray.origin + (result.t * ray.direction);

        // Make sure hit point is inside the plane, since this is NOT
        // an infinite plane!
        if (InsidePlane(position_hit)) {
            result.t = time_hit; 
            result.position = position_hit;
            result.normal = normal;
            result.hitObjectColor = shapeColor;
            result.hitObjectShininess = shininess;
        }
        else
            return result;
    } 
    else
        return result;

    // Return final hit record, if the point of intersection was inside the plane
    return result;

}

bool Plane::InsidePlane(Vector3d point) {
    if ( ( (point[0] >= v1[0]) && (point[0] <= v2[0]) )
        && ((point[1] <= v1[1]) && (point[0] >= v3[1])) )
        return true;

    return false;
}
