#include "gamescene.h"
#include <memory>
#include "viewerinputcontroller.h"
#include "playerinputcontroller.h"

GameScene::GameScene(QSize viewportSize)
    : BaseScene(viewportSize)
{
    m_viewerController = std::make_shared<ViewerInputController>(&m_camera);
    m_playerController = std::make_shared<PlayerInputController>(&m_camera);
    m_activeController = m_viewerController;
}

GameScene::~GameScene()
{
}

void GameScene::handleEvent(QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
      QKeyEvent *keyEvent = (QKeyEvent *)event;
      if (keyEvent->key() == Qt::Key_Tab)
      {
        m_activeController->saveCameraAttr();
        if (m_activeController == m_viewerController)
        {
            m_activeController = m_playerController;
        }
        else
        {
            m_activeController = m_viewerController;
        }
        m_activeController->restoreCameraAttr();
      }
    }

    m_activeController->handleEvent(event);
}

void GameScene::prepareControllers()
{
    m_playerController->saveCameraAttr();
    m_viewerController->saveCameraAttr();
}
