#ifndef SCENE_H
#define SCENE_H

#include "Shape.h"
#include "image.h"
#include <vector>
#include <limits>

namespace Raytracer148 {
class Scene {
public:
  Scene() {
    lightPos[0] = lightPos[1] = 3;
    lightPos[2] = 0;
  }

  virtual ~Scene() {
    for (unsigned int i = 0; i < shapes.size(); i++)
      delete shapes[i];
    shapes.resize(0);
  }

  void addShape(Shape *s) { shapes.push_back(s); }
  HitRecord closestHit(const Ray &ray, bool & foundSomething);

  Eigen::Vector3d trace(const Ray &ray, int curr_recursion_depth);
  void render(Image &image);

  void setAmbientLightStrength(double strength);
  void setAmbientLightColor(Eigen::Vector3d light_color);
  void setSpecularLightStrength(double strength);
  void setSpecularLightColor(Eigen::Vector3d light_color);

private:
  std::vector<Shape*> shapes;
  Eigen::Vector3d lightPos;
  double ambientLightStrength;
  double specularLightStrength;
  Eigen::Vector3d ambientLightColor;
  Eigen::Vector3d specularLightColor;
  const int max_recursion_depth = 20;

};
}

#endif
