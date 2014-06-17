#ifndef LADIA_CSS342_NVECTOR_H
#define LADIA_CSS342_NVECTOR_H

#include <cmath>

// Represents an n-dimensional Vector
template<typename T, int D> //type, dimensions
class NVector
{
	T val_[D];
  
  public: 
  NVector(); //default ctor
  NVector(const T, const T); //x, y
  NVector(const T, const T, const T); //x, y, z

  // adds the value of the given vector to current NVector 
  void transform(const NVector<T, D> &);

  // returns the dot product of the vector
  // x^2 + y^2 + z^2
  static T dotProduct(const NVector<T, D> &, const NVector<T, D> &);

  // returns the distance between the two vectors
  static double Distance(const NVector<T, D> &, const NVector<T, D> &);

  // getters
  T x() const;
  T y() const;
  T z() const;

  // Allows iteration through the components of the vector
  // pre: the given index is within the range of dimensions of the vector
  T& operator[](int);
  const T operator[](const int) const; 

  // setters
  void setX(const T);
  void setY(const T);
  void setZ(const T);

  // scalar multiplication
  NVector<T, D>& operator *= (const double);
  NVector<T, D>& operator *= (const int);
  const NVector<T, D> operator * (const double) const;
  const NVector<T, D> operator * (const int) const;
  
  // scalar addition and subtraction
  NVector<T, D>& operator += (const NVector<T, D> &);
  NVector<T, D>& operator -= (const NVector<T, D> &);
  const NVector<T, D> operator + (const NVector<T, D> &) const;
  const NVector<T, D> operator - (const NVector<T, D> &) const;
};

#include <cassert>

typedef NVector<double, 3> Vector3;
typedef NVector<double, 3> Vector3D;
typedef NVector<double, 2> Vector2D;


template<typename T, int D>
NVector<T, D>::NVector() 
{
  assert(("NVector size must be > 0", D > 0));
}

template<typename T, int D>
NVector<T, D>::NVector(const T x, const T y) 
{
  assert(("Vector size must be 2 when initializing with 2 parameters", D == 2));
  val_[0] = x;
  val_[1] = y;
}

template<typename T, int D>
NVector<T, D>::NVector(const T x, const T y, const T z) 
{
  assert(("Vector size must be 3 when initializing with 3 parameters", D == 3));
  val_[0] = x;
  val_[1] = y;
  val_[2] = z;
}

template<typename T, int D>
void NVector<T, D>::transform(const NVector<T, D>& NVector) 
{
  for(int i = 0; i < D; ++i)
    val_[i] += NVector[i];
}

// returns the dot product of the vector
// x^2 + y^2 + z^2
template<typename T, int D>
T NVector<T, D>::dotProduct(const NVector<T, D>& NVector1, const NVector<T, D>& NVector2) 
{
  T sum = 0;
  for(int i = 0; i < D; ++i)
    sum += NVector1.val_[i] * NVector2.val_[i];
  return sum;
}

template<typename T, int D>
double NVector<T, D>::Distance(const NVector<T, D>& left, const NVector<T, D>& right) 
{
  double sum = 0;
  for(int i = 0; i < D; ++i) {
    T a = left.val_[i];
    T b = right.val_[i];
    sum += a * a - 2 * a * b + b * b; // (a-b)^2 = a^2 - 2ab + b^2
  }
  return std::sqrt(sum);
}

//getters
template<typename T, int D>
T NVector<T, D>::y() const {
  assert(("y not defined with NVector size less than 2", D >= 2));
  return val_[1];
}


template<typename T, int D>
T NVector<T, D>::z() const {
  assert(("z not defined with NVector size less than 3", D >= 3));
  return val_[2];
}

// Allows iteration through the components of the vector
// pre: the given index is within the range of dimensions of the vector
template<typename T, int D>
T& NVector<T, D>::operator[](int index)
{
  assert(("Index out of bounds", index >= 0 && index < D));
  return val_[index];
}

// Allows iteration through the components of the vector
// pre: the given index is within the range of dimensions of the vector
template<typename T, int D>
const T NVector<T, D>::operator[](const int index) const {
  assert(("Index out of bounds", index >= 0 && index < D));
  return val_[index];
}

//setters
template<typename T, int D>
void NVector<T, D>::setX(const T x) {
  val_[0] = x;
}

template<typename T, int D>
void NVector<T, D>::setY(const T y) {
  assert(("y not defined with NVector size less than 2", D >= 2));
  val_[1] = y;
}

template<typename T, int D>
void NVector<T, D>::setZ(const T z) {
  assert(("z not defined with NVector size less than 3", D >= 3));
  val_[2] = z;
}

template<typename T, int D>
T NVector<T, D>::x() const {
  return val_[0];
}

//overloaded operators
template<typename T, int D>
NVector<T, D>& NVector<T, D>::operator *= (const double scalar) 
{
  for(int i = 0; i < D; ++i)
    val_[i] *= scalar;
  return *this;
}

template<typename T, int D>
const NVector<T, D> NVector<T, D>::operator * (const double scalar) const
{
  NVector<T, D> result = *this;
  result *= scalar;
  return result;
}

template<typename T, int D>
NVector<T, D>& NVector<T, D>::operator *= (const int scalar) 
{
  for(int i = 0; i < D; ++i)
    val_[i] *= scalar;
  return *this;
}

template<typename T, int D>
const NVector<T, D> NVector<T, D>::operator * (const int scalar) const
{
  NVector<T, D> result = *this;
  result *= scalar;
  return result;
}

template<typename T, int D>
NVector<T, D>& NVector<T, D>::operator += (const NVector<T, D> &rhs) 
{
  for(int i = 0; i < D; ++i)
    val_[i] += rhs.val_[i];
  return *this;
}

template<typename T, int D>
const NVector<T, D> NVector<T, D>::operator + (const NVector<T, D> &rhs) const
{
  NVector<T, D> result = *this;
  result += rhs;
  return result;
}

template<typename T, int D>
NVector<T, D>& NVector<T, D>::operator -= (const NVector<T, D> &rhs)
{
  for(int i = 0; i < D; ++i)
    val_[i] -= rhs.val_[i];
  return *this;
}

template<typename T, int D>
const NVector<T, D> NVector<T, D>::operator - (const NVector<T, D> &rhs) const
{
  NVector<T, D> result = *this;
  result -= rhs;
  return result;
}

#endif
