#ifndef LADIA_NBODYSIMULATOR_MODELOBJECT_H
#define LADIA_NBODYSIMULATOR_MODELOBJECT_H

#include "nvector.h"

class ModelObject
{
public:

  // ctors
  ModelObject();

  // position, velocity, force, mass, shape
  ModelObject(Vector3D, Vector3D, Vector3D, double, double, int = 0);

  // Modifies the position and velocity using the kinematic equations of motion
  // where acceleration is equal to force divided by mass
  // x(t) = x(0) + v(0) * t + 1/2 a * t^2
  // v(t) = v(0) + a * t
  void Advance(double);

  // getters
  const Vector3D position() const;
  const Vector3D velocity() const;
  const Vector3D force() const;
  const double   mass() const;
  const double   radius() const;
  const int      index() const;
  const bool     isDead() const;
  
  // setters
  void set_position(Vector3D);
  void set_velocity(Vector3D);
  void set_force(Vector3D);
  void set_mass(double);
  void set_index(int);

  void kill();

protected:
  Vector3D position_;
  Vector3D velocity_;
  Vector3D force_;

  double mass_;
  double radius_; // *TODO* generalize to shape
  int index_; // id number
  bool isDead_; // id number
};

#endif
