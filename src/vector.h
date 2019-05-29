#pragma once

class Vector
{
   #define EPS 0.0001f

public:
  float  x,y,z;

  Vector() = default;
  Vector(float x, float y, float z);

  operator const float* () const { return &x; }// cast to float*
  bool   operator ==(const Vector& v) const;   // equal
  bool   operator !=(const Vector& v) const;   // not equal
  Vector operator + (const Vector& v) const;   // add two vectors
  void   operator +=(const Vector& v);         // add another vector
  Vector operator - (const Vector& v) const;   // subtract two vectors
  Vector operator - () const;                  // negate
  void   operator -=(const Vector& v);         // subtract another vector
  Vector operator * (const float f) const;     // multiply by scalar
  float  operator * (const Vector& v) const;   // dot product
  void   operator *=(const float f);           // multiply by scalar
  Vector operator % (const Vector& v) const;   // cross product

  void   set(float x=0, float y=0, float z=0); // set components
  void   normalize(float length= 1.0f);        // scale to length
  float  length() const;                       // get length
  float* data() const;                         // get float[3] pointer to components
  int    maxIndex() const;                     // get index of maximum component (0=x, 1=y, 2=z)
  void   minimum(const Vector& v);             // component-wise minimum (1,2,3,4).minimum( (3,2,1,0) ) = (1,2,1,0)
  void   maximum(const Vector& v);             // component-wise maximum
};
