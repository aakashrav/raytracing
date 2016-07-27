#include "Scene.h"
#include <cmath>
#include <iostream>
using namespace Raytracer148;
using namespace std;
using namespace Eigen;

HitRecord Scene::closestHit(const Ray &ray, bool & foundSomething) {
    HitRecord result;
    result.t = -1;
    foundSomething = false;

    for (unsigned int i = 0; i < shapes.size(); i++) {
        HitRecord r = shapes[i]->intersect(ray);
        if (r.t > std::numeric_limits<double>::epsilon() && (!foundSomething || r.t < result.t)) {
            result = r;
            foundSomething = true;
        }
    }

    return result;
}

// Returns an RGB color, where R/G/B are each in the range [0,1]
Vector3d Scene::trace(const Ray &ray, int curr_recursion_depth) {

    HitRecord rec, srec;
    bool foundSomething;
    Vector3d result;
    result[0] = result[1] = result[2] = 0;

    rec = closestHit(ray, foundSomething);

    Vector3d lightDir = (lightPos - rec.position).normalized();
    if (rec.t < numeric_limits<double>::epsilon()) return result;

    double diffuse = lightDir.dot(rec.normal);
    if (diffuse < 0) diffuse = 0;

    if (foundSomething) {
        // Ambient color
        result = ambientLightColor * ambientLightStrength;
        // Compute the vector of light
        Vector3d lightDir = (lightPos - rec.position);
        Ray lightRay;
        lightRay.origin = rec.position;
        lightRay.direction = lightDir;
        // Check shading
        HitRecord srec = closestHit(lightRay, foundSomething);
        if (!foundSomething) {
            Vector3d h = (lightDir.normalized() + (-ray.direction).normalized()).normalized();
            result += (((specularLightColor * diffuse) * max(0.0,(rec.normal.dot(lightDir)))) + 
                     ((specularLightColor * specularLightStrength)*(pow((rec.normal.dot(h)),shininess))));
        }
    }

    // http://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
    Vector3d lightReflection = (ray.direction) - ((2 * ((ray.direction).dot(rec.normal))) * rec.normal);
    Ray newRay;
    newRay.origin = rec.position;
    newRay.direction = lightReflection;

    if (curr_recursion_depth == max_recursion_depth)
        return result;
    else
        return (result + (specularLightStrength * trace(newRay,curr_recursion_depth+1)));
}

void Scene::render(Image &image) {
    // We make the assumption that the camera is located at (0,0,0)
    // and that the image plane happens in the square from (-1,-1,1)
    // to (1,1,1).

    assert(image.getWidth() == image.getHeight());

    // Sampling grid size
    int n = 3;

    int size = image.getWidth();
    double pixelSize = 2. / size;
    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++) {
            Vector3d color;
            color[0] = 0;
            color[1] = 0;
            color[2] = 0;

            for (int p = 0; p < n; p++) {
                for (int q = 0; q < n; q++) {

                    double x_offset = (double)p/n;
                    double y_offset = (double)q/n;

                    Ray curRay;
                    curRay.origin[0] = curRay.origin[1] = curRay.origin[2] = 0;
                    curRay.direction[0] = (x + x_offset) * pixelSize - 1;
                    curRay.direction[1] = 1 - (y + y_offset) * pixelSize;
                    curRay.direction[2] = 1;
                    color += trace(curRay,0);
                    std::cout << x_offset << " " << y_offset << std::endl;
                }
            }

            color[0] /= (n*n);
            color[1] /= (n*n);
            color[2] /= (n*n);

            // Ray curRay;
            // curRay.origin[0] = curRay.origin[1] = curRay.origin[2] = 0;
            // curRay.direction[0] = (x + 0.5) * pixelSize - 1;
            // curRay.direction[1] = 1 - (y + 0.5) * pixelSize;
            // curRay.direction[2] = 1;

            // color = trace(curRay,0);
            image.setColor(x, y, color[0], color[1], color[2]);
        }
}

void Scene::setAmbientLightStrength(double strength) {
    if ((strength >=0) && (strength <= 1))
        ambientLightStrength = strength;
}

void Scene::setAmbientLightColor(Eigen::Vector3d light_color) {
    if ((light_color[0] >=0) && (light_color[1] <= 1) && 
        (light_color[1] >= 0) && (light_color[1] <=1) &&
        (light_color[2] >= 0) && (light_color[2] <=1) )
        ambientLightColor = light_color;
}

void Scene::setSpecularLightStrength(double strength) {
    if ((strength >=0) && (strength <= 1))
        specularLightStrength = strength;
}

void Scene::setShininess(double shine) {
    if ((shine >=0) && (shine <= 1))
        shininess = shine;
}

void Scene::setSpecularLightColor(Eigen::Vector3d light_color) {
    if ((light_color[0] >=0) && (light_color[1] <= 1) && 
        (light_color[1] >= 0) && (light_color[1] <=1) &&
        (light_color[2] >= 0) && (light_color[2] <=1) )
        specularLightColor = light_color;
}
