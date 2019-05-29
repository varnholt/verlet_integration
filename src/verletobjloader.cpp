#include "verletobjloader.h"

#include <QFile>
#include <QStringList>

#include "verletedge.h"
#include "verletobject.h"
#include "verletparticle.h"


VerletObject* VerletObjLoader::load(
   const QString & filename,
   float scale,
   bool autoFixate
)
{
   VerletObject* object = nullptr;

   QFile file(filename);

   if (file.open(QIODevice::ReadOnly | QIODevice::Text))
   {
      float xMin = 9999;
      float yMin = 9999;
      float zMin = 9999;

      VerletObject object;

      std::vector<Vector> positions;
      std::vector<Vector> normals;
      std::vector<int> positionIndices;
      std::vector<int> normalIndices;

      while (!file.atEnd())
      {
         QString line = file.readLine().trimmed();
         line = line.replace("  ", " ");
         QStringList split = line.split(" ", QString::SkipEmptyParts);

         if (split.length() == 4)
         {
            QString type = split.at(0);

            // vector
            if (type == "v")
            {
               float x = split.at(1).toFloat();
               float y = split.at(2).toFloat();
               float z = split.at(3).toFloat();

               xMin = qMin(xMin, x);
               yMin = qMin(yMin, y);
               zMin = qMin(zMin, z);

               positions.push_back(Vector(x,y,z));
            }
            else if (type == "vn")
            {
               float x = split.at(1).toFloat();
               float y = split.at(2).toFloat();
               float z = split.at(3).toFloat();

               normals.push_back(Vector(x,y,z));
            }
            else if (type == "f")
            {
               if (line.contains("/"))
               {
                  for (int t = 0; t < 3; t++)
                  {
                     QStringList tri = split.at(t+1).split("/");

                     int positionIndex = tri.at(0).toInt();
                     int normalIndex = tri.at(2).toInt();

                     positionIndices.push_back(positionIndex);
                     normalIndices.push_back(normalIndex);
                  }
               }
               else
               {
                  bool aOk = false;
                  bool bOk = false;
                  bool cOk = false;

                  int a = split.at(1).toInt(&aOk);
                  int b = split.at(2).toInt(&bOk);
                  int c = split.at(3).toInt(&cOk);

                  if (aOk && bOk && cOk)
                  {
                     positionIndices.push_back(a);
                     positionIndices.push_back(b);
                     positionIndices.push_back(c);
                  }
               }
            }
         }
      }

      // apply scale
      for (auto i = 0u; i < positions.size(); i++)
      {
         positions[i].x *= scale;
         positions[i].y *= scale;
         positions[i].z *= scale;
      }

      for (auto i = 0u; i < positions.size(); i++)
      {
         auto p = std::make_shared<VerletParticle>(positions.at(i));
         object.addParticle(p);
      }

      object.setPositionIndices(positionIndices);
      object.setNormals(normals);
      object.setNormalIndices(normalIndices);

      // parse edges
      auto& particles = object.getParticles();
      for (auto i = 0u; i < positionIndices.size(); i += 3)
      {
         const auto& p0 = particles.at(positionIndices.at(i    ) - 1);
         const auto& p1 = particles.at(positionIndices.at(i + 1) - 1);
         const auto& p2 = particles.at(positionIndices.at(i + 2) - 1);

         // do add edges twice
         auto addA = true;
         auto addB = true;
         auto addC = true;

         for (const auto& edge : object.getEdges())
         {
            if (
                  (&edge.getP0() == &p0 && &edge.getP1() == &p1)
               || (&edge.getP0() == &p1 && &edge.getP1() == &p0)
            )
            {
               addA = false;
            }

            if (
                  (&edge.getP0() == &p1 && &edge.getP1() == &p2)
               || (&edge.getP0() == &p2 && &edge.getP1() == &p1)
            )
            {
               addB = false;
            }

            if (
                  (&edge.getP0() == &p2 && &edge.getP1() == &p0)
               || (&edge.getP0() == &p0 && &edge.getP1() == &p2)
            )
            {
               addB = false;
            }
         }

         if (addA)
         {
            object.addEdge(VerletEdge{p0, p1});
         }

         if (addB)
         {
            object.addEdge(VerletEdge{p1, p2});
         }

         if (addC)
         {
            object.addEdge(VerletEdge{p2, p0});
         }
      }

      // autofixate
      // give object some stiffness at its center
      if (autoFixate)
      {
         Vector center{0, 0, 0};
         for (auto i = 0u; i < positions.size(); i++)
         {
            center += positions.at(i);
         }

         center.x /= static_cast<float>(positions.size());
         center.y /= static_cast<float>(positions.size());
         center.z /= static_cast<float>(positions.size());

         auto centerParticle = std::make_shared<VerletParticle>(center);
         for (auto& p : particles)
         {
            VerletEdge edge(p, centerParticle);
            edge.setVisible(false);
            object.addEdge(edge);
         }

         object.addParticle(centerParticle);
      }
   }

   return object;
}
