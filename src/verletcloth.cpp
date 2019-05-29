#include "verletcloth.h"

#include "verletedge.h"
#include "verletparticle.h"

#include <math.h>


void VerletCloth::createMesh(
   uint32_t width,
   uint32_t height,
   float dx,
   float dz
)
{
   mWidth = width;
   mHeight = height;

   const auto size = static_cast<size_t>(width * height);
   mParticles.resize(size);

   auto px = 0.0f;
   auto py = 0.0f;
   auto pz = 0.0f;

   // build mesh
   for (auto z = 0u; z < height; z++)
   {
      px = 0.0f;
      pz += dz;

      for (auto x = 0u; x < width; x ++)
      {
         px += dx;

         // make the cloth a bit uneven
         py = static_cast<float>(
              sin(static_cast<double>(px) * 0.01) * 10.0
            + cos(static_cast<double>(pz) * 0.01) * 50.0
         );

         mParticles[x + z * width] = std::make_shared<VerletParticle>(Vector{px, py, pz});
      }
   }

   // connect each particle with an edge
   for (auto y = 0u; y < height; y++)
   {
      for (auto x = 0u; x < width; x++)
      {
         const auto& p0 = mParticles[x + y * width];

         // connect left
         if (x > 0)
         {
            addEdge({p0, mParticles[(x - 1) + y * width]});
         }

         // connect right
         if (x < width - 1)
         {
            addEdge({p0, mParticles[(x + 1) + y * width]});
         }

         // connect top
         if (y > 0)
         {
            addEdge({p0, mParticles[x + (y - 1) * width]});
         }

         // connect bottom
         if (y < height - 1)
         {
            addEdge({p0, mParticles[x + (y + 1) * width]});
         }
      }
   }
}


void VerletCloth::pinTop()
{
   for (auto i = 0u; i < mWidth; i++)
   {
      mParticles[i]->setPositionFixed(true);
   }
}


void VerletCloth::copyYtoZ()
{
   for (auto y = 0u; y < mHeight; y++)
   {
      for (auto x = 0u; x < mWidth; x ++)
      {
         auto& particle = mParticles[x + y * mWidth];

         auto position = particle->getPosition();
         auto previous = particle->getPositionPrevious();

         position.z = -position.y;
         previous.z = -previous.y;

         particle->setPosition(position);
         particle->setPositionPrevious(previous);
      }
   }
}


void VerletCloth::pushParticle(int32_t x, int32_t y)
{
   auto& prev = const_cast<Vector&>(mParticles[x + mWidth * y]->getPositionPrevious());
   prev.z -= 50.0f;
}
