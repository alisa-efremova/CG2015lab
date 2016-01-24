#pragma once

#include "../gl/scenenode.h"
#include <QVector3D>

class ColoredCube : public SceneNode
{
public:
    ColoredCube(SceneNode *parent);

    void advance(int64_t msec) override;
    void render(QPainter &painter) override;

    void setScale(float scale);
    void setPosition(QVector3D position);

    float m_scale;
    QVector3D m_position;
};
