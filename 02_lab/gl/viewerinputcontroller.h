#pragma once

#include "inputcontroller.h"
#include "basescene.h"
#include <QEvent>
#include <memory>

class ViewerInputController : public InputController
{
public:
    ViewerInputController(SceneCamera * camera);
    virtual void handleEvent(QEvent * event) override;
    virtual void saveCameraAttr() override;
    virtual void restoreCameraAttr() override;

private:
    SceneCamera * m_camera;

    float m_yRot = 0;
    float m_zRot = 0;

    QVector3D m_eye;
    QVector3D m_at;
    QVector3D m_up;

    bool isMousePressed = false;
    QPoint ptrMousePosition;
};
