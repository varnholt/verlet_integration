#pragma once

#include "verletobject.h"

#include <QObject>


class VerletKopuli : public QObject, public VerletObject
{
   Q_OBJECT

public:

   VerletKopuli();


protected slots:

   void kick();
};

