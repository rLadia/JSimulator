#ifndef LADIA_NBODYSIMULATOR_UTILITIES_H
#define LADIA_NBODYSIMULATOR_UTILITIES_H

#include <fstream>
#include "../src/nbodysimulator.h"

namespace NBodySimulatorUtil {  
  typedef NBodySimulator::BodyList BodyList;

  void PrintPosition(BodyList &, double);
  bool createBodiesFromFile(BodyList &, std::ifstream &);
  void InitBodies(BodyList &);
};

#endif
