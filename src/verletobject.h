#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "vector.h"
#include "verletedge.h"


class VerletParticle;


class VerletObject
{

public:

   VerletObject() = default;

   std::vector<std::shared_ptr<VerletParticle>>& getParticlesRw();
   const std::vector<std::shared_ptr<VerletParticle>>& getParticles() const;
   void setParticles(const std::vector<std::shared_ptr<VerletParticle>>& particles);
   void addParticle(const std::shared_ptr<VerletParticle>& particle);

   const std::vector<VerletEdge>& getEdges() const;
   void setEdges(const std::vector<VerletEdge>& edges);
   void addEdge(const VerletEdge& edge);

   float getFriction() const;
   void setFriction(float friction);

   float getBouncyness() const;
   void setBouncyness(float bouncyness);

   int32_t getStiffness() const;
   void setStiffness(int32_t stiffness);

   void moveBy(float dx, float dy, float dz);

   const std::vector<int32_t>& getPositionIndices() const;
   void setPositionIndices(const std::vector<int32_t> &positionIndices);

   const std::vector<Vector>& getNormals() const;
   void setNormals(const std::vector<Vector> &normals);

   const std::vector<int32_t>& getNormalIndices() const;
   void setNormalIndices(const std::vector<int32_t> &normalIndices);


protected:

   std::vector<std::shared_ptr<VerletParticle>> mParticles;
   std::vector<VerletEdge> mEdges;
   std::vector<Vector> mNormals;
   std::vector<int32_t> mNormalIndices;
   std::vector<int32_t> mTriangleIndices;

   float mFriction = 0.996f;
   float mBouncyness = 0.9f;
   int32_t mStiffness = 1;

};

