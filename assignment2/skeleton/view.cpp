#include "view.h"
#include <QDebug>
#include <QString>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include <QTimer>
#include "vertex.h"
#include "skelontonparser.h"
#include "skelonton.h"
#include "balljoint.h"

// Front Verticies
#define VERTEX_FTR Vertex( QVector3D( 0.5f,  0.5f,  0.5f), QVector3D( 1.0f, 1.0f, 1.0f ) )
#define VERTEX_FTL Vertex( QVector3D(-0.5f,  0.5f,  0.5f), QVector3D( 1.0f, 1.0f, 1.0f ) )
#define VERTEX_FBL Vertex( QVector3D(-0.5f, -0.5f,  0.5f), QVector3D( 1.0f, 1.0f, 1.0f ) )
#define VERTEX_FBR Vertex( QVector3D( 0.5f, -0.5f,  0.5f), QVector3D( 1.0f, 1.0f, 1.0f ) )

// Back Verticies
#define VERTEX_BTR Vertex( QVector3D( 0.5f,  0.5f, -0.5f), QVector3D( 1.0f, 1.0f, 1.0f ) )
#define VERTEX_BTL Vertex( QVector3D(-0.5f,  0.5f, -0.5f), QVector3D( 1.0f, 1.0f, 1.0f ) )
#define VERTEX_BBL Vertex( QVector3D(-0.5f, -0.5f, -0.5f), QVector3D( 1.0f, 1.0f, 1.0f ) )
#define VERTEX_BBR Vertex( QVector3D( 0.5f, -0.5f, -0.5f), QVector3D( 1.0f, 1.0f, 1.0f ) )

// Create a colored cube
static const Vertex sg_vertexes[] = {
  // Face 1 (Front)
    VERTEX_FTR, VERTEX_FTL, VERTEX_FBL,
    VERTEX_FBL, VERTEX_FBR, VERTEX_FTR,
  // Face 2 (Back)
    VERTEX_BBR, VERTEX_BTL, VERTEX_BTR,
    VERTEX_BTL, VERTEX_BBR, VERTEX_BBL,
  // Face 3 (Top)
    VERTEX_FTR, VERTEX_BTR, VERTEX_BTL,
    VERTEX_BTL, VERTEX_FTL, VERTEX_FTR,
  // Face 4 (Bottom)
    VERTEX_FBR, VERTEX_FBL, VERTEX_BBL,
    VERTEX_BBL, VERTEX_BBR, VERTEX_FBR,
  // Face 5 (Left)
    VERTEX_FBL, VERTEX_FTL, VERTEX_BTL,
    VERTEX_FBL, VERTEX_BTL, VERTEX_BBL,
  // Face 6 (Right)
    VERTEX_FTR, VERTEX_FBR, VERTEX_BBR,
    VERTEX_BBR, VERTEX_BTR, VERTEX_FTR
};

#undef VERTEX_BBR
#undef VERTEX_BBL
#undef VERTEX_BTL
#undef VERTEX_BTR

#undef VERTEX_FBR
#undef VERTEX_FBL
#undef VERTEX_FTL
#undef VERTEX_FTR

view::view(QWidget *parent) : QOpenGLWidget(parent)
{
    //m_timer = new QTimer(this);
    //m_timer->setInterval(30);
    //connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    //m_timer->start();
     //this->setFocusPolicy(Qt::StrongFocus);

    QFile mfile(QString("/Users/mayue/test.skel"));
    SkelontonParser parser(&mfile);
    skel = parser.skel;
    qDebug()<<skel->tree.size();
    m_projection.setToIdentity();
    m_projection.perspective(45.0f, 1, 0.0f, 1000.0f);
    m_camera.setToIdentity();
    m_camera.setTranslation(0,0,-5);
    update();
}
view::~view() {

}

void view::initializeGL()
{
  // Initialize OpenGL Backend
  initializeOpenGLFunctions();
  connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(teardownGL()), Qt::DirectConnection);
  connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));

  //glEnable(GL_CULL_FACE);
  glPolygonOffset(2.0f, 2.0f);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  //glPolygonOffset( -0.1f, 0.2f );
  {
    // Create Shader (Do not release until VAO is created)
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader/simple.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader/simple.frag");
    m_program->link();
    m_program->bind();

    // Cache Uniform Locations
    u_modelToWorld = m_program->uniformLocation("modelToWorld");
    u_worldToCamera = m_program->uniformLocation("worldToCamera");
    u_cameraToView = m_program->uniformLocation("cameraToView");

    // Create Buffer (Do not release until VAO is created)
    m_vertex.create();
    m_vertex.bind();
    m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertex.allocate(sg_vertexes, sizeof(sg_vertexes));

    // Create Vertex Array Object
    m_object.create();
    m_object.bind();
    m_program->enableAttributeArray(0);
    m_program->enableAttributeArray(1);
    m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
    m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());

    // Release (unbind) all
    m_object.release();
    m_vertex.release();
    m_program->release();
  }
}

