#include "balljoint.h"

BallJoint::BallJoint()
{
    offset = QVector3D(0.0f,0.0f,0.0f);
    boxmin = QVector3D(-0.1f,-0.1f,-0.1f);
    boxmax = QVector3D(0.1f,0.1f,0.1f);
    rotxlimit = QVector2D(-100000, 100000);
    rotylimit = QVector2D(-100000, 100000);
    rotzlimit = QVector2D(-100000, 100000);
    pose = QVector3D(0.0f, 0.0f, 0.0f);
}

BallJoint::~BallJoint()
{

}
