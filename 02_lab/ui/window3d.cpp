#include "window3d.h"
#include <QResizeEvent>
#include <QPainter>
#include <QGuiApplication>

Window3D::Window3D(QWindow *parent)
    : QWindow(parent)
{
    setSurfaceType(QWindow::OpenGLSurface);
    setFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
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
}

void Window3D::popScene()
{
    if (!m_sceneStack.empty())
    {
        m_sceneStack.back()->onPop();
        m_sceneStack.pop_back();
    }
}

void Window3D::mousePressEvent(QMouseEvent* event)
{
    ptrMousePosition = event->pos();
    isMousePressed = true;
    return QWindow::mousePressEvent(event);
}

void Window3D::mouseReleaseEvent(QMouseEvent* event)
{
    isMousePressed = false;
    return QWindow::mouseReleaseEvent(event);
}

void Window3D::mouseMoveEvent(QMouseEvent* event)
{

    if (isMousePressed)
    {
        yRot -= (event->y()-ptrMousePosition.y())/10;
        if (yRot > 90) yRot = 90;
        if (yRot < 0) yRot = 0;

        zRot -= (event->x()-ptrMousePosition.x())/10;

        ptrMousePosition = event->pos();
    }
    return QWindow::mouseMoveEvent(event);
}

void Window3D::wheelEvent(QWheelEvent* event)
{
    if ((event->delta())>0) xMov += 1; else if ((event->delta())<0) xMov -= 1;
    if (xMov < -10) xMov = -10;
    if (xMov > 3) xMov = 3;

    return QWindow::wheelEvent(event);
}

void Window3D::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        rotateLeft();
        break;

    case Qt::Key_Right:
        rotateRight();
        break;

    case Qt::Key_Up:
        rotateUp();
        break;

    case Qt::Key_Down:
        rotateDown();
        break;

    case Qt::Key_Escape:
        this->close();
        break;
    }

   return QWindow::keyPressEvent(event);
}

void Window3D::rotateLeft()
{
   zRot += 1.0;
}

void Window3D::rotateRight()
{
   zRot -= 1.0;
}

void Window3D::rotateUp()
{
   yRot += 1.0;
}

void Window3D::rotateDown()
{
   yRot -= 1.0;
}

bool Window3D::event(QEvent *event)
{
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
    scene.camera().loadMatrix(QVector3D(xRot, yRot, zRot), QVector3D(xMov, 0.0f, 0.0f));
    scene.render(painter);
    scene.visit([&](SceneNode & node) {
        node.render(painter);
    });
}