void view::resizeGL(int width, int height)
{
    m_projection.setToIdentity();
    m_projection.perspective(45.0f, width / float(height), 0.0f, 1000.0f);
}

void view::paintGL()
{
  // Clear
  glClear(GL_COLOR_BUFFER_BIT);

  // Render using our shader
  m_program->bind();

  m_program->setUniformValue(u_worldToCamera,m_camera.getMatrix());
  m_program->setUniformValue(u_cameraToView, m_projection);
  //qDebug()<<m_camera.getMatrix();
  {
    m_object.bind();
    QHash<BallJoint*, BallJoint*>::const_iterator it = skel->tree.begin();
    while(it != skel->tree.constEnd()) {
        BallJoint* currJoint = it.key();
        currJoint->getLocalPos();
        if(currJoint == skel->root)
            currJoint->localPos.rotate(m_trackball.rotation());
        ++it;
    }
    it = skel->tree.begin();
    while(it != skel->tree.constEnd()) {
        BallJoint* currJoint = it.key();
        QMatrix4x4 boneModel = currJoint->localPos;
        QVector3D scaleFactor = currJoint->getScaleFactor();
        QVector3D translateFactor = currJoint->getTranslation();
        boneModel.translate(translateFactor);
        boneModel.scale(scaleFactor);

         //qDebug()<<boneModel;
         //boneModel.rotate(m_trackball.rotation());
        //qDebug()<<boneModel;
        while(skel->tree[currJoint] != NULL) {
            currJoint = skel->tree[currJoint];
            boneModel = (currJoint->localPos)*boneModel;
        }
        m_program->setUniformValue(u_modelToWorld, boneModel);
        //glEnable(GL_POLYGON_OFFSET_FILL);
        //glPolygonOffset(2.0f, 2.0f);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
        //glDisable(GL_POLYGON_OFFSET_FILL);
        ++it;
    }

    m_object.release();
  }
  m_program->release();
}
void view::teardownGL()
{
  // Actually destroy our OpenGL information
  m_object.destroy();
  m_vertex.destroy();
  delete m_program;
}


//the zero point of widget is left-up corner
//the view's zero point is in the center of the widget and from -1~1
QPointF view::PosToViewPos(const QPoint& p)
{
    return QPointF(2.0 * float(p.x()) / width() - 1.0,
                   1.0 - 2.0 * float(p.y()) / height());
}


void view::mousePressEvent(QMouseEvent *event)
{
    qDebug()<< event->button();
    if(event->button() & Qt::LeftButton)
    {
        m_trackball.push(PosToViewPos(event->pos()));
    }
    //camera
    if(event->button() & Qt::RightButton)
    {
        //m_trackballCamera.push(PosToViewPos(event->pos()));
    }
}


void view::mouseReleaseEvent(QMouseEvent *event)
{

    if(event->buttons() & Qt::LeftButton)
    {
        m_trackball.release(PosToViewPos(event->pos()),QQuaternion());
    }

    if(event->buttons() & Qt::RightButton)
    {
        //m_trackballCamera.release(PosToViewPos(event->pos()),QQuaternion());
    }
}

void view::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        m_trackball.move(PosToViewPos(event->pos()),QQuaternion());
    }
}

void view::keyPressEvent(QKeyEvent *event)
{
    float  moveSpeed;
    moveSpeed = 1;
    QVector3D translation;
    qDebug()<<event->key();
    switch(event->key())
    {
    case Qt::Key_W:
        translation += m_camera.forward();
        break;
    case Qt::Key_S:
        translation -= m_camera.forward();

        break;
    case Qt::Key_A:
        translation -= m_camera.right();

        break;
    case Qt::Key_D:
        translation += m_camera.right();

        break;
    case Qt::Key_Q:
        translation += m_camera.up();

        break;
    case Qt::Key_E:
        translation -= m_camera.up();

        break;
    case Qt::Key_Up:
        m_camera.rotate(5.0f, m_camera.right());
        break;
    case Qt::Key_Down:
        m_camera.rotate(-5.0f, m_camera.right());
        break;
    case Qt::Key_Right:
        m_camera.rotate(-5.0f, m_camera.up());
        break;
    case Qt::Key_Left:
        m_camera.rotate(5.0f,m_camera.up());
        break;
    case Qt::Key_Comma:
        m_camera.rotate(-5.0f, m_camera.forward());
        break;
    case Qt::Key_Period:
        m_camera.rotate(5.0f,m_camera.forward());
        break;
    default:
        break;
    }
    m_camera.translate(moveSpeed*translation);
    qDebug()<< m_camera.getMatrix();
    //m_camera.translate(translation);
}

