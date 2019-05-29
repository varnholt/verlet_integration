#pragma once

#include <array>
#include <memory>

#include "verletparticle.h"

class VerletEdge
{

public:

   VerletEdge(const std::shared_ptr<VerletParticle>& p0, const std::shared_ptr<VerletParticle>& p1);

   float getLength() const;
   float computeDistance();

   bool isVisible() const;
   void setVisible(bool visible);

   const std::shared_ptr<VerletParticle>& getP0() const;
   const std::shared_ptr<VerletParticle>& getP1() const;

   float getWidth() const;
   void setWidth(float width);

   bool isValid() const;


protected:

   std::array<std::shared_ptr<VerletParticle>, 2> mParticles;

   float mLength = 1.0f;
   float mWidth = 0.5f;

   bool mVisible = true;
};

