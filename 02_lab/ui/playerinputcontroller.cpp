#include "playerinputcontroller.h"

PlayerInputController::PlayerInputController()
{
}

void PlayerInputController::handleEvent(QEvent * event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = (QKeyEvent *)event;
        switch (keyEvent->key())
        {
        case Qt::Key_A:
            rotateLeft();
            break;

        }
    }
}

void PlayerInputController::rotateLeft()
{
   zRot += 1.0;
}

void PlayerInputController::setScene(std::shared_ptr<BaseScene> scene)
{
    m_scene = scene;
}

void PlayerInputController::updateCamera()
{
    m_scene->camera().loadMatrix(QVector3D(xRot, yRot, zRot), QVector3D(xMov, 0.0f, 0.0f));
}

