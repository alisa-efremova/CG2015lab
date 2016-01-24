#pragma once

#include "basescene.h"

class GameScene : public BaseScene
{
    Q_OBJECT
public:
    GameScene(QSize viewportSize = QSize(0, 0));
    virtual ~GameScene();
};

