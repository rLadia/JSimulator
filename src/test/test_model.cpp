#include <iostream>

#include "util.h"
#include "test.h"

const double elapsed = 7.7;

void NBodySimulatorTestSuite::TestModel() 
{
  
  Model model;
  Model::ObjectList bodies;
  
  NBodySimulatorUtil::InitBodies(bodies);

  std::cout << "\n--- Program Start ---\n";
  NBodySimulatorUtil::PrintPosition(bodies, 0);
  
  model.Update(bodies, elapsed);

  std::cout << "\n--- Simulation Complete ---\n";
  NBodySimulatorUtil::PrintPosition(bodies, elapsed);
}
