#ifndef BALLJOINT_H
#define BALLJOINT_H

#include <QObject>
#include <QString>
#include <QVector3D>
#include <QVector2D>
#include <vector>
class BallJoint
{
public:
    BallJoint();
    ~BallJoint();
    QString name;
    QVector3D offset;
    QVector3D boxmin;
    QVector3D boxmax;
    QVector3D pose;

    QVector2D rotxlimit;
    QVector2D rotylimit;
    QVector2D rotzlimit;
};

#endif // BALLJOINT_H
