#pragma once

#include "verletobject.h"

class VerletCloth : public VerletObject
{

public:

   void createMesh(
      uint32_t width,
      uint32_t height,
      float dx,
      float dy
   );

   void pinTop();
   void copyYtoZ();

   void pushParticle(int32_t x, int32_t y);


private:

   uint32_t mWidth = 0;
   uint32_t mHeight = 0;
};

