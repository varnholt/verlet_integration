#include "verletrenderer.h"

#include "verletedge.h"
#include "verletobject.h"
#include "verletparticle.h"


#include <QGLWidget>


void VerletRenderer::renderTriangles(const std::vector<VerletObject>& objects)
{
   for (auto& object : objects)
   {
      const auto& particles = object.getParticles();
      const auto& positionIndices = object.getPositionIndices();

      // const auto& edges = object.getEdges();
      //
      // std::vector<Vector> normals = object.getNormals();
      // std::vector<int> normalIndices = object.getNormalIndices();
      //
      // glColor3f(
      //    i/(float)indices.length(),
      //    i/(float)indices.length(),
      //    i/(float)indices.length()
      // );

      glBegin(GL_TRIANGLES);
      for (auto i = 0u; i < positionIndices.size(); i += 3)
      {
         glColor4f(
            0.5f,
            0.5f,
            0.6f,
            1.0f
         );

         const auto& p0 = particles.at(positionIndices.at(i    ) - 1);
         const auto& p1 = particles.at(positionIndices.at(i + 1) - 1);
         const auto& p2 = particles.at(positionIndices.at(i + 2) - 1);

         const auto& v0 = p0->getPosition();
         const auto& v1 = p1->getPosition();
         const auto& v2 = p2->getPosition();

         auto generatedNormal = (v1 - v0) % (v2 - v1);
         generatedNormal.normalize();

         // Vector n0 = normals.at(normalIndices.at(i)-1);
         // Vector n1 = normals.at(normalIndices.at(i+1)-1);
         // Vector n2 = normals.at(normalIndices.at(i+2)-1);
         //
         // glNormal3f(n0.x, n0.y, n0.z);

         glNormal3f(generatedNormal.x, generatedNormal.y, generatedNormal.z);

         glVertex3f(
            p0->getPosition().x,
            p0->getPosition().y,
            p0->getPosition().z
         );

         // glNormal3f(n1.x, n1.y, n1.z);
         glNormal3f(generatedNormal.x, generatedNormal.y, generatedNormal.z);

         glVertex3f(
            p1->getPosition().x,
            p1->getPosition().y,
            p1->getPosition().z
         );

         // glNormal3f(n2.x, n2.y, n2.z);
         glNormal3f(generatedNormal.x, generatedNormal.y, generatedNormal.z);

         glVertex3f(
            p2->getPosition().x,
            p2->getPosition().y,
            p2->getPosition().z
         );
      }

      glEnd();
   }
}


void VerletRenderer::renderEdges(const std::vector<VerletObject>& objects)
{
   for (const auto& object : objects)
   {
      // edges
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
      glLineWidth(0.5f);
      glBegin(GL_LINES);

      for (const auto& e : object.getEdges())
      {
         if (e.isVisible())
         {
            glVertex3f(
               e.getP0()->getPosition().x,
               e.getP0()->getPosition().y,
               e.getP0()->getPosition().z
            );

            glVertex3f(
               e.getP1()->getPosition().x,
               e.getP1()->getPosition().y,
               e.getP1()->getPosition().z
            );
         }
      }

      glEnd();
   }
}



void VerletRenderer::renderVertices(const std::vector<VerletObject>& objects)
{
   for (const auto& object : objects)
   {
      const auto& particles = object.getParticles();

      // particles
      glPointSize(10.0f);
      glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
      glBegin(GL_POINTS);

      for (auto& p : particles)
      {
         glVertex2f(
            p->getPosition().x,
            p->getPosition().y
         );
      }

      glEnd();
   }
}


void VerletRenderer::renderMesh(const VerletObject& object, int32_t width, int32_t height)
{
   glBegin(GL_TRIANGLES);

   glColor4f(
      0.5f,
      0.5f,
      0.6f,
      1.0f
   );

   const auto& particles = object.getParticles();

   for (auto y = 0; y < height - 1; y++)
   {
      for (auto x = 0; x < width - 1; x++)
      {
         const auto a1x = x;
         const auto a1y = y;
         const auto a2x = x;
         const auto a2y = y + 1;
         const auto a3x = x + 1;
         const auto a3y = y;

         const auto b1x = x;
         const auto b1y = y + 1;
         const auto b2x = x + 1;
         const auto b2y = y + 1;
         const auto b3x = x + 1;
         const auto b3y = y;

         const auto& a1 = particles.at(a1x + a1y * width)->getPosition();
         const auto& a2 = particles.at(a2x + a2y * width)->getPosition();
         const auto& a3 = particles.at(a3x + a3y * width)->getPosition();

         const auto& b1 = particles.at(b1x + b1y * width)->getPosition();
         const auto& b2 = particles.at(b2x + b2y * width)->getPosition();
         const auto& b3 = particles.at(b3x + b3y * width)->getPosition();

         Vector an = (a2 - a1) % (a3 - a2);
         an.normalize();

         Vector bn = (b2 - b1) % (b3 - b2);
         bn.normalize();

         glNormal3f(an.x, an.y, an.z);
         glVertex3f(a1.x, a1.y, a1.z);

         glNormal3f(an.x, an.y, an.z);
         glVertex3f(a2.x, a2.y, a2.z);

         glNormal3f(an.x, an.y, an.z);
         glVertex3f(a3.x, a3.y, a3.z);


         glNormal3f(bn.x, bn.y, bn.z);
         glVertex3f(b1.x, b1.y, b1.z);

         glNormal3f(bn.x, bn.y, bn.z);
         glVertex3f(b2.x, b2.y, b2.z);

         glNormal3f(bn.x, bn.y, bn.z);
         glVertex3f(b3.x, b3.y, b3.z);
      }
   }

   glEnd();
}


