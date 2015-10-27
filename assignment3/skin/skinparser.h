#ifndef SKINPARSER_H
#define SKINPARSER_H
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <QMap>
#include <QTextStream>
#include <QFile>
#include <QVector3D>
#include <QVector>
#include <QMatrix4x4>
struct SkinedVertex
{
    QVector3D m_position;
    QVector3D m_normal;

    int m_jointIndex[4];
    float m_jointWeight[4];
};

enum SkinParseToken
{
    PT_SKIN_EMPTY,
    PT_SKIN_JOINT_END,
    PT_POS,
    PT_NORMALS,
    PT_SKINWEIGHT,
    PT_TRIANGLES,
    PT_BINDING,
    PT_MATRIX
};
class SkinParseMap : public QMap<QString, SkinParseToken>
{
public:
  SkinParseMap()
  {
    insert("positions",PT_POS);
    insert("normals", PT_NORMALS);
    insert("skinweights", PT_SKINWEIGHT);
    insert("triangles", PT_TRIANGLES);
    insert("bindings", PT_BINDING);
    insert("}", PT_SKIN_JOINT_END);
    insert("matrix", PT_MATRIX);
  }
};
static SkinParseMap const skin_sg_reserved;

class SkinParser
{
public:
    SkinParser(QFile *file);
    ~SkinParser();
    void initGL();
    QVector<QMatrix4x4*> bindingsMatrix;
    void draw();
private:
    QFile* m_file;
    QString m_lexicon;
    QString m_currentLine;
    QVector<SkinedVertex*> skinVertexs;
    QVector<int> triangles;
    bool parse();
    SkinParseToken lexToken();

    QOpenGLBuffer *m_vBuffer;
    QOpenGLBuffer *m_eBuffer;
    QOpenGLVertexArrayObject *m_vao;
signals:

public slots:
};

#endif // SKINPARSER_H
