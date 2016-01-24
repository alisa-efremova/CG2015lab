#pragma once

#include <QJsonObject>
#include <QVector3D>
#include <memory>
#include "gl/basescene.h"

class SceneJsonParser
{
public:
    SceneJsonParser(std::shared_ptr<BaseScene> scene, QString path);
    ~SceneJsonParser() {}
    void readIntoJsonObject();
    void setCameraSettings();
    void parseObjects();
    QVector3D getVector3D(const QJsonArray & jsonArr) const;
    bool isValid() const;

private:
    std::shared_ptr<BaseScene> m_scene;
    QString m_path;
    QJsonObject m_data;
    bool m_isValid = false;
};
