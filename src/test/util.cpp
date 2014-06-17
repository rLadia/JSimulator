#include "util.h"

#include <iomanip>
#include <string>
#include "tablelogger.h"

// initializes the body data
void NBodySimulatorUtil::InitBodies(BodyList &bodies) 
{
  typedef NBodySimulator::Body Body;

  Body body1(
    Vector3(10, 0, 0), // position
    Vector3(0, 0, 0),  // velocity
    Vector3(0, 0, 0),  // force
    1, // mass
    1  // radius
  );

  Body body2(
    Vector3(20, 0, 0), 
    Vector3(0, 0, 0), 
    Vector3(0, 0, 0),
    1, 
    1
  );

  bodies.push_back(body1);
  bodies.push_back(body2);
}

// uses the information from the file to add bodies to the simulation
bool NBodySimulatorUtil::createBodiesFromFile(BodyList &bodies, std::ifstream &file)
{
  if(!file.is_open())
   return false; //file was not able to be read

  do { //read rest of bodies
    int x, y, z, r, vx, vy, vz;

    file >> x >> y >> z >> r >> vx >> vy >> vz;

    if(file.fail())
       break;
    
    NBodySimulator::Body body(
      Vector3(x, y, z), 
      Vector3(vx, vy, vz), 
      Vector3(0,0,0),
      r, 
      r);
    bodies.push_back(body);
  } while(file.good());
  
  return true;
}

void NBodySimulatorUtil::PrintPosition(BodyList &bodies, double elapsed)
  {
    using std::string;

    std::vector<TableLogger::HeaderStyle> header;
    header.push_back(std::make_pair("Index", TableLogger::kCenter));
    header.push_back(std::make_pair("X-Position", TableLogger::kCenter));
    header.push_back(std::make_pair("Y-Position", TableLogger::kCenter));

    std::string title = "Position at " + std::to_string(elapsed) + " seconds"; 

    TableLogger table(title, header);

    table.LogTableHead();

    int index = 0;
    for(BodyList::iterator i = bodies.begin(); i != bodies.end(); ++i) {
  
      std::vector<std::string> row; 
      row.push_back(std::to_string(index));
      row.push_back(std::to_string(i->position().x()));
      row.push_back(std::to_string(i->position().y()));
      index ++;
      table.LogTableRow(row);
    }
  }
