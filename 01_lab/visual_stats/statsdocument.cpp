#include "statsdocument.h"
#include "statskeyvaluemodel.h"
#include "istatsmodelprovider.h"
#include "statsserializer.h"
#include <QWidget>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>

namespace
{
const QLatin1String FILE_FORMAT_FILTER("*.json");
}

StatsDocument::StatsDocument(QWidget *parent, IStatsModelProvider &provider)
    : QObject(parent)
    , m_provider(provider)
{

}

void StatsDocument::createNew()
{
    m_path.clear();
    StatsKeyValueModel model;
    m_provider.setStatsModel(model);
    m_provider.setIsSaved();
}

bool StatsDocument::open()
{
    QString openPath = selectOpenPath();
    if (openPath.isEmpty())
    {
        return false;
    }
    m_path = openPath;

    StatsKeyValueModel model;
    StatsSerializer serializer(m_path);
    if (!serializer.load(model))
    {
        return false;
    }

    m_provider.setStatsModel(model);
    m_provider.setIsSaved();
    return true;
}

bool StatsDocument::save()
{
    if (m_path.isEmpty())
    {
        QString savePath = selectSavePath();
        if (savePath.isEmpty())
        {
            return false;
        }
        m_path = savePath;
    }

    StatsSerializer serializer(m_path);
    if (serializer.save(m_provider.statsModel()))
    {
        m_provider.setIsSaved();
        //QMessageBox::about(this, tr("Success"), tr("Table is successfully saved"));
    }
}

bool StatsDocument::saveAs()
{
    QString savePath = selectSavePath();
    if (savePath.isEmpty())
    {
        return false;
    }
    m_path = savePath;

    StatsSerializer serializer(m_path);
    //return serializer.save(m_provider.statsModel());
    if (serializer.save(m_provider.statsModel()))
    {
        m_provider.setIsSaved();
        //QMessageBox::about(this, tr("Success"), tr("Table is successfully saved"));
    }
}

QString StatsDocument::selectSavePath() const
{
    QString fromDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    auto parentWindow = qobject_cast<QWidget *>(parent());
    return QFileDialog::getSaveFileName(parentWindow, QString(), fromDir, FILE_FORMAT_FILTER);
}

QString StatsDocument::selectOpenPath() const
{
    QString fromDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    auto parentWindow = qobject_cast<QWidget *>(parent());
    return QFileDialog::getOpenFileName(parentWindow, QString(), fromDir, FILE_FORMAT_FILTER);
}
