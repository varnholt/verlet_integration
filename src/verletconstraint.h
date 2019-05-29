#pragma once

#include <memory>

class VerletParticle;

class VerletConstraint
{
public:

   VerletConstraint() = default;
   virtual ~VerletConstraint() = default;
   virtual void constrain(const std::shared_ptr<VerletParticle>&);
};

