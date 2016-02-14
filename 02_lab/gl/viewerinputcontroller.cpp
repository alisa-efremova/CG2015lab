#include "viewerinputcontroller.h"

static float MOUSE_SPEED = 0.2;
static float WHEEL_SPEED = 0.005;

ViewerInputController::ViewerInputController(SceneCamera * camera)
    : m_camera(camera)
{
}

void ViewerInputController::handleEvent(QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
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
           m_camera->rotateAroundCenter(diff * MOUSE_SPEED);
           ptrMousePosition = mouseEvent->pos();
        }
    }
    else if (event->type() == QEvent::Wheel)
    {
        QWheelEvent *wheelEvent = (QWheelEvent *)event;
        m_camera->moveForward(WHEEL_SPEED * wheelEvent->delta());
    }
}

void ViewerInputController::saveCameraAttr()
{
    m_eye = m_camera->eye();
    m_at = m_camera->at();
    m_up = m_camera->up();
    m_yRot = m_camera->getRotatationAngles().y();
    m_zRot = m_camera->getRotatationAngles().z();
}

void ViewerInputController::restoreCameraAttr()
{
    m_camera->lookAt(m_eye, m_at, m_up);
    m_camera->setRotationAngles(QVector3D(0, m_yRot, m_zRot));
}
