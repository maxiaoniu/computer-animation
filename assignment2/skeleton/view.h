#ifndef VIEW_H
#define VIEW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <QOpenGLWidget>
#include <QTimer>
#include "skelonton.h"
#include "camera.h"
#include "trackball.h"
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

  QTimer *m_timer;
  TrackBall m_trackball;
  QMatrix4x4 m_projection;
  Camera m_camera;
  QMatrix4x4 m_transform;

  int rotateX;
  int rotateY;
  int rotateZ;
public slots:
  void recFile(const QString &name);
  void worldRotationX(int angle);
  void worldRotationY(int angle);
  void worldRotationZ(int angle);
};

#endif // VIEW_H
