#pragma once

#include "inputcontroller.h"
#include "../gl/basescene.h"
#include <QEvent>
#include <memory>
#include <map>

class PlayerInputController : public InputController
{
public:
    PlayerInputController();
    virtual void handleEvent(QEvent * event) override;
    virtual void setScene(std::shared_ptr<BaseScene> scene) override;
    virtual void updateCamera() override;
    virtual void saveCameraAttr() override;
    virtual void restoreCameraAttr() override;

private:
    std::shared_ptr<BaseScene> m_scene;

    QVector3D m_eye;
    QVector3D m_at;
    QVector3D m_up;

    struct Direction
    {
        bool up       = false;
        bool down     = false;
        bool left     = false;
        bool right    = false;
        bool forward  = false;
        bool backward = false;
    };

    Direction m_direction;

    std::map<int, bool&> m_keyMap =
    {
        {Qt::Key_W,     m_direction.forward},
        {Qt::Key_A,     m_direction.left},
        {Qt::Key_S,     m_direction.backward},
        {Qt::Key_D,     m_direction.right},
        {Qt::Key_Up,    m_direction.up},
        {Qt::Key_Left,  m_direction.left},
        {Qt::Key_Down,  m_direction.down},
        {Qt::Key_Right, m_direction.right}
    };

    bool isMousePressed = false;
    QPoint ptrMousePosition;
};
