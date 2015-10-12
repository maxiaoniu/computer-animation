#include "skelontonparser.h"
#include <QDebug>
#include <QVector3D>
#include <QString>
#include <QRegularExpression>

SkelontonParser::SkelontonParser(QFile *file)
{
    m_file = file;
    currJoint = NULL;
    skel = new Skelonton();
    file->open(QFile::ReadOnly | QFile::Text);
    parse();
}

SkelontonParser::~SkelontonParser()
{
   // delete skel;
}


ParseToken SkelontonParser::lexToken()
{
    ParseMap::const_iterator it = sg_reserved.find(m_lexicon);

    return it.value();
}


bool SkelontonParser::parse()
{

    QTextStream in(m_file);
    qDebug()<<"begin";
    while(!in.atEnd()) {
        m_currentLine.clear();
        m_currentLine = in.readLine();

        //delete the empty char in the begin and end of current line
        m_currentLine = m_currentLine.trimmed();

        m_lexicon.clear();

        m_lexicon = m_currentLine.section(" ", 0, 0);
        QStringList strList = m_currentLine.split(' ',QString::SkipEmptyParts);

        switch(lexToken())
        {
            case PT_BALLJOINT:
                qDebug()<<m_currentLine;
                parseBallJoint();
                break;
            case PT_JOINT_END:
                parseEnd();
                break;
            case PT_BOXMAX:
                currJoint->boxmax = QVector3D(strList[1].toFloat(),
                                                strList[2].toFloat(),
                                                strList[3].toFloat());
                break;
        case PT_BOXMIN:
            currJoint->boxmin = QVector3D(strList[1].toFloat(),
                                            strList[2].toFloat(),
                                            strList[3].toFloat());
            break;
        case PT_OFFSET:
            currJoint->offset = QVector3D(strList[1].toFloat(),
                                            strList[2].toFloat(),
                                            strList[3].toFloat());
            break;
        case PT_POSE:
            currJoint->pose = QVector3D(strList[1].toFloat(),
                                            strList[2].toFloat(),
                                            strList[3].toFloat());
            break;
        case PT_ROTXLIMIT:
            currJoint->rotxlimit = QVector2D(strList[1].toFloat(),
                                            strList[2].toFloat());
            break;
        case PT_ROTYLIMIT:
            currJoint->rotylimit = QVector2D(strList[1].toFloat(),
                                            strList[2].toFloat());
            break;
        case PT_ROTZLIMIT:
            currJoint->rotzlimit = QVector2D(strList[1].toFloat(),
                                            strList[2].toFloat());
            break;

         default:
                break;
        }

    }
    return true;
}

void SkelontonParser::parseBallJoint() {
    currJoint = new BallJoint();
    currJoint->name = m_currentLine.section(" ", 1, 1);
    if(stackParent.isEmpty()) {
        skel->root = currJoint;
        skel->tree[currJoint] = NULL;
    }
    else {
        skel->tree[currJoint] = stackParent.top();
    }
    stackParent.push(currJoint);
}

void SkelontonParser::parseEnd() {
    if(!stackParent.isEmpty())
        stackParent.pop();
}





















