#include "overlap.h"
#include <cmath>

//if the sum of the radius is <= the distance, the spheres collide
bool Overlap::IsOverlapping(Shape::Sphere left, Shape::Sphere right)
{
  return Vector3D::Distance(left.center, right.center) 
    <= left.radius + right.radius;
}

//if the sum of the radius is <= the distance, the spheres collide
bool Overlap::IsOverlapping(Shape::Circle left, Shape::Circle right)
{
  return Vector2D::Distance(left.center, right.center) 
    <= left.radius + right.radius;
}

//Returns whether the point exists within the sphere
bool Overlap::IsOverlapping(Shape::Circle circle, Shape::Point point)
{
  return Vector2D::Distance(circle.center, point.center) <= circle.radius;
}