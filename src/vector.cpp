#include "vector.h"
#include <math.h>


Vector::Vector(float x, float y, float z)
: x(x),
  y(y),
  z(z)
{
}


void Vector::set(float px, float py, float pz)
{
   x= px;
   y= py;
   z= pz;
}


Vector Vector::operator * (const float f) const
{
   Vector n;
   n.x= x*f;
   n.y= y*f;
   n.z= z*f;
   return n;
}


float Vector::operator * (const Vector& v) const
{
   return x*v.x + y*v.y + z*v.z;
}

Vector Vector::operator + (const Vector& v) const
{
   Vector n;
   n.x= x + v.x;
   n.y= y + v.y;
   n.z= z + v.z;
   return n;
}


void Vector::operator += (const Vector& v)
{
   x+=v.x;
   y+=v.y;
   z+=v.z;
}


Vector Vector::operator - (const Vector& v) const
{
   Vector n;
   n.x= x - v.x;
   n.y= y - v.y;
   n.z= z - v.z;
   return n;
}

Vector Vector::operator - () const
{
   Vector n;
   n.x= -x;
   n.y= -y;
   n.z= -z;
   return n;
}


void Vector::operator -= (const Vector& v)
{
   x-=v.x;
   y-=v.y;
   z-=v.z;
}


Vector Vector::operator % (const Vector& v) const
{
   Vector n;
   n.x = y*v.z - z*v.y;
   n.y = z*v.x - x*v.z;
   n.z = x*v.y - y*v.x;
   return n;
}


bool Vector::operator == (const Vector& v1) const
{
   float x1= x - v1.x;
   float y1= y - v1.y;
   float z1= z - v1.z;
   float dist= x1*x1 + y1*y1 + z1*z1;
   if (dist<0.0001f) return true; else return false;
}


bool Vector::operator != (const Vector& v1) const
{
   float x1= x - v1.x;
   float y1= y - v1.y;
   float z1= z - v1.z;
   float dist= x1*x1 + y1*y1 + z1*z1; // no sqrt! compare with EPS^2 instead
   if (dist<EPS) return false; else return true;
}


void Vector::normalize(float length)
{
   float t = length / static_cast<float>(sqrt(static_cast<double>(x*x + y*y + z*z)));
   x*=t;
   y*=t;
   z*=t;
}


float Vector::length() const
{
   return static_cast<float>(sqrt(static_cast<double>(x*x + y*y + z*z)));
}


float* Vector::data() const
{
   return (float*)&x;
}


int Vector::maxIndex() const
{
   if (x >= y && x >= z)
      return 0;
   if (y >= z)
      return 1;
   else
      return 2;
}


void Vector::maximum(const Vector& v)
{
   if (v.x > x) x= v.x;
   if (v.y > y) y= v.y;
   if (v.z > z) z= v.z;
}


void Vector::minimum(const Vector& v)
{
   if (v.x < x) x= v.x;
   if (v.y < y) y= v.y;
   if (v.z < z) z= v.z;
}
