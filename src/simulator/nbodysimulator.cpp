#include <cassert>

#include "gravity.h"
#include "nbodysimulator.h"

const double NBodySimulator::kDefaultTimeInterval = 0.01;
const double NBodySimulator::kDefaultGravity = 10.0;

NBodySimulator::NBodySimulator(const double time_interval, const double gravity) 
  : time_interval_(time_interval), gravity_(gravity)
{}

NBodySimulator::NBodySimulator() 
  : time_interval_(kDefaultTimeInterval), gravity_(kDefaultGravity)
{}

void NBodySimulator::Simulate(BodyList &bodies, const double time_simulated)
{
  Simulate(bodies, time_simulated, nullptr);
}

void NBodySimulator::Simulate(BodyList &bodies, const double time_simulated, CallBack call_back)
{
  double elapsed;

  for(elapsed = 0; 
    elapsed <= time_simulated - time_interval_; 
    elapsed += time_interval_) {

    AdvanceAndCallback(bodies, time_interval_, call_back);
  }

  // simulates any time remaining
  if(elapsed > time_simulated && time_simulated >= 0) {
    AdvanceAndCallback(bodies, elapsed - time_interval_, call_back);
  }
}

void NBodySimulator::AdvanceAndCallback(BodyList &bodies, const double time, CallBack call_back)
{
  ResetForces(bodies);
  CalculateForcesBetweenBodies(bodies);

  for(BodyList::iterator i = bodies.begin(); i != bodies.end(); ++i)
    i->Advance(time_interval_);
  if(call_back != nullptr)
    call_back(bodies);
}

// set the forces of each simulated body to 0
void NBodySimulator::ResetForces(BodyList &bodies) 
{
  for(BodyList::iterator i = bodies.begin(); i != bodies.end(); ++i)
    i->set_force(Vector3(0,0,0));
}


// Calculates the instantaneous forces exerted on the simulated bodies
// by each other simulated body
void NBodySimulator::CalculateForcesBetweenBodies(BodyList &bodies) 
{
  BodyList::iterator i = bodies.begin();

  for(i; i != bodies.end(); ++i) {
    BodyList::iterator j = i; // not necessary to start at beginning
    j ++; // bodies do not apply a force on themselves
    for(; j != bodies.end(); ++j) {
      AddForcesBetween(*i, *j);
    }
  };
}


// Adds the force exerted on each body to each body's net force 
void NBodySimulator::AddForcesBetween(ModelObject &b1, ModelObject &b2)
{
  Gravity::PointMass m1 = { b1.mass(), b1.position() };
  Gravity::PointMass m2 = { b2.mass(), b2.position() };

  Vector3 force = Gravity::force(m1, m2, gravity_);
  b1.set_force(b1.force() + force);
  b2.set_force(b2.force() + force * -1);
}
