#pragma once
#include <QString>
#include "nodes/loadablescenenode.h"
#include "../gl/basescene.h"
#include "coloredcube.h"

static QString COLORED_CUBE = "ColoredCube";

class SceneNodeFactory
{
public:
    static LoadableSceneNode * createNode(QString type, BaseScene * scene)
    {
        LoadableSceneNode * node;
        if (type == COLORED_CUBE)
        {
            node = new ColoredCube(scene);
        }

        return node;
    }
};

