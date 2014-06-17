#include <iostream>

#include "util.h"
#include "test.h"

const double elapsed = 1.0;

void NBodySimulatorTestSuite::TestData() 
{
  NBodySimulator simulation;
  NBodySimulator::BodyList bodies;

  NBodySimulatorUtil::InitBodies(bodies);

  std::cout << "\n--- Program Start ---\n";
  NBodySimulatorUtil::PrintPosition(bodies, 0);
  
  simulation.Simulate(bodies, elapsed);

  std::cout << "\n--- Simulation Complete ---\n";
  NBodySimulatorUtil::PrintPosition(bodies, elapsed);
}


