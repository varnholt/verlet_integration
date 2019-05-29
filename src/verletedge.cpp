#include "verletedge.h"

// verlet
#include "verletparticle.h"

// framework
#include "vector.h"

// cmath
#include <math.h>


VerletEdge::VerletEdge(const std::shared_ptr<VerletParticle>& p0, const std::shared_ptr<VerletParticle>& p1)
{
   mParticles[0] = p0;
   mParticles[1] = p1;

   mLength = computeDistance();
}


float VerletEdge::getLength() const
{
   return mLength;
}


float VerletEdge::computeDistance()
{
   auto p0 = mParticles[0];
   auto p1 = mParticles[1];

   const auto& dx = p1->getPosition().x - p0->getPosition().x;
   const auto& dy = p1->getPosition().y - p0->getPosition().y;
   const auto& dz = p1->getPosition().z - p0->getPosition().z;

   const auto distance = sqrt(static_cast<double>(dx * dx + dy * dy + dz * dz));
   return static_cast<float>(distance);
}


bool VerletEdge::isVisible() const
{
   return mVisible;
}


void VerletEdge::setVisible(bool visible)
{
   mVisible = visible;
}


const std::shared_ptr<VerletParticle>& VerletEdge::getP0() const
{
   return mParticles[0];
}


const std::shared_ptr<VerletParticle>& VerletEdge::getP1() const
{
   return mParticles[1];
}


float VerletEdge::getWidth() const
{
    return mWidth;
}


void VerletEdge::setWidth(float width)
{
    mWidth = width;
}



