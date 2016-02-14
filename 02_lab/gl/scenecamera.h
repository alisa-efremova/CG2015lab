#pragma once

#include <QObject>
#include <QVector3D>
#include <QSize>
#include <stdint.h>

/// Static camera, can be manually controlled.
class SceneCamera : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(SceneCamera)
    Q_PROPERTY(QSize viewport READ viewport WRITE setViewport)
    Q_PROPERTY(QVector3D eye READ eye)
public:
    explicit SceneCamera(QSize viewport, QObject *parent = 0);

    void loadMatrix();
    void lookAt(QVector3D const &eye, QVector3D const& at, QVector3D const& up);
    /// @param msec - milliseconds since last advance or creation.
    void advance(int64_t msec);

    void rotateAroundCenter(QPoint step);
    void rotate(QPoint step);
    void moveForward(float step);

    QSize viewport() const;
    void setViewport(QSize viewport);
    QVector3D eye() const;
    QVector3D at() const;
    QVector3D up() const;

    void setSpeed(QVector3D speed);
    QVector3D speed() const;

    void setRotationAngles(QVector3D rotatAngles);
    QVector3D getRotatationAngles() const;

private:
    QSize m_viewport;
    QVector3D m_eye;   /**< Eye position */
    QVector3D m_front; /**< Front direction */
    QVector3D m_up;    /**< Up direction */
    QVector3D m_speed; /**< Speed, meters per second, front/left/up */
    QVector3D m_rotationAngles;
};
