#include "verletobject.h"

#include "verletparticle.h"


std::vector<std::shared_ptr<VerletParticle> >& VerletObject::getParticlesRw()
{
   return mParticles;
}


const std::vector<std::shared_ptr<VerletParticle> >& VerletObject::getParticles() const
{
   return mParticles;
}


void VerletObject::setParticles(const std::vector<std::shared_ptr<VerletParticle>>& particles)
{
   mParticles = particles;
}


void VerletObject::addParticle(const std::shared_ptr<VerletParticle>& particle)
{
   mParticles.push_back(particle);
}


const std::vector<VerletEdge>& VerletObject::getEdges() const
{
   return mEdges;
}


void VerletObject::setEdges(const std::vector<VerletEdge>& edges)
{
   mEdges = edges;
}


void VerletObject::addEdge(const VerletEdge& edge)
{
   mEdges.push_back(edge);
}


float VerletObject::getFriction() const
{
   return mFriction;
}


void VerletObject::setFriction(float friction)
{
   mFriction = friction;
}


float VerletObject::getBouncyness() const
{
   return mBouncyness;
}


void VerletObject::setBouncyness(float bouncyness)
{
   mBouncyness = bouncyness;
}


int32_t VerletObject::getStiffness() const
{
   return mStiffness;
}


void VerletObject::setStiffness(int32_t stiffness)
{
   mStiffness = stiffness;
}


void VerletObject::moveBy(float dx, float dy, float dz)
{
   for (auto& p : mParticles)
   {
      p->moveBy(dx, dy, dz);
   }
}


const std::vector<int32_t>& VerletObject::getPositionIndices() const
{
   return mTriangleIndices;
}


void VerletObject::setPositionIndices(const std::vector<int32_t> &positionIndices)
{
   mTriangleIndices = positionIndices;
}


const std::vector<Vector>& VerletObject::getNormals() const
{
   return mNormals;
}


void VerletObject::setNormals(const std::vector<Vector> &normals)
{
   mNormals = normals;
}


const std::vector<int32_t>& VerletObject::getNormalIndices() const
{
   return mNormalIndices;
}


void VerletObject::setNormalIndices(const std::vector<int32_t> &normalIndices)
{
   mNormalIndices = normalIndices;
}


