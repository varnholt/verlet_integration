#pragma once

#include "vector.h"
#include "verletconstraint.h"

#include <memory>
#include <vector>


class VerletObject;

class VerletWorld
{
public:

   void update();

   void addObject(const VerletObject& object);
   const std::vector<VerletObject>& getObjects() const;

   void addConstraint(const VerletConstraint&);
   const std::vector<VerletConstraint>& getConstraints() const;

   void unitTest();


private:

   void updateParticles();
   void constrainParticles();
   void updateEdges();

   // forces
   Vector mGravity;
   Vector mWind;

   std::vector<VerletObject> mObjects;
   std::vector<VerletConstraint> mConstraints;
};


