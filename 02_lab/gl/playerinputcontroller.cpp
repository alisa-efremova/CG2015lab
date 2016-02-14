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
    m_camera->setRotationAngles(QVector3D(0, 0, 0));
}

void PlayerInputController::handleEvent(QEvent * event)
{
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *keyEvent = (QKeyEvent *)event;
        processKeyEvent(keyEvent);
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

void PlayerInputController::processKeyEvent(QKeyEvent *keyEvent)
{
    QVector3D speed;
    Direction currentKey = EMPTY;
    Direction pressedKey = EMPTY;

    //detect current direction by pressed key
    auto it = m_keyMap.find(keyEvent->key());
    if (it != m_keyMap.end())
    {
        currentKey = (*it).second;
    }

    //process pressed key
    if (keyEvent->type() == QEvent::KeyPress && currentKey != EMPTY)
    {
        m_direction.at((*it).second) = true;
        pressedKey = currentKey;
    }

    //process released key
    if (keyEvent->type() == QEvent::KeyRelease && currentKey != EMPTY)
    {
        m_direction.at((*it).second) = false;
    }

    //set speed
    speed.setY(getSpeedByDirection(LEFT, RIGHT, pressedKey));
    speed.setX(getSpeedByDirection(FORWARD, BACKWARD, pressedKey));
    speed.setZ(getSpeedByDirection(UP, DOWN, pressedKey));

    m_camera->setSpeed(speed);
}

float PlayerInputController::getSpeedByDirection(const Direction direction, const Direction reverseDirection, const Direction currentDirection)
{
    float speedVal = 0;
    if ((m_direction.at(direction) && !m_direction.at(reverseDirection)) || (m_direction.at(direction) && m_direction.at(reverseDirection) && currentDirection == direction))
    {
        speedVal = MOVE_SPEED;
    }

    if ((m_direction.at(reverseDirection) && !m_direction.at(direction)) || (m_direction.at(direction) && m_direction.at(reverseDirection) && currentDirection == reverseDirection))
    {
        speedVal = -MOVE_SPEED;
    }
    return speedVal;
}
