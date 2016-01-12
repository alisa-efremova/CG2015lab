#include "playerinputcontroller.h"
#include <QMatrix4x4>

PlayerInputController::PlayerInputController()
{
}

void PlayerInputController::setScene(std::shared_ptr<BaseScene> scene)
{
    m_scene = scene;
    saveCameraAttr();
}

void PlayerInputController::updateCamera()
{
    m_scene->camera().loadMatrix(QVector3D(xRot, yRot, zRot));
}

void PlayerInputController::saveCameraAttr()
{
    m_eye = m_scene->camera().eye();
    m_at = m_scene->camera().at();
    m_up = m_scene->camera().up();
}

void PlayerInputController::restoreCameraAttr()
{
    m_scene->camera().lookAt(m_eye, m_at, m_up);
}

void PlayerInputController::handleEvent(QEvent * event)
{
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *keyEvent = (QKeyEvent *)event;
        QVector3D speed = m_scene->camera().speed();
        float maxSpeed = 2.0f;

        switch (keyEvent->key())
        {
        case Qt::Key_Left:
        case Qt::Key_A:
            if (event->type() == QEvent::KeyPress)
            {
                speed.setY(maxSpeed);
            }
            else
            {
                speed.setY(0);
            }
            break;

        case Qt::Key_Right:
        case Qt::Key_D:
            if (event->type() == QEvent::KeyPress)
            {
                speed.setY(-maxSpeed);
            }
            else
            {
                speed.setY(0);
            }
            break;

        case Qt::Key_Up:
            if (event->type() == QEvent::KeyPress)
            {
                speed.setZ(maxSpeed);
            }
            else
            {
                speed.setZ(0);
            }
            break;

        case Qt::Key_Down:
            if (event->type() == QEvent::KeyPress)
            {
                speed.setZ(-maxSpeed);
            }
            else
            {
                speed.setZ(0);
            }
            break;

        case Qt::Key_W:
            if (event->type() == QEvent::KeyPress)
            {
                speed.setX(maxSpeed);
            }
            else
            {
                speed.setX(0);
            }
            break;
        case Qt::Key_S:
            if (event->type() == QEvent::KeyPress)
            {
                speed.setX(-maxSpeed);
            }
            else
            {
                speed.setX(0);
            }
            break;
        }
        m_scene->camera().setSpeed(speed);
    }
    else if (event->type() == QEvent::MouseButtonPress)
    {
       QMouseEvent *mouseEvent = (QMouseEvent *)event;
       ptrMousePosition = mouseEvent->pos();
       isMousePressed = true;
    }
    else if (event->type() == QEvent::MouseButtonRelease)
    {
        isMousePressed = false;
    }
    else if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent *mouseEvent = (QMouseEvent *)event;
        changeDirection(mouseEvent);
    }
}

void PlayerInputController::changeDirection(QMouseEvent * event)
{
    if (isMousePressed)
    {
        saveCameraAttr();

        QPoint diff = event->pos() - ptrMousePosition;

        QMatrix4x4 matrix;
        QVector3D front = m_at - m_eye;
        QVector3D left = QVector3D::crossProduct(m_up, front);
        matrix.rotate(-1 * diff.x() * 0.2f, m_up);
        matrix.rotate(diff.y() * 0.2f, left);
        front = matrix * front;
        m_at = front + m_eye;

        restoreCameraAttr();

        ptrMousePosition = event->pos();
    }
}


