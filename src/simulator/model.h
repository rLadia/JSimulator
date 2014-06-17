/*
Interface for initializing and retreiving updates from the simulation model.

The user gives the model information about the initial conditions and time
elapsed. (later on, any additional input that comes from the user). The model 
calculates the effect that the initial conditions have on the model and 
returns the data in a parseable fashion.

References the rules for determining how the objects in the model interact 
with each other.
*/

#include <vector>
#include <list>
#include "modelobject.h"

#ifndef LADIA_NBODYSIMULATOR_MODEL_H
#define LADIA_NBODYSIMULATOR_MODEL_H

class Model
{
public:
  typedef std::vector<ModelObject> ObjectList;
  static const double kTimeInterval; // default time interval used for calculations

  Model();

  // Updates the model to simulate the passing of a period of time. The time
  // interval given determines how accurate the simulation is.
  // The objects can have their position, velocity or force modified 
  // and are removed from the list if they overlap with another object
  void Update(ObjectList &, const double, const double);

  // calls update with default time interval
  void Update(ObjectList &, const double);

private:
  // calculates the gravitational forces between each object
  // and adds it to their force member
  void UpdateGravitationalForces(ObjectList &, const double);

  // Removes objects that are overlapping from the list
  static void HandleOverlaps(ObjectList &);

  static bool IsOverlapping(ModelObject &, ModelObject &);
};

#endif
