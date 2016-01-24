#include "window3d.h"
#include <QResizeEvent>
#include <QPainter>
#include <QGuiApplication>

Window3D::Window3D(QWindow *parent)
    : QWindow(parent)
{
    setSurfaceType(QWindow::OpenGLSurface);
    setFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    m_viewerController = std::make_shared<ViewerInputController>();
    m_playerController = std::make_shared<PlayerInputController>();
    m_activeController = m_viewerController;
    installEventFilter(this);
    m_viewerController->installEventFilter(this);
    m_playerController->installEventFilter(this);
}

bool Window3D::eventFilter(QObject *target, QEvent *event)
{
    /*if (event->type() == QEvent::KeyPress)
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
        return true;
      }
      else if (keyEvent->key() == Qt::Key_Escape)
      {
          this->close();
      }
    }

    m_activeController->handleEvent(event);*/
    return QWindow::eventFilter(target, event);
}

void Window3D::setFixedSize(QSize size)
{
    setMinimumSize(size);
    setMaximumSize(size);
}

void Window3D::pushScene(std::shared_ptr<BaseScene> scene)
{
    m_sceneStack.push_back(scene);
    scene->onPush();

    m_playerController->setScene(scene);
    m_viewerController->setScene(scene);
}

void Window3D::popScene()
{
    if (!m_sceneStack.empty())
    {
        m_sceneStack.back()->onPop();
        m_sceneStack.pop_back();
    }
}

bool Window3D::event(QEvent *event)
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
        return true;
      }
      else if (keyEvent->key() == Qt::Key_Escape)
      {
          this->close();
      }
    }

    m_activeController->handleEvent(event);

    switch (event->type())
    {
    case QEvent::UpdateRequest:
        m_updatePending = false;
        render();
        return true;
    case QEvent::Close:
        if (m_canRender)
        {
            stopRendering();
        }
        return QWindow::event(event);
    default:
        return QWindow::event(event);
    }
}

void Window3D::exposeEvent(QExposeEvent *event)
{
    QWindow::exposeEvent(event);
    if (isExposed())
        render();
}

void Window3D::resizeEvent(QResizeEvent *event)
{
    QWindow::resizeEvent(event);
    if (!m_canRender)
    {
        initRendering();
    }
}

void Window3D::showEvent(QShowEvent *event)
{
    QWindow::showEvent(event);
}

void Window3D::deferRender()
{
    if (!m_updatePending) {
        m_updatePending = true;
        QGuiApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

void Window3D::render()
{
    if (!m_canRender)
    {
        return;
    }

    m_pContext->makeCurrent(this);
    if (!m_sceneStack.empty())
    {
        updateScene(*m_sceneStack.back());
    }
    else
    {
        glClearColor(1, 1, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    m_pContext->swapBuffers(this);
    deferRender();
}

void Window3D::stopRendering()
{
    while (!m_sceneStack.empty())
    {
        popScene();
    }
    m_canRender = false;
}

void Window3D::initRendering()
{
    if (!m_pContext) {
        m_pContext = new QOpenGLContext(this);
        m_pContext->setFormat(requestedFormat());
        m_pContext->create();
    }
    m_canRender = true;
    m_updateTime.start();
}

void Window3D::updateScene(BaseScene &scene)
{
    scene.setViewport(size());

    int msec = m_updateTime.elapsed();
    m_updateTime.restart();
    scene.visit([&](SceneNode & node) {
        node.advance(msec);
    });
    scene.camera().advance(msec);

    QOpenGLPaintDevice device(size());
    QPainter painter(&device);
    m_activeController->updateCamera();
    scene.render(painter);
    scene.visit([&](SceneNode & node) {
        node.render(painter);
    });
}
