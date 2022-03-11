#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QFile>
#include "model.h"
#include "modelOperator.h"

ModelProj modelProjInit();

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ModelProj currentProj = modelProjInit();
    Action action;
    bool moving = false;
    bool rotating = false;
    QPointF mousePosPrevious;

protected:
    std::string getLoadFileName();
    std::string getSaveFileName();
    void paintEvent(QPaintEvent *event);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    void updateProjection();
    void processErrorMessage(Status errorCode);
    void printMessage(const char *messageText);

private slots:
    void on_LoadFileBtn_triggered();
    void on_SaveFileBtn_triggered();
};

#endif // MAINWINDOW_H
