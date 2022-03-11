#include "controller.h"
#include <QTextStream>
#include <QDebug>

Controller::Controller(QWidget *parent) : QWidget(parent)
{
    controllerState = IDLE;
    QObject::connect(this, SIGNAL(unpressBtnSignal()), this, SLOT(idleControllerSlot()));
    QObject::connect(this, &Controller::idleControllerSignal, this, &Controller::btnPressedControllerSlot);
}

void Controller::idleControllerSlot()
{
    if (controllerState == UNPRESS_BTN)
    {
        controllerState = IDLE;
        if (floorQueue.size() != 0)
        {
            emit idleControllerSignal(floorQueue.back());
        }
        else
        {
            size_t floor = 0;
            QTextStream cin(stdin);

            qDebug() << "Enter desired floor number:";
            cin >> floor;
            emit idleControllerSignal(floor);
        }
    }
    // already in idle
    else
    {
        size_t floor = 0;
        QTextStream cin(stdin);

        qDebug() << "Enter desired floor number:";
        cin >> floor;
        emit idleControllerSignal(floor);
    }
}

void Controller::btnPressedControllerSlot(size_t floor)
{
    if (controllerState == IDLE)
    {
        controllerState = BTN_PRESSED;

        floorQueue.push_front(floor);
        floor = floorQueue.back();

        emit btnPressedControllerSignal(floor);
    }
    else if (controllerState == BTN_PRESSED)
        floorQueue.push_front(floor);
}

void Controller::unpressBtnSlot()
{
    floorQueue.pop_back();
    controllerState = UNPRESS_BTN;
    emit unpressBtnSignal();
}
