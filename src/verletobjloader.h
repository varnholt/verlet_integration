#pragma once

#include <QString>


class VerletObject;


class VerletObjLoader
{
public:

   static VerletObject* load(
      const QString& filename,
      float scale = 1.0f,
      bool autoFixate = false
   );
};

