#include "balljoint.h"
#include <QtMath>
BallJoint::BallJoint()
{
    offset = QVector3D(0.0f,0.0f,0.0f);
    boxmin = QVector3D(-0.1f,-0.1f,-0.1f);
    boxmax = QVector3D(0.1f,0.1f,0.1f);
    rotxlimit = QVector2D(-10000.0f, 10000.0f);
    rotylimit = QVector2D(-10000.0f, 10000.0f);
    rotzlimit = QVector2D(-10000.0f, 10000.0f);
    pose = QVector3D(0.0f, 0.0f, 0.0f);
}

BallJoint::~BallJoint()
{

}

void BallJoint::getLocalPos()
{

    localPos.setToIdentity();

    float px = pose.x();
    float py = pose.y();
    float pz = pose.z();

    //clamp
    if(px < rotxlimit.x()) px = rotxlimit.x();
    if(px > rotxlimit.y()) px = rotxlimit.y();
    if(py < rotylimit.x()) py = rotylimit.x();
    if(py > rotylimit.y()) py = rotylimit.y();
    if(pz < rotzlimit.x()) pz = rotzlimit.x();
    if(pz > rotzlimit.y()) pz = rotzlimit.y();

    px = qRadiansToDegrees(px);
    py = qRadiansToDegrees(py);
    pz = qRadiansToDegrees(pz);


    localPos.translate(offset);

    localPos.rotate(pz,0,0,1);

    localPos.rotate(py,0,1,0);
        localPos.rotate(px,1,0,0);

}
QVector3D BallJoint::getScaleFactor()
{
    QVector3D scaleFactor = (boxmax-boxmin);
    return scaleFactor;
}
QVector3D BallJoint::getTranslation() {
    QVector3D cubeTranslate = (boxmax+boxmin)/2;
    return cubeTranslate;
}
