#ifndef LADIA_NBODYSIMULATOR_SHAPE_H
#define LADIA_NBODYSIMULATOR_SHAPE_H

#include "nvector.h"

namespace Shape
{
  struct Point
  {
    Vector2D center;
  };

  struct Circle
  {
    Vector2D center;
    double radius;
  };

  struct Square
  {
    Vector2D center;
    double length;
  };

  struct Sphere
  {
    Vector3D center;
    double radius;
  };
}

#endif
