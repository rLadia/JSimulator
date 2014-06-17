#ifndef LADIA_CSS342_NBODYSIMULATOR_H
#define LADIA_CSS342_NBODYSIMULATOR_H

#include <vector>
#include "modelobject.h"

// Simulates the motion of 3d bodies through space
class NBodySimulator {
public:
  typedef ModelObject Body;
  typedef std::vector<Body> BodyList;
  typedef void (*CallBack)(BodyList&);

  static const double kDefaultTimeInterval;
  static const double kDefaultGravity;

  // Simulates the effects of gravity on the given list of objects over the 
  // given time period. If a callback function is specified, that function is
  // called after each simulation step
  void Simulate(BodyList &, const double);
  void Simulate(BodyList &, const double, CallBack);

  // Calculates the instantaneous forces exerted on each body by every other
  // body and adds that force to the body's force member
  void CalculateForcesBetweenBodies(BodyList &);

  // time interval used to update forces, gravitational constant used
  NBodySimulator(const double, const double);
  NBodySimulator();

private:
  double time_interval_;
  double gravity_;

  // Sets the net force of each simulated body to 0
  void ResetForces(BodyList &);

  // Recalculates the forces acting on each body, advances each object the 
  // provided time period and calls the callback function with the provided 
  // list
  void AdvanceAndCallback(BodyList &, const double, CallBack);

  // Adds the gravitational force between each body to each body's net force
  void AddForcesBetween(Body &, Body &);
};

#endif
