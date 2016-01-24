#include "playerinputcontroller.h"
#include <QMatrix4x4>
#include <map>

static float MOUSE_SPEED = 0.2;
static float MOVE_SPEED = 2.0;

PlayerInputController::PlayerInputController(SceneCamera * camera)
    : m_camera(camera)
{
}

void PlayerInputController::saveCameraAttr()
{
    m_eye = m_camera->eye();
    m_at = m_camera->at();
    m_up = m_camera->up();
}

void PlayerInputController::restoreCameraAttr()
{
    m_camera->lookAt(m_eye, m_at, m_up);
    m_camera->setRotatAngles(QVector3D(0, 0, 0));
}

void PlayerInputController::handleEvent(QEvent * event)
{
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *keyEvent = (QKeyEvent *)event;
        QVector3D speed;

        if (keyEvent->type() == QEvent::KeyPress)
        {
            auto it = m_keyMap.find(keyEvent->key());
            if (it != m_keyMap.end())
            {
                (*it).second = true;
            }
        }

        if (keyEvent->type() == QEvent::KeyRelease)
        {
            auto it = m_keyMap.find(keyEvent->key());
            if (it != m_keyMap.end())
            {
                (*it).second = false;
            }
        }

        if (m_direction.left)
        {
            speed.setY(MOVE_SPEED);
        }

        if (m_direction.right)
        {
            speed.setY(-MOVE_SPEED);
        }

        if (m_direction.left && m_direction.right && keyEvent->key() == Qt::Key_A)
        {
            speed.setY(MOVE_SPEED);
        }

        if (m_direction.left && m_direction.right && keyEvent->key() == Qt::Key_D)
        {
            speed.setY(-MOVE_SPEED);
        }

        if (m_direction.up)
        {
            speed.setZ(MOVE_SPEED);
        }

        if (m_direction.down)
        {
            speed.setZ(-MOVE_SPEED);
        }

        if (m_direction.forward)
        {
            speed.setX(MOVE_SPEED);
        }

        if (m_direction.backward)
        {
            speed.setX(-MOVE_SPEED);
        }

        m_camera->setSpeed(speed);
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
        if (isMousePressed)
        {
            QPoint diff = mouseEvent->pos() - ptrMousePosition;
            m_camera->rotate(diff * MOUSE_SPEED);
            ptrMousePosition = mouseEvent->pos();
        }
    }
}


