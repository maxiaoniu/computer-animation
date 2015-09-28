#ifndef SKELONTON_H
#define SKELONTON_H
#include <QFile>
#include "balljoint.h"
class Skelonton
{
public:
    Skelonton(QFile *file);
    ~Skelonton();

    BallJoint *root;

};

#endif // SKELONTON_H
