#pragma once

#include <cstdint>
#include <vector>

class VerletObject;


class VerletRenderer
{
   public:

      VerletRenderer() = default;

      void renderTriangles(const std::vector<VerletObject>& objects);
      void renderEdges(const std::vector<VerletObject>& objects);
      void renderVertices(const std::vector<VerletObject>& objects);
      void renderMesh(const VerletObject& object, int32_t width, int32_t height);
};

