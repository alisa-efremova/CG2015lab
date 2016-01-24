#pragma once

#include "basescene.h"
#include "inputcontroller.h"
#include "playerinputcontroller.h"
#include "viewerinputcontroller.h"

class GameScene : public BaseScene
{
    Q_OBJECT
public:
    GameScene(QSize viewportSize = QSize(0, 0));
    virtual ~GameScene();

    virtual void handleEvent(QEvent *event) override;

    std::shared_ptr<InputController> m_activeController;
    std::shared_ptr<ViewerInputController> m_viewerController;
    std::shared_ptr<PlayerInputController> m_playerController;
};

