#include "scenecamera.h"
#include "glhelper.h"
#include <QMatrix4x4>

static float Y_ROT_MAX_ANGLE = 90;
static float Y_ROT_MIN_ANGLE = 0;

SceneCamera::SceneCamera(QSize viewport, QObject *parent)
    : QObject(parent)
    , m_viewport(viewport)
{
}

void SceneCamera::loadMatrix()
{
    QMatrix4x4 matrix;
    matrix.lookAt(m_eye, m_eye + m_front, m_up);

    QVector3D left = QVector3D::crossProduct(m_up, m_front);
    matrix.rotate(-m_rotatAngles.y(), left);
    matrix.rotate(m_rotatAngles.z(), m_up);

    GLHelper::setModelViewMatrix(matrix);
}

void SceneCamera::lookAt(const QVector3D &eye, const QVector3D &at, const QVector3D &up)
{
    m_eye = eye;
    m_front = at - eye;
    m_up = up;
    m_front.normalize();
}

void SceneCamera::advance(int64_t msec)
{
    QVector3D left = QVector3D::crossProduct(m_up, m_front);
    float seconds = float(msec) * 0.001f;
    float dFront = m_speed.x() * seconds;
    float dLeft = m_speed.y() * seconds;
    float dUp = m_speed.z() * seconds;
    m_eye += m_front * dFront;
    m_eye += left * dLeft;
    m_eye += m_up * dUp;
}

void SceneCamera::rotateAroundCenter(QPoint step)
{
    m_rotatAngles.setY(m_rotatAngles.y() + step.y());

    if (m_rotatAngles.y() > Y_ROT_MAX_ANGLE) m_rotatAngles.setY(Y_ROT_MAX_ANGLE);
    if (m_rotatAngles.y() < Y_ROT_MIN_ANGLE) m_rotatAngles.setY(Y_ROT_MIN_ANGLE);
    m_rotatAngles.setZ(m_rotatAngles.z() + step.x());
}

void SceneCamera::rotate(QPoint step)
{
    QMatrix4x4 matrix;
    QVector3D left = QVector3D::crossProduct(m_up, m_front);
    matrix.rotate(-1 * step.x(), m_up);
    matrix.rotate(step.y(), left);
    m_front = matrix * m_front;
}

void SceneCamera::moveForward(float step)
{
    m_eye += m_front * step;
}

QSize SceneCamera::viewport() const
{
    return m_viewport;
}

void SceneCamera::setViewport(QSize viewport)
{
    m_viewport = viewport;
}

QVector3D SceneCamera::eye() const
{
    return m_eye;
}

QVector3D SceneCamera::at() const
{
    return m_eye + m_front;
}
QVector3D SceneCamera::up() const
{
    return m_up;
}

void SceneCamera::setSpeed(QVector3D speed)
{
    m_speed = speed;
}

QVector3D SceneCamera::speed() const
{
    return m_speed;
}

void SceneCamera::setRotatAngles(QVector3D rotatAngles)
{
    m_rotatAngles = rotatAngles;
}

QVector3D SceneCamera::getRotatAngles() const
{
    return m_rotatAngles;
}
