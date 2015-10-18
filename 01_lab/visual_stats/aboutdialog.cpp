#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setStyleSheet("border: 0");
    drawInitials();
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::drawInitials()
{
    const int xOffset = 0;
    const int yOffset = 0;
    const int letterLen = 90;

    drawT(xOffset, yOffset);
    drawA(xOffset + letterLen, yOffset);
    drawB(xOffset + letterLen * 2, yOffset);
}

void AboutDialog::drawT(int xStep, int yStep)
{
    QPainterPath pathT;
    pathT.moveTo(xStep, yStep);
    pathT.lineTo(80 + xStep, yStep);
    pathT.lineTo(80 + xStep, 15 + yStep);
    pathT.lineTo(50 + xStep, 15 + yStep);
    pathT.lineTo(50 + xStep, 80 + yStep);
    pathT.lineTo(30 + xStep, 80 + yStep);
    pathT.lineTo(30 + xStep, 15 + yStep);
    pathT.lineTo(xStep, 15 + yStep);
    pathT.closeSubpath();

    scene->addPath(pathT, QPen(QColor::fromRgb(0, 179, 255)), QBrush(QColor::fromRgb(0, 179, 255)));
}

void AboutDialog::drawA(int xStep, int yStep)
{
    QPainterPath pathA;
    pathA.moveTo(30 + xStep, yStep);
    pathA.lineTo(50 + xStep, yStep);
    pathA.lineTo(80 + xStep, 80 + yStep);
    pathA.lineTo(60 + xStep, 80 + yStep);
    pathA.lineTo(53 + xStep, 60 + yStep);
    pathA.lineTo(27 + xStep, 60 + yStep);
    pathA.lineTo(20 + xStep, 80 + yStep);
    pathA.lineTo(xStep, 80 + yStep);
    pathA.closeSubpath();

    pathA.moveTo(40 + xStep, 20 + yStep);
    pathA.lineTo(32 + xStep, 45 + yStep);
    pathA.lineTo(48 + xStep, 45 + yStep);
    pathA.closeSubpath();

    pathA.setFillRule(Qt::OddEvenFill);

    scene->addPath(pathA, QPen(QColor::fromRgb(0, 255, 85)), QBrush(QColor::fromRgb(0, 255, 85)));
}

void AboutDialog::drawB(int xStep, int yStep)
{
    QPainterPath pathB;
    pathB.moveTo(xStep, yStep);
    pathB.lineTo(40 + xStep, yStep);
    pathB.arcTo(20 + xStep, yStep, 40, 40, 90, -130);
    pathB.arcTo(20 + xStep, 30 + yStep, 50, 50, 65, -155);
    pathB.lineTo(xStep, 80 + yStep);
    pathB.closeSubpath();

    pathB.moveTo(20 + xStep, 15 + yStep);
    pathB.lineTo(32.5 + xStep, 15 + yStep);
    pathB.arcTo(25 + xStep, 15 + yStep, 15, 15, 90, -180);
    pathB.lineTo(20 + xStep, 30 + yStep);
    pathB.closeSubpath();

    pathB.moveTo(20 + xStep, 45 + yStep);
    pathB.lineTo(40 + xStep, 45 + yStep);
    pathB.arcTo(30 + xStep, 45 + yStep, 20, 20, 90, -180);
    pathB.lineTo(20 + xStep, 65 + yStep);
    pathB.closeSubpath();

    pathB.setFillRule(Qt::OddEvenFill);

    scene->addPath(pathB, QPen(QColor::fromRgb(0, 43, 255)), QBrush(QColor::fromRgb(0, 43, 255)));
}
