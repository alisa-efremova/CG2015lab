#pragma once

#include <QWindow>
#include <QOpenGLPaintDevice>
#include <QTime>
#include <memory>
#include "../gl/basescene.h"
#include "viewerinputcontroller.h"
#include "playerinputcontroller.h"

class Window3D : public QWindow
{
    Q_OBJECT
    Q_DISABLE_COPY(Window3D)

public:
    explicit Window3D(QWindow *parent = 0);
    void setFixedSize(QSize size);
    void pushScene(std::shared_ptr<BaseScene> scene);
    void popScene();

    bool event(QEvent *) override;

    bool eventFilter(QObject *target, QEvent *event);
protected:
    void exposeEvent(QExposeEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;

private slots:
    void deferRender();
    void render();
    void stopRendering();
    void initRendering();
    void updateScene(BaseScene &scene);

private:
    QTime m_updateTime;
    bool m_canRender = false;
    bool m_updatePending = false;

    std::vector<std::shared_ptr<BaseScene>> m_sceneStack;
    QOpenGLContext *m_pContext = nullptr;

    std::shared_ptr<InputController> m_activeController;
    std::shared_ptr<ViewerInputController> m_viewerController;
    std::shared_ptr<PlayerInputController> m_playerController;
};
