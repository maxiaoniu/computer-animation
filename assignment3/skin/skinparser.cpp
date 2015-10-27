#include "skinparser.h"
#include <QDebug>
#include <QVector3D>
#include <QString>
#include <QRegularExpression>

SkinParser::SkinParser(QFile *file)
{
    m_file = file;
    file->open(QFile::ReadOnly | QFile::Text);
    parse();
    initGL();
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

        switch (lexToken()) {
        case PT_POS:
        {
            int number = m_currentLine.section(" ",1, 1).toInt();
            while (number--) {
                m_currentLine.clear();
                m_currentLine = in.readLine();
                m_currentLine = m_currentLine.trimmed();

                QStringList strList = m_currentLine.split(' ',QString::SkipEmptyParts);

                SkinedVertex *vertex = new SkinedVertex();

                vertex->m_position = QVector3D(strList[0].toFloat(),
                                                strList[1].toFloat(),
                                                strList[2].toFloat());

                skinVertexs.append(vertex);
            }
            break;
        }
        case PT_NORMALS:
        {
            for(int i = 0; i< skinVertexs.size(); ++i) {
                m_currentLine.clear();
                m_currentLine = in.readLine();
                m_currentLine = m_currentLine.trimmed();

                QStringList strList = m_currentLine.split(' ',QString::SkipEmptyParts);

                skinVertexs[i]->m_normal = QVector3D(strList[0].toFloat(),
                                                strList[1].toFloat(),
                                                strList[2].toFloat());
            }
            break;
        }
        case PT_SKINWEIGHT:
        {
            for(int i = 0; i< skinVertexs.size(); ++i) {
                m_currentLine.clear();
                m_currentLine = in.readLine();
                m_currentLine = m_currentLine.trimmed();

                QStringList strList = m_currentLine.split(' ',QString::SkipEmptyParts);
                int n = strList[0].toInt();

                for(int j=0; j< n; ++j) {
                    skinVertexs[i]->m_jointIndex[j] = strList[1+2*j].toInt();
                    skinVertexs[i]->m_jointWeight[j] = strList[2+2*j].toFloat();
                }
                qDebug()<< skinVertexs[i]->m_jointWeight[0];
            }
            break;
        }
        case PT_TRIANGLES:
        {
            int number = m_currentLine.section(" ",1, 1).toInt();
            while (number--) {
                m_currentLine.clear();
                m_currentLine = in.readLine();
                m_currentLine = m_currentLine.trimmed();

                QStringList strList = m_currentLine.split(' ',QString::SkipEmptyParts);
                triangles.append(strList[0].toInt());
                triangles.append(strList[1].toInt());
                triangles.append(strList[2].toInt());
            }
            break;
        }
        case PT_BINDING:
        {
            int number = m_currentLine.section(" ", 1, 1).toInt();
            bindingsMatrix.resize(number);
            for(int i = 0; i < number; i++) {
                QMatrix4x4 *matrix =  new QMatrix4x4();

                m_currentLine.clear();
                m_currentLine = in.readLine();
                m_currentLine.clear();
                m_currentLine = in.readLine();
                m_currentLine = m_currentLine.trimmed();
                QStringList strList = m_currentLine.split(' ',QString::SkipEmptyParts);
                matrix->setRow(0,QVector4D(strList[0].toFloat(),strList[1].toFloat(),
                                          strList[2].toFloat(),0.0f));

                m_currentLine.clear();
                m_currentLine = in.readLine();
                m_currentLine = m_currentLine.trimmed();
                strList = m_currentLine.split(' ',QString::SkipEmptyParts);
                matrix->setRow(1,QVector4D(strList[0].toFloat(),strList[1].toFloat(),
                                          strList[2].toFloat(),0));
                m_currentLine.clear();
                m_currentLine = in.readLine();
                m_currentLine = m_currentLine.trimmed();
                strList = m_currentLine.split(' ',QString::SkipEmptyParts);
                matrix->setRow(2,QVector4D(strList[0].toFloat(),strList[1].toFloat(),
                                          strList[2].toFloat(),0));
                m_currentLine.clear();
                m_currentLine = in.readLine();
                m_currentLine = m_currentLine.trimmed();
                strList = m_currentLine.split(' ',QString::SkipEmptyParts);
                matrix->setRow(3,QVector4D(strList[0].toFloat(),strList[1].toFloat(),
                                          strList[2].toFloat(),1));

                bindingsMatrix[i] = matrix;
                m_currentLine.clear();
                m_currentLine = in.readLine();
            }

        }
        default:
            break;
        }
    }
}

void SkinParser::initGL() {
    QOpenGLFunctions f = QOpenGLFunctions(QOpenGLContext::currentContext());
    m_vBuffer= new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_eBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

    m_vBuffer->create();
    m_eBuffer->create();

    m_vBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_eBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);

    m_vao = new QOpenGLVertexArrayObject();
    m_vao ->create();
    m_vao -> bind();

    struct vertex{
        GLfloat m_position[3];
        GLfloat m_normal[3];
        GLfloat m_jointIndex[4];
        GLfloat m_jointWeight[4];
    };

    m_vBuffer->bind();
    m_vBuffer->allocate(sizeof(vertex)*skinVertexs.size());
    vertex *data = (vertex *)m_vBuffer->map(QOpenGLBuffer::WriteOnly);
    for(size_t i = 0; i< (size_t)skinVertexs.size(); ++i) {
        data[i].m_position[0] = skinVertexs[i]->m_position.x();
        data[i].m_position[1] = skinVertexs[i]->m_position.y();
        data[i].m_position[2] = skinVertexs[i]->m_position.z();

        data[i].m_normal[0] = skinVertexs[i]->m_normal.x();
        data[i].m_normal[1] = skinVertexs[i]->m_normal.y();
        data[i].m_normal[2] = skinVertexs[i]->m_normal.z();
        qDebug()<<"vertex"<<i;
        for(int j=0; j< 4;++j) {
            data[i].m_jointIndex[j] = skinVertexs[i]->m_jointIndex[j];
            qDebug()<<"index"<<j<<" "<<data[i].m_jointIndex[j];
            data[i].m_jointWeight[j] = skinVertexs[i]->m_jointWeight[j];
            qDebug()<<"weight"<<j<<" "<<data[i].m_jointWeight[j];
        }
    }
    m_vBuffer->unmap();
    m_eBuffer->bind();
    m_eBuffer->allocate(sizeof(int)*triangles.size());
    int *index_data = (int *)m_eBuffer->map(QOpenGLBuffer::WriteOnly);
    for(size_t i =0; i< (size_t)triangles.size();++i) {
        index_data[i] = triangles[i];
    }
    m_eBuffer->unmap();
    f.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),(void*)offsetof(vertex, m_position));
    f.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),(void*)offsetof(vertex, m_normal));
    f.glVertexAttribPointer(2, 4, GL_FLOAT,   GL_FALSE, sizeof(vertex),(void*)offsetof(vertex, m_jointIndex));
    f.glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(vertex),(void*)offsetof(vertex, m_jointWeight));

    f.glEnableVertexAttribArray(0);
    f.glEnableVertexAttribArray(1);    
    f.glEnableVertexAttribArray(2);
    f.glEnableVertexAttribArray(3);

    m_vao->release();
    m_eBuffer->release();
    m_vBuffer->release();
}
void SkinParser::draw()
{
    m_vao->bind();
    QOpenGLFunctions f(QOpenGLContext::currentContext());

    f.glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_INT, 0);
    m_vao->release();

}
