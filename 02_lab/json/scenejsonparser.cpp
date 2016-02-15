#include "jsonkey.h"
#include "scenejsonparser.h"
#include "nodes/scenenodefactory.h"
#include "nodes/loadablescenenode.h"
#include <QCoreApplication>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>

SceneJsonParser::SceneJsonParser(std::shared_ptr<BaseScene> scene, QString path)
    : m_scene(scene),
      m_path(path)
{
}

void SceneJsonParser::readIntoJsonObject()
{
    QFile json(m_path);
    if (json.open(QIODevice::ReadOnly))
    {
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(json.readAll(), &parseError);
        if (parseError.error == QJsonParseError::NoError && jsonDoc.isObject())
        {
            m_data = jsonDoc.object();
        }
        else
        {
            qDebug() << parseError.errorString();
        }
    }
    else
    {
        qDebug() << "Cannot open file. error code: " << json.error();
    }
}

void SceneJsonParser::setCameraSettings()
{
    auto camera = m_data[JsonKey::CAMERA].toObject();
    auto eye    = JsonHelper::getVector3D(camera[JsonKey::EYE].toArray());
    auto center = JsonHelper::getVector3D(camera[JsonKey::CENTER].toArray());
    auto up     = JsonHelper::getVector3D(camera[JsonKey::UP].toArray());
    m_scene->camera().lookAt(eye, center, up);
}

void SceneJsonParser::parseObjects()
{
    auto objects = m_data[JsonKey::OBJECTS].toArray();
    foreach (QJsonValue val, objects)
    {
        auto object = val.toObject();
        auto className = object[JsonKey::CLASS].toString();
        LoadableSceneNode * node = SceneNodeFactory::createNode(className, m_scene.get());
        m_isValid = node->loadFromJson(object);
    }
}

bool SceneJsonParser::isValid() const
{
    return m_isValid;
}




