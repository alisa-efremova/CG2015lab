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
    virtual void saveCameraAttr() override;
    virtual void restoreCameraAttr() override;

private:
    std::shared_ptr<BaseScene> m_scene;

    float m_yRot = 0;
    float m_zRot = 0;

    QVector3D m_eye;
    QVector3D m_at;
    QVector3D m_up;

    bool isMousePressed = false;
    QPoint ptrMousePosition;
};
