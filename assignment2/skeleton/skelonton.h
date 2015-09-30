#ifndef SKELONTON_H
#define SKELONTON_H
#include <QFile>
#include <QHash>
#include "balljoint.h"
class Skelonton
{
public:
    Skelonton();
    ~Skelonton();

    BallJoint *root;
    //parent tree struct, key is child and value is parents
    QHash<BallJoint*, BallJoint*> tree;

};

#endif // SKELONTON_H
