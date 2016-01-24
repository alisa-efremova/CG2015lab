#include "viewerinputcontroller.h"

static float MOUSE_SPEED = 0.2;
static float WHEEL_SPEED = 0.005;

ViewerInputController::ViewerInputController()
{
}

void ViewerInputController::setScene(std::shared_ptr<BaseScene> scene)
{
    m_scene = scene;
    saveCameraAttr();
}

void ViewerInputController::updateCamera()
{
    m_scene->camera().loadMatrix();
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
           m_scene->camera().rotateAroundCenter(diff * MOUSE_SPEED);
           ptrMousePosition = mouseEvent->pos();
        }
    }
    else if (event->type() == QEvent::Wheel)
    {
        QWheelEvent *wheelEvent = (QWheelEvent *)event;
        m_scene->camera().moveForward(WHEEL_SPEED * wheelEvent->delta());
    }
}

void ViewerInputController::saveCameraAttr()
{
    m_eye = m_scene->camera().eye();
    m_at = m_scene->camera().at();
    m_up = m_scene->camera().up();
    m_yRot = m_scene->camera().getRotatAngles().y();
    m_zRot = m_scene->camera().getRotatAngles().z();
}

void ViewerInputController::restoreCameraAttr()
{
    m_scene->camera().lookAt(m_eye, m_at, m_up);
    m_scene->camera().setRotatAngles(QVector3D(0, m_yRot, m_zRot));
}
