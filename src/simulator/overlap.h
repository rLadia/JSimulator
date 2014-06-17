#ifndef LADIA_CSS342_COLLISION_H
#define LADIA_CSS342_COLLISION_H

#include "shape.h"

// Namespace holding common functions useful for collsion detection
namespace Overlap 
{
  //return: true if the spheres are overlapping
  bool IsOverlapping(Shape::Sphere, Shape::Sphere);

  //return: true if the spheres are overlapping
  bool IsOverlapping(Shape::Circle, Shape::Circle);

  // return: true if the point is contained within the sphere
  bool IsOverlapping(Shape::Circle, Shape::Point);
}

#endif
