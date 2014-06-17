#include "model.h"
#include "nbodysimulator.h"
#include <iostream>
#include <algorithm>
#include "overlap.h"

const double Model::kTimeInterval = NBodySimulator::kDefaultTimeInterval;

Model::Model()
{}

void Model::Update(
  ObjectList &objects, 
  const double time_elapsed)
{
  Update(objects, time_elapsed, kTimeInterval);
}

void Model::Update(
  ObjectList &objects, 
  const double time_simulated, 
  const double time_interval)
{
  NBodySimulator simulator(time_interval, NBodySimulator::kDefaultGravity);
  simulator.Simulate(objects, time_simulated, &Model::HandleOverlaps);
}

void Model::UpdateGravitationalForces(ObjectList &objects, const double time)
{
  NBodySimulator simulator;
  simulator.Simulate(objects, time);
}

void Model::HandleOverlaps(ObjectList &objects)
{
  if(objects.size() <= 1) // no overlap possible with one item
    return;

  ObjectList::iterator i = objects.begin();

  for(i = objects.begin(); i != objects.end(); ++i) {
    if (i->isDead())
      continue;

    ObjectList::iterator j = i;
    
    for(++j; j != objects.end(); ++j) {
      if(j->isDead())
        continue; 

      if(IsOverlapping(*i, *j)) { // remove the objects from the list
        i->kill();
        j->kill();
        break; // inner while loop is complete
      } 
    }

  };
}

bool Model::IsOverlapping(ModelObject &left, ModelObject &right)
{
  Shape::Sphere circle_left = { left.position(), left.radius() };
  Shape::Sphere circle_right = { right.position(), right.radius() };

  return (Overlap::IsOverlapping(circle_left, circle_right));
}
