#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QString>
#include <memory>
#include <QAbstractItemModel>

namespace Ui {
class MainWindow;
}
class StatsTableModel;
class StatsDocument;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void drawPieChart();
    void on_newDocument_triggered();
    void on_saveDocument_triggered();
    void on_openDocument_triggered();
    void on_saveDocumentAs_triggered();
    void on_showTable_triggered();
    void on_showDiagram_triggered();

    void on_actionAbout_triggered();

    void on_actionInsertRow_triggered();
    void onRowReady(QString text, int value);

    void on_actionDeleteRow_triggered();

    void on_tableUpdated();
    void on_valueUpdated(const QModelIndex & topLeft, const QModelIndex & bottomRight);
    //void on_tableUpdated(const QList<QPersistentModelIndex> &parents = QList<QPersistentModelIndex>(), QAbstractItemModel::LayoutChangeHint hint = QAbstractItemModel::NoLayoutChangeHint);
   // void on_tableUpdated(const QList<QPersistentModelIndex> &parents, QAbstractItemModel::LayoutChangeHint hint);

private:
    bool checkUnsavedChanges();
    void addPieToChart(QRectF & rect, qreal startAngle, qreal sweepLength, const QColor & color);

    Ui::MainWindow *m_ui;
    std::shared_ptr<StatsTableModel> m_tableModel;
    std::unique_ptr<StatsDocument> m_document;
    QGraphicsScene *scene;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *event);
};
