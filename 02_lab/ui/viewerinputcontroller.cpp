#include "viewerinputcontroller.h"

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
    m_scene->camera().loadMatrix(QVector3D(xRot, yRot, zRot));
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
        moveByMouse(mouseEvent);
    }
    else if (event->type() == QEvent::Wheel)
    {
        QWheelEvent *wheelEvent = (QWheelEvent *)event;
        changeDistance(wheelEvent);
    }
}

void ViewerInputController::saveCameraAttr()
{
    m_eye = m_scene->camera().eye();
    m_at = m_scene->camera().at();
    m_up = m_scene->camera().up();
}

void ViewerInputController::restoreCameraAttr()
{
    m_scene->camera().lookAt(m_eye, m_at, m_up);
}

void ViewerInputController::moveByMouse(QMouseEvent* event)
{
    if (isMousePressed)
    {
        yRot += (event->y() - ptrMousePosition.y())/10;
        if (yRot > 90) yRot = 90;
        if (yRot < 0) yRot = 0;

        zRot += (event->x() - ptrMousePosition.x())/10;

        ptrMousePosition = event->pos();
    }
}

void ViewerInputController::changeDistance(QWheelEvent* event)
{
    float step;

    if ((event->delta()) > 0)
    {
        step = -0.5;
    }
    else if ((event->delta()) < 0)
    {
        step = 0.5;
    }

    //todo: add restrictions

    saveCameraAttr();
    m_eye += (m_eye - m_at) * step;
    restoreCameraAttr();
}
