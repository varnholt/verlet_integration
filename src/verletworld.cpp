// base
#include "verletworld.h"

// verlet
#include "verletconstants.h"
#include "verletconstraint.h"
#include "verletedge.h"
#include "verletobject.h"
#include "verletparticle.h"

#include <math.h>


namespace
{
   static const auto INTEGRATION_ITERATIONS = 4;

   static const auto WORLD_WIDTH  = 1920.0f;
   static const auto WORLD_HEIGHT = 1080.0f;
   static const auto WORLD_DEPTH  = 1000.0f;
}


void VerletWorld::unitTest()
{
   auto p0 = std::make_shared<VerletParticle>();
   auto p1 = std::make_shared<VerletParticle>(Vector{200, 100, 0});
   auto p2 = std::make_shared<VerletParticle>(Vector{200, 200, 0});
   auto p3 = std::make_shared<VerletParticle>(Vector{100, 100, 0});

   p0->setPosition(Vector(100, 100, 0));
   p0->setPositionPrevious(Vector(75, 125, 0)); // kick box

   VerletEdge e0{p0, p1};
   VerletEdge e1{p1, p2};
   VerletEdge e2{p2, p3};
   VerletEdge e3{p3, p0};
   VerletEdge e4{p0, p2};
   e4.setVisible(false);

   VerletObject vo;

   vo.addParticle(p0);
   vo.addParticle(p1);
   vo.addParticle(p2);
   vo.addParticle(p3);

   vo.addEdge(e0);
   vo.addEdge(e1);
   vo.addEdge(e2);
   vo.addEdge(e3);
   vo.addEdge(e4);

   mObjects.push_back(vo);
}


void VerletWorld::updateParticles()
{
   for (auto& object: mObjects)
   {
      for (auto& particle : object.getParticlesRw())
      {
         if (!particle->isPositionFixed())
         {
            auto current  = particle->getPosition();
            auto previous = particle->getPositionPrevious();

            const auto friction = object.getFriction();

            const auto vx = (current.x - previous.x) * friction;
            const auto vy = (current.y - previous.y) * friction;
            const auto vz = (current.z - previous.z) * friction;

            previous = current;

            current.x += vx;
            current.y += vy;
            current.z += vz;

            current.y += GRAVITY;

            particle->setPosition(current);
            particle->setPositionPrevious(previous);
         }
      }
   }
}


void VerletWorld::constrainParticles()
{
   for (auto& object : mObjects)
   {
      const auto bounce = object.getBouncyness();
      const auto friction = object.getFriction();

      for (auto& particle : object.getParticlesRw())
      {
         if (!particle->isPositionFixed())
         {
            auto& current = const_cast<Vector&>(particle->getPosition());
            auto& previous = const_cast<Vector&>(particle->getPositionPrevious());

            auto vx = (current.x - previous.x) * friction;
            auto vy = (current.y - previous.y) * friction;
            auto vz = (current.z - previous.z) * friction;

            // width bounds
            if (current.x > WORLD_WIDTH)
            {
               current.x = WORLD_WIDTH;
               previous.x = current.x + vx * bounce;
            }
            else if (current.x < 0)
            {
               current.x = 0;
               previous.x = current.x + vx * bounce;
            }

            // depth bounds
            if (current.z > WORLD_DEPTH)
            {
               current.z = WORLD_DEPTH;
               previous.z = current.z + vz * bounce;
            }
            else if (current.z < -WORLD_DEPTH)
            {
               current.z = -WORLD_DEPTH;
               previous.z = current.z + vz * bounce;
            }

            for (auto& constraint : mConstraints)
            {
               constraint.constrain(particle);
            }
         }
      }
   }
}


void VerletWorld::updateEdges()
{
   for (auto& object : mObjects)
   {
      for (auto& edge : object.getEdges())
      {
         auto& p0 = const_cast<Vector&>(edge.getP0()->getPosition());
         auto& p1 = const_cast<Vector&>(edge.getP1()->getPosition());

         const auto dx = p1.x - p0.x;
         const auto dy = p1.y - p0.y;
         const auto dz = p1.z - p0.z;

         const auto distance = static_cast<float>(sqrt(static_cast<double>(dx * dx + dy * dy + dz * dz)));
         const auto difference = edge.getLength() - distance;

         const auto ratio = difference / distance / 2.0f;

         const auto offsetX = dx * ratio;
         const auto offsetY = dy * ratio;
         const auto offsetZ = dz * ratio;

         if (!edge.getP0()->isPositionFixed())
         {
            p0.x -= offsetX;
            p0.y -= offsetY;
            p0.z -= offsetZ;
         }

         if (!edge.getP1()->isPositionFixed())
         {
            p1.x += offsetX;
            p1.y += offsetY;
            p1.z += offsetZ;
         }
      }
   }
}


const std::vector<VerletConstraint>& VerletWorld::getConstraints() const
{
   return mConstraints;
}


void VerletWorld::update()
{
   updateParticles();

   for (auto i = 0; i < INTEGRATION_ITERATIONS; i++)
   {
      updateEdges();
      constrainParticles();
   }
}


void VerletWorld::addObject(const VerletObject& object)
{
   mObjects.push_back(object);
}


const std::vector<VerletObject>& VerletWorld::getObjects() const
{
   return mObjects;
}


void VerletWorld::addConstraint(const VerletConstraint& constraint)
{
   mConstraints.push_back(constraint);
}

