#ifndef LADIA_NBODYSIMULATOR_TEST_H
#define LADIA_NBODYSIMULATOR_TEST_H

#include "../src/nbodysimulator.h"
#include "../src/model.h"

namespace NBodySimulatorTestSuite 
{
  static const char* kFileName = "sphere.txt";

  // Reads initial conditions from a file and runs the simulation for a preset 
  // period of time. The initial and final conditions are logged.
  void TestModel();

  // Reads initial conditions from a file and runs the simulation for a preset 
  // period of time. The initial and final conditions are logged.
  void TestFile();

  // Runs the simulation for a preset period of time using hard-coded initial
  // conditions. The initial and final conditions are logged.
  void TestData();

  // Animates an ascii text representation of the simulation onto the screen. 
  // The simulation runs for a preset period of time. The initial conditions are
  // read from a file.
  void TestDraw();
};

#endif
