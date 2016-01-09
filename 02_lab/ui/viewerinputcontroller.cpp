#include "viewerinputcontroller.h"

ViewerInputController::ViewerInputController()
{

}

void ViewerInputController::handleEvent(QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = (QKeyEvent *)event;
        switch (keyEvent->key())
        {
        case Qt::Key_Left:
            rotateLeft();
            break;

        case Qt::Key_Right:
            rotateRight();
            break;

        case Qt::Key_Up:
            rotateUp();
            break;

        case Qt::Key_Down:
            rotateDown();
            break;
        }
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
        moveByMouse(mouseEvent);
    }
    else if (event->type() == QEvent::Wheel)
    {
        QWheelEvent *wheelEvent = (QWheelEvent *)event;
        changeDistance(wheelEvent);
    }
}

void ViewerInputController::setScene(std::shared_ptr<BaseScene> scene)
{
    m_scene = scene;
}

void ViewerInputController::updateCamera()
{
    m_scene->camera().loadMatrix(QVector3D(xRot, yRot, zRot), QVector3D(xMov, 0.0f, 0.0f));
}

void ViewerInputController::rotateLeft()
{
   zRot += 1.0;
}

void ViewerInputController::rotateRight()
{
   zRot -= 1.0;
}

void ViewerInputController::rotateUp()
{
   yRot += 1.0;
}

void ViewerInputController::rotateDown()
{
   yRot -= 1.0;
}

void ViewerInputController::moveByMouse(QMouseEvent* event)
{
    if (isMousePressed)
    {
        yRot -= (event->y()-ptrMousePosition.y())/10;
        if (yRot > 90) yRot = 90;
        if (yRot < 0) yRot = 0;

        zRot -= (event->x()-ptrMousePosition.x())/10;

        ptrMousePosition = event->pos();
    }
}

void ViewerInputController::changeDistance(QWheelEvent* event)
{
    if ((event->delta())>0) xMov += 1; else if ((event->delta())<0) xMov -= 1;
    if (xMov < -10) xMov = -10;
    if (xMov > 3) xMov = 3;
}
