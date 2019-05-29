#include "verletparticle.h"


VerletParticle::VerletParticle(Vector pos)
{
   mPosition = pos;
   mPositionPrevious = pos;
}


const Vector& VerletParticle::getPosition() const
{
   return mPosition;
}


void VerletParticle::setPosition(const Vector &pos)
{
   mPosition = pos;
}


const Vector& VerletParticle::getPositionPrevious() const
{
   return mPositionPrevious;
}


void VerletParticle::setPositionPrevious(const Vector& posPrev)
{
   mPositionPrevious = posPrev;
}


bool VerletParticle::isPositionFixed() const
{
   return mPositionFixed;
}


void VerletParticle::setPositionFixed(bool positionFixed)
{
   mPositionFixed = positionFixed;
}


void VerletParticle::moveBy(float dx, float dy, float dz)
{
   mPosition.x += dx;
   mPosition.y += dy;
   mPosition.z += dz;

   mPositionPrevious.x += dx;
   mPositionPrevious.y += dy;
   mPositionPrevious.z += dz;
}

