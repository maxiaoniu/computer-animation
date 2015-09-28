#ifndef SKELONTONPARSER_H
#define SKELONTONPARSER_H
#include "skelonton.h"
#include <QMap>
#include <QTextStream>
#include <QFile>


enum ParseToken
{
    PT_BALLJOINT,
    PT_JOINT_START,
    PT_OFFSET,
    PT_BOXMIN,
    PT_BOXMAX,
    PT_POSE,
    PT_ROTXLIMIT,
    PT_ROTYLIMIT,
    PT_ROTZLIMIT,
    PT_JOINT_END
};

class ParseMap : public QMap<QString, ParseToken>
{
public:
  ParseMap()
  {
    insert("balljoint",PT_BALLJOINT);
    insert("{", PT_JOINT_START);
    insert("}", PT_JOINT_END);
    insert("offset", PT_OFFSET);
    insert("boxmin", PT_BOXMIN);
    insert("boxmax", PT_BOXMAX);
    insert("pose", PT_POSE);
    insert("rotxlimit", PT_ROTXLIMIT);
    insert("rotylimit", PT_ROTYLIMIT);
    insert("rotzlimit", PT_ROTZLIMIT);
  }
};
static ParseMap const sg_reserved;

class SkelontonParser
{
public:
    SkelontonParser(QFile *file);
    ~SkelontonParser();
private:
    QFile* m_file;
    QString m_lexicon;
    QString m_currentLine;
    BallJoint* currJoint;
    bool parse();
    ParseToken lexToken();
};

#endif // SKELONTONPARSER_H
