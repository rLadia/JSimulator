#include "modelobject.h"
#include <cmath>

// default ctor
ModelObject::ModelObject()
  : position_(0, 0, 0), velocity_(0, 0, 0), force_(0, 0, 0), mass_(0), radius_(0), index_(0), isDead_(false)
{}

// position, velocity, force, mass, radius
ModelObject::ModelObject(
  Vector3D position, 
  Vector3D velocity, 
  Vector3D force, 
  double mass, 
  double radius,
  int index)
  : position_(position), 
    velocity_(velocity), 
    force_(force), 
    mass_(mass), 
    radius_(radius),
    index_(index),
    isDead_(false)
{}

void ModelObject::Advance(double time)
{
  Vector3 acceleration = force_ * (1.0f / mass_);

  position_ += velocity_ * time; // v(0) * t
  position_ += acceleration * 0.5 * std::pow(time, 2.0); // 1/2 * a * t^2

  velocity_ += acceleration * time; // v(t) = v(0) + at
}

// getters
const Vector3D ModelObject::position() const 
{ return position_; }

const Vector3D ModelObject::velocity() const
{ return velocity_; }

const Vector3D ModelObject::force() const
{ return force_; }

const double ModelObject::mass() const
{ return mass_; }

const double ModelObject::radius() const 
{ return radius_; }

const int ModelObject::index() const 
{ return index_; }

const bool ModelObject::isDead() const 
{ return isDead_; }

// setters
void ModelObject::set_position(Vector3D position) { 
  position_.setX(position.x()); 
  position_.setY(position.y()); 
}
void ModelObject::set_velocity(Vector3D velocity) { velocity_ = velocity; }
void ModelObject::set_force(Vector3D force) { force_ = force; }
void ModelObject::set_mass(double mass) { mass_ = mass; }
void ModelObject::set_index(int index) { index_ = index; }
void ModelObject::kill() { isDead_ = true; }
