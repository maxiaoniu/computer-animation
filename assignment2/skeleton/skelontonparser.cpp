#include "skelontonparser.h"
#include <QDebug>

SkelontonParser::SkelontonParser(QFile *file)
{
    m_file = file;
    file->open(QFile::ReadOnly | QFile::Text);
    parse();

}

SkelontonParser::~SkelontonParser()
{

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
        m_lexicon.clear();
        qDebug()<<m_currentLine;
    }
    return true;

}
























