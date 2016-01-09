#pragma once

#include "inputcontroller.h"
#include "../gl/basescene.h"
#include <QEvent>
#include <memory>

class ViewerInputController : public InputController
{
public:
    ViewerInputController();
    virtual void handleEvent(QEvent * event) override;
    virtual void setScene(std::shared_ptr<BaseScene> scene) override;
    virtual void updateCamera() override;

private:
    std::shared_ptr<BaseScene> m_scene;

    float xRot = 0;
    float yRot = 0;
    float zRot = 0;
    float xMov = 0;

    bool isMousePressed = false;
    QPoint ptrMousePosition;

    void rotateLeft();
    void rotateRight();
    void rotateUp();
    void rotateDown();
    void changeDistance(QWheelEvent *event);
    void moveByMouse(QMouseEvent *event);
};
