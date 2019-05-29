#include "verletkopuli.h"

// Qt
#include <QFile>
#include <QPair>
#include <QStringList>
#include <QTimer>

// verlet
#include "verletedge.h"
#include "verletparticle.h"



VerletKopuli::VerletKopuli()
{
   float scale = 0.3f;
   int xMin = 9999;
   int yMin = 9999;

   QList<Vector> positions;
   QList< QPair<int,int> > edges;

   QFile file("data/kopuli.txt");
   if (file.open(QIODevice::ReadOnly | QIODevice::Text))
   {
      while (!file.atEnd())
      {
         QString line = file.readLine();

         QStringList split = line.split(";");

         if (split.length() == 2)
         {
            bool xOk = false;
            bool yOk = false;
            int x = split.at(0).toInt(&xOk);
            int y = split.at(1).toInt(&yOk);

            if (xOk && yOk)
            {
               xMin = qMin(xMin, x);
               yMin = qMin(yMin, y);

               positions.push_back(Vector(x,y,0));
            }
         }

         split = line.split(",");

         if (split.length() == 2)
         {
            bool aOk = false;
            bool bOk = false;
            int a = split.at(0).toInt(&aOk);
            int b = split.at(1).toInt(&bOk);

            if (aOk && bOk)
            {
               edges.push_back(QPair<int,int>(a,b));
            }
         }
      }
   }

   if (positions.length() > 0)
   {

      foreach (const Vector& v, positions)
      {
         addParticle(
            new VerletParticle(
               Vector(
                  (v.x - xMin) * scale,
                  (v.y - yMin) * scale,
                  0
               )
            )
         );
      }

      auto particles = getParticles();

      VerletParticle p0;
      VerletParticle p1;

      for (auto i = 1u; i < particles.size(); i++)
      {
         p0 = particles.at(i - 1);
         p1 = particles.at(i    );
         addEdge(VerletEdge{p0, p1});
      }

      p0 = particles.at(particles.size() - 1);
      p1 = particles.at(0);
      addEdge(VerletEdge{p0, p1});

      // add extra edges
      for (int i = 0; i < edges.length(); i++)
      {
         auto e = edges.at(i);

         VerletEdge tmp{
            particles.at(e.first),
            particles.at(e.second)
         };

         tmp.setVisible(false);
         addEdge(tmp);
      }
   }

   auto timer = new QTimer(this);

   connect(
      timer,
      SIGNAL(timeout()),
      this,
      SLOT(kick())
   );

   timer->start(10000);
}


void VerletKopuli::kick()
{
   auto particles = getParticles();

   for (auto i = 0u; i < 20u; i++)
   {
      auto p = particles.at(i);

      auto prev = p.getPositionPrevious();
      auto curr = p.getPosition();

      prev.x = curr.x + (qrand() % 10) - 10;
      prev.y = curr.y + 10;
   }
}
