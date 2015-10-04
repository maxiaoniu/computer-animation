#ifndef VIEW_H
#define VIEW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <QOpenGLWidget>
#include "skelonton.h"
#include "camera.h"
#include "trackball.h"
class QTimer;
class QOpenGLShaderProgram;

class view : public QOpenGLWidget,
               protected QOpenGLFunctions
{
  Q_OBJECT

public:
    explicit view(QWidget *parent = 0);
    ~view();
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);
protected slots:
    void teardownGL();
    //void update();
private:
  // OpenGL State Information
  QPointF PosToViewPos(const QPoint& p);

  QOpenGLBuffer m_vertex;
  QOpenGLVertexArrayObject m_object;
  QOpenGLVertexArrayObject m_object1;
  QOpenGLShaderProgram *m_program;
  Skelonton *skel;

  // Shader Information
  int u_modelToWorld;
  int u_worldToCamera;
  int u_cameraToView;

  //QTimer *m_timer;
  TrackBall m_trackball;
  QMatrix4x4 m_projection;
  Camera m_camera;
  QMatrix4x4 m_transform;

};

#endif // VIEW_H
