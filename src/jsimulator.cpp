#include "NBodySimulator/src/modelobject.h"
#include "NBodySimulator/src/model.h"
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS() {

  class_<NVector<double, 3>>("NVector")
    .constructor<double, double>()
    .property("x", &NVector<double, 3>::x, &NVector<double, 3>::setX)
    .property("y", &NVector<double, 3>::y, &NVector<double, 3>::setY)
    ;

  class_<ModelObject>("ModelObject")
    .constructor<Vector3D, Vector3D, Vector3D, double, double, int>()
    .constructor<>()
    .property("isDead", &ModelObject::isDead)
    .function("kill", &ModelObject::kill)
    .property("mass", &ModelObject::mass, &ModelObject::set_mass)
    .property("index", &ModelObject::index, &ModelObject::set_index)
    .property("position", &ModelObject::position, &ModelObject::set_position)
    .property("velocity", &ModelObject::velocity, &ModelObject::set_velocity)
    .property("force", &ModelObject::force, &ModelObject::set_force)
    ;
  
  register_vector<ModelObject>("MOVector");

  class_<Model>("Model")
    .constructor<>()
    .function("update", select_overload<void(std::vector<ModelObject>&, const double)>(&Model::Update))
    ;
}
