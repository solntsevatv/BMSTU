#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::lift()
{
    QObject::connect(&controller, &Controller::btnPressedControllerSignal, &cabin, &Cabin::movingPrepCabinSlot);
    QObject::connect(&cabin, &Cabin::movingPrepCabinSignal, &doors, &Doors::closingDoorsSlot);
    QObject::connect(&doors, &Doors::closedDoorsSignal, &cabin, &Cabin::movingCabinSlot);
    QObject::connect(&cabin, &Cabin::arrivedCabinSignal, &cabin, &Cabin::arrivalCabinSlot);
    QObject::connect(&cabin, &Cabin::arrivalCabinSignal, &doors, &Doors::openingDoorsSlot);
    QObject::connect(&doors, &Doors::openedDoorsSignal, &cabin, &Cabin::idleCabinSlot);
    QObject::connect(&cabin, &Cabin::idleCabinSingal, &controller, &Controller::unpressBtnSlot);

    doorsClosingTimer.setSingleShot(true);
    doors.closeDoorTimer = &doorsClosingTimer;
    connect(&doorsClosingTimer, &QTimer::timeout, &doors, &Doors::closedDoorsSlot);

    doorsOpeningTimer.setSingleShot(true);
    doors.openDoorTimer = &doorsOpeningTimer;
    connect(&doorsOpeningTimer, &QTimer::timeout, &doors, &Doors::openedDoorsSlot);

    floorPassingTimer.setSingleShot(true);
    cabin.cabinTimer = &floorPassingTimer;
    connect(&floorPassingTimer, &QTimer::timeout, &cabin, &Cabin::movingCabinSlot);

    controller.idleControllerSlot();
}
