#pragma once

#include "vector.h"

class VerletParticle
{

public:

   VerletParticle() = default;
   VerletParticle(Vector pos);

   const Vector& getPosition() const;
   void setPosition(const Vector& pos);

   const Vector& getPositionPrevious() const;
   void setPositionPrevious(const Vector& posPrev);

   bool isPositionFixed() const;
   void setPositionFixed(bool positionFixed);

   void moveBy(float dx, float dy, float dz);


protected:

   Vector mPosition;
   Vector mPositionPrevious;
   bool mPositionFixed = false;
};
