#pragma once

#include "../gl/basescene.h"
#include <QEvent>
#include <QKeyEvent>
#include <memory>

class InputController : public QObject
{
    Q_OBJECT
public:
    virtual ~InputController() = default;

    virtual void handleEvent(QEvent *event) = 0;
    virtual void updateCamera() = 0;
    virtual void saveCameraAttr() = 0;
    virtual void restoreCameraAttr() = 0;

    virtual void setScene(std::shared_ptr<BaseScene> scene) = 0;
};
