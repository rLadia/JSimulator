#include <cmath>
#include "gravity.h"

// returns the gravitational force between two point masses
// default value for the gravitational constant
NVector<double, 3> Gravity::force(PointMass m1, PointMass m2) 
{
  return force(m1, m2, Gravity::G);
}

// returns the gravitational force between two point masses
// using a custom value for the gravitational constant
NVector<double, 3> Gravity::force(PointMass m1, PointMass m2, const double g_constant) 
{
  // direction vector
  NVector<double, 3> direction = m2.location - m1.location;

  double r2 = NVector<double, 3>::dotProduct(direction, direction); // radius^2
  double r3 = pow(r2, 1.5); // radius^3

  // GMm/r^3 * R
  return direction * (g_constant * m1.mass * m2.mass / r3);
}
