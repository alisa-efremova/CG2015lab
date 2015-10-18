#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QGraphicsScene>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog();

private:
    void drawInitials();
    void drawT(int xStep, int yStep);
    void drawA(int xStep, int yStep);
    void drawB(int xStep, int yStep);

    Ui::AboutDialog *ui;
    QGraphicsScene *scene;
};

#endif // ABOUTDIALOG_H
