#include "skinparser.h"
#include <QDebug>
#include <QVector3D>
#include <QString>
#include <QRegularExpression>

SkinParser::SkinParser(QFile *file)
{
    m_file = file;
    skin = new Skin();
    file->open(QFile::ReadOnly | QFile::Text);
    parse();
}
SkinParser::~SkinParser() {

}

SkinParseToken SkinParser::lexToken()
{
    SkinParseMap::const_iterator it = skin_sg_reserved.find(m_lexicon);

    return it.value();
}

bool SkinParser::parse()
{
    QTextStream in(m_file);
    while(!in.atEnd()) {
        m_currentLine.clear();
        m_currentLine = in.readLine();

        m_currentLine = m_currentLine.trimmed();

        m_lexicon.clear();

        m_lexicon = m_currentLine.section(" ", 0, 0);
        int number = m_currentLine.section(" ",1, 1).toInt();
        QStringList strList = m_currentLine.split(' ',QString::SkipEmptyParts);

        switch (lexToken()) {
        case PT_POS:
            qDebug()<<m_currentLine;
            qDebug()<<number;

            break;
        default:
            break;
        }
    }
}
