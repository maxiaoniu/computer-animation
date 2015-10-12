#ifndef SKIN_H
#define SKIN_H
#include <QVector3D>
struct SkinedVertex
{
    QVector3D m_position;
    QVector3D m_normal;

    char m_jointIndex[4];
    float m_jointWeight[3];
};

class Skin
{
public:
    Skin();

signals:

public slots:
};

#endif // SKIN_H
