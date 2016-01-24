#include "scenejsonparser.h"
#include "nodes/coloredcube.h"
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonArray>
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
        QJsonParseError  parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(json.readAll(), &parseError);
        if (parseError.error == QJsonParseError::NoError)
        {
            if (jsonDoc.isObject())
            {
                m_data = jsonDoc.object();
                auto obj = jsonDoc.object();
                auto camera = obj["camera"].toObject();
                auto eye = camera["eye"].toArray();
            }
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
    auto camera = m_data["camera"].toObject();
    auto eye = getVector3D(camera["eye"].toArray());
    auto center = getVector3D(camera["center"].toArray());
    auto up = getVector3D(camera["up"].toArray());
    m_scene->camera().lookAt(eye, center, up);
}

void SceneJsonParser::parseObjects()
{
    auto objects = m_data["objects"].toArray();
    foreach (QJsonValue val, objects)
    {
        auto object = val.toObject();
        auto className = object["class"].toString();
        auto scale = object["scale"].toDouble();
        auto position = getVector3D(object["position"].toArray());
qDebug() << className;
        if (className == "ColoredCube")
        {
            auto cube = new ColoredCube(m_scene.get());
            cube->setPosition(position);
            cube->setScale(scale);
            m_isValid = true;
        }
    }
}

QVector3D SceneJsonParser::getVector3D(const QJsonArray & jsonArr) const
{
    QVector3D vec(0, 0, 0);
    if (jsonArr.size() == 3)
    {
        float arr[3];
        int i = 0;
        foreach(QJsonValue val, jsonArr)
        {
            arr[i] = val.toDouble();
            i++;
        }
        vec = QVector3D(arr[0], arr[1], arr[2]);
    }
    return vec;
}

bool SceneJsonParser::isValid() const
{
    return m_isValid;
}




