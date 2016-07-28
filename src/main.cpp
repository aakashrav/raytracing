#include <iostream>
#include "image.h"
#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"
using namespace std;
using namespace Raytracer148;
using namespace Eigen;

#define SPHERE
// #define PLANE

int main() {
    Image im(400, 400);

    Scene scene;
    Eigen::Vector3d ambientLightColor;

    ambientLightColor[0] = .5;
    ambientLightColor[1] = .7;
    ambientLightColor[2] = .6;
    scene.setAmbientLightColor(ambientLightColor);
    scene.setSpecularLightColor(ambientLightColor);
    double ambientLightStrength = .7;
    scene.setAmbientLightStrength(ambientLightStrength);
    double specularLightStrength = .3;
    scene.setSpecularLightStrength(specularLightStrength);
    // Set specular shininess for all shapes
    double shininess = 32;

    #ifdef SPHERE
    Vector3d center;
    center[0] = 0;
    center[1] = 0;
    center[2] = 4;
    Vector3d sphere1color;
    sphere1color[0] = .5;
    sphere1color[1] = .7;
    sphere1color[2] = .1;
    scene.addShape(new Sphere(center, 2, sphere1color, shininess));

    center[0] = -.5;
    center[1] = 1;
    center[2] = 2.5;
    Vector3d sphere2color;
    sphere2color[0] = .4;
    sphere2color[1] = .3;
    sphere2color[2] = .4;
    scene.addShape(new Sphere(center, .5, sphere2color, shininess));

    center[0] = .5;
    center[1] = 1.25;
    center[2] = 2.75;
    Vector3d sphere3color;
    sphere3color[0] = .2;
    sphere3color[1] = .9;
    sphere3color[2] = .2;
    scene.addShape(new Sphere(center, .5, sphere3color, shininess));
    #endif

    #ifdef PLANE
    Vector3d normalToPlane;
    Vector3d pointOnPlane;
    normalToPlane[0] = 0;
    normalToPlane[1] = 0;
    normalToPlane[2] = -1;
    Vector3d PlaneColor;
    PlaneColor[0] = .3;
    PlaneColor[1] = .4;
    PlaneColor[2] = .7;

    // Bounding vertices of plane;
    Vector3d v1;
    v1[0] = 0;
    v1[1] = .3;
    v1[2] = 8;
    Vector3d v2;
    v2[0] = .5;
    v2[1] = .3;
    v2[2] = 8;
    Vector3d v3;
    v3[0] = 0;
    v3[1] = 0;
    v3[2] = 8;
    Vector3d v4;
    v4[0] = .5;
    v4[1] = 0;
    v4[2] = 8;
    pointOnPlane = v3;

    scene.addShape(new Plane(normalToPlane, pointOnPlane, PlaneColor,
        v1,v2,v3,v4, shininess));
    #endif

    scene.render(im);

    im.writePNG("test.png");

    return 0;
}
