#pragma once

#include <QJsonArray>
#include <QJsonObject>
#include <QVector3D>

class JsonHelper
{
public:
    static QVector3D getVector3D(const QJsonArray & jsonArr)
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
};

