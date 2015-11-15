#pragma once

#include <QWindow>
#include <QOpenGLPaintDevice>
#include <QTime>
#include <memory>
#include "../gl/basescene.h"

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

protected:
    void exposeEvent(QExposeEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;

    virtual void keyPressEvent(QKeyEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

private slots:
    void deferRender();
    void render();
    void stopRendering();
    void initRendering();
    void updateScene(BaseScene &scene);

    void rotateLeft();
    void rotateRight();
    void rotateUp();
    void rotateDown();

private:
    QTime m_updateTime;
    bool m_canRender = false;
    bool m_updatePending = false;

    std::vector<std::shared_ptr<BaseScene>> m_sceneStack;
    QOpenGLContext *m_pContext = nullptr;

    bool isMousePressed = false;
    QPoint ptrMousePosition;

    float xRot = 0;
    float yRot = 0;
    float zRot = 0;
    float xMov = 0;
};
