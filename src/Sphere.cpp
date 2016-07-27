#include "Sphere.h"
#include <limits>
using namespace Raytracer148;
using namespace Eigen;
using namespace std;

HitRecord Sphere::intersect(const Ray &ray) {
    HitRecord result;
    result.t = -1;

    // set up intersection system as at^2+bt+c (see lecture 10)
    double at = ray.direction.squaredNorm();
    double bt = 2 * ray.direction.dot(ray.origin - c);
    double ct = (ray.origin - c).squaredNorm() - r * r;

    double discriminant = bt * bt - 4 * at * ct;

    if (discriminant < numeric_limits<double>::epsilon()) return result; // no hit!

    double t0 = (-bt - sqrt(discriminant)) / (2 * at);
    double t1 = (-bt + sqrt(discriminant)) / (2 * at);

    if (t1 < numeric_limits<double>::epsilon()) return result; // no hit!

    // hit!

    if (t0 > numeric_limits<double>::epsilon()) result.t = t0; // use closer hit if it's in front
    else result.t = t1;

    result.position = ray.origin + result.t * ray.direction;
    result.normal = (result.position - c).normalized();
    result.hitObjectColor = shapeColor;

    return result;
}

// Intersecting with a plane

Vector3d Plane::getSurfaceNormal(Vector3d v1, Vector3d v2, Vector3d v3) {
    /*
     * Obtain vectors between the coordinates of
     * triangle.
     */
     Eigen::Vector3d triangleVector1 = {v2[0] - v1[0], v2[1] - v1[1], v2[2] - v1[2]};
     Eigen::Vector3d triangleVector2 = {v3[0] - v1[0], v3[1] - v1[1], v3[2] - v1[2]};

     Eigen::Vector3d cross = triangleVector1.cross(triangleVector2);

     return cross.normalized();

}

HitRecord Plane::intersect(const Ray & ray) {
    HitRecord result;
    result.t = -1;

    // Compute normal to the plane
    Eigen::Vector3d firstVector = v2 - v1;
    Eigen::Vector3d secondVector = v3 - v2;
    Eigen::Vector3d normal_vector = (firstVector.cross(secondVector)).normalized();

    // Make sure ray is not parallel to the plane
    if ((ray.direction.dot(normal_vector)) == 0) {
        return result;
    }

    // Set up intersection system.
    result.t = ((-1) * (ray.origin.dot(normal_vector + v1))) / (ray.direction.dot(normal_vector));
    result.position = ray.origin + result.t * ray.direction;
    result.normal =  normal_vector;
    result.hitObjectColor = shapeColor;

    return result;

}
