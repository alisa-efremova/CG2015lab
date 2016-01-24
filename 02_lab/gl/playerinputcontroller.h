#pragma once

#include "inputcontroller.h"
#include "basescene.h"
#include <QEvent>
#include <memory>
#include <map>

class PlayerInputController : public InputController
{
public:
    PlayerInputController(SceneCamera * camera);
    virtual void handleEvent(QEvent * event) override;
    virtual void saveCameraAttr() override;
    virtual void restoreCameraAttr() override;


private:
    SceneCamera * m_camera;

    QVector3D m_eye;
    QVector3D m_at;
    QVector3D m_up;

    enum direction { EMPTY, UP, DOWN, LEFT, RIGHT, FORWARD, BACKWARD };
    void processKeyEvent(QKeyEvent * keyEvent);
    float getSpeedByDirection(const int direction, const int reverseDirection, const int currentDirection);

    const std::map<int, int> m_keyMap =
    {
        {Qt::Key_W,     FORWARD},
        {Qt::Key_A,     LEFT},
        {Qt::Key_S,     BACKWARD},
        {Qt::Key_D,     RIGHT},
        {Qt::Key_Up,    UP},
        {Qt::Key_Left,  LEFT},
        {Qt::Key_Down,  DOWN},
        {Qt::Key_Right, RIGHT}
    };

    std::map<int, bool> m_direction =
    {
        {LEFT,     false},
        {RIGHT,    false},
        {FORWARD,  false},
        {BACKWARD, false},
        {UP,       false},
        {DOWN,     false}
    };

    bool isMousePressed = false;
    QPoint ptrMousePosition;
};
