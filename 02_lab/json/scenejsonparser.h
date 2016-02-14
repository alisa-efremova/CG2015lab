#pragma once

#include <memory>
#include "gl/basescene.h"
#include "jsonhelper.h"

class SceneJsonParser
{
public:
    SceneJsonParser(std::shared_ptr<BaseScene> scene, QString path);
    ~SceneJsonParser() {}
    void readIntoJsonObject();
    void setCameraSettings();
    void parseObjects();
    bool isValid() const;

private:
    std::shared_ptr<BaseScene> m_scene;
    QString m_path;
    QJsonObject m_data;
    bool m_isValid = false;
};
