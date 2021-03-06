#ifndef BALLJOINT_H
#define BALLJOINT_H

#include <QObject>
#include <QString>
#include <QVector3D>
#include <QVector2D>
#include <vector>
#include <QMatrix4x4>
class BallJoint
{
public:
    BallJoint();
    ~BallJoint();
    QString name;
    int id;
    QVector3D offset;
    QVector3D boxmin;
    QVector3D boxmax;
    QVector3D pose;
    QMatrix4x4 localPos;

    QVector2D rotxlimit;
    QVector2D rotylimit;
    QVector2D rotzlimit;

    void getLocalPos();
    QVector3D getScaleFactor();
    QVector3D getTranslation();
};

#endif // BALLJOINT_H
