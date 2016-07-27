#include "Shape.h"
using namespace Raytracer148;

using namespace Eigen;

void Shape::setShapeColor(Vector3d color) {
	 if ( (color[0] >=0) && (color[1] <= 1) && 
        (color[1] >= 0) && (color[1] <=1) &&
        (color[2] >= 0) && (color[2] <=1) )
        shapeColor = color;
}
