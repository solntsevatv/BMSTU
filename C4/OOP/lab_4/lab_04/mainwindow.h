#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>

#include "head.h"
#include "doors.h"
#include "cabin.h"
#include "controller.h"

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

public:
    void lift();

protected:
    Doors doors;
    Controller controller;
    Cabin cabin;

private:
    QTimer doorsClosingTimer;
    QTimer doorsOpeningTimer;
    QTimer floorPassingTimer;
};
#endif // MAINWINDOW_H
