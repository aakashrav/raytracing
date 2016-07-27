#include <iostream>
#include "Image.h"
#include "Scene.h"
#include "Sphere.h"
using namespace std;
using namespace Raytracer148;
using namespace Eigen;

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
    // Set specular shininess
    double shine = 32;
    scene.setShininess(shine);

    Vector3d center;
    center[0] = 0;
    center[1] = 0;
    center[2] = 4;
    Vector3d sphere1color;
    sphere1color[0] = .5;
    sphere1color[1] = .7;
    sphere1color[2] = .1;
    scene.addShape(new Sphere(center, 2, sphere1color));

    center[0] = -.5;
    center[1] = 1;
    center[2] = 2.5;
    Vector3d sphere2color;
    sphere2color[0] = .4;
    sphere2color[1] = .3;
    sphere2color[2] = .4;
    scene.addShape(new Sphere(center, .5, sphere2color));

    center[0] = .5;
    center[1] = 1.25;
    center[2] = 2.75;
    Vector3d sphere3color;
    sphere3color[0] = .2;
    sphere3color[1] = .9;
    sphere3color[2] = .2;
    scene.addShape(new Sphere(center, .5, sphere3color));

    // Vector3d v1;
    // v1[0] = .5;
    // v1[1] = 1.25;
    // v1[2] = 2.75;
    // Vector3d v2;
    // v2[0] = -.5;
    // v2[1] = 1;
    // v2[2] = 2.5;
    // Vector3d v3;
    // v3[0] = 0;
    // v3[1] = 0;
    // v3[2] = 4;
    // Vector3d v4;
    // v4[0] = 0;
    // v4[1] = 0;
    // v4[2] = 5;
    // scene.addShape(new Plane(v1,v2,v3,v4));


    scene.render(im);

    im.writePNG("test.png");

    return 0;
}
