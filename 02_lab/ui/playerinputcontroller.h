#pragma once

#include "inputcontroller.h"
#include "../gl/basescene.h"
#include <QEvent>
#include <memory>

class PlayerInputController : public InputController
{
public:
    PlayerInputController();
    virtual void handleEvent(QEvent * event) override;
    virtual void setScene(std::shared_ptr<BaseScene> scene) override;
    virtual void updateCamera() override;

private:
    std::shared_ptr<BaseScene> m_scene;
    void rotateLeft();

    float xRot = 0;
    float yRot = 0;
    float zRot = 0;
    float xMov = 0;

    bool isMousePressed = false;
    QPoint ptrMousePosition;
};
