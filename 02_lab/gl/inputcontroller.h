#pragma once

#include "basescene.h"
#include <QEvent>
#include <QKeyEvent>
#include <memory>

class InputController : public QObject
{
    Q_OBJECT
public:
    virtual ~InputController() = default;

    virtual void handleEvent(QEvent *event) = 0;
    virtual void saveCameraAttr() = 0;
    virtual void restoreCameraAttr() = 0;
};
