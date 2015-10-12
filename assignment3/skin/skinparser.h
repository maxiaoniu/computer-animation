#ifndef SKINPARSER_H
#define SKINPARSER_H
#include "skin.h"
#include <QMap>
#include <QTextStream>
#include <QFile>

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
    Skin *skin;
private:
    QFile* m_file;
    QString m_lexicon;
    QString m_currentLine;

    bool parse();
    SkinParseToken lexToken();

signals:

public slots:
};

#endif // SKINPARSER_H
