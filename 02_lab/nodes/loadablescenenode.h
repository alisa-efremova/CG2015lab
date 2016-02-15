#pragma once
#include "gl/scenenode.h"

class LoadableSceneNode : public SceneNode
{
public:
    LoadableSceneNode(SceneNode *parent)
        : SceneNode(parent)
    {}

    ~LoadableSceneNode() {}

    virtual bool loadFromJson(QJsonObject & object) = 0;
};
