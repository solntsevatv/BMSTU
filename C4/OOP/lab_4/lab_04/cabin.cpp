#include "cabin.h"
#include <QDebug>
#include "head.h"

Cabin::Cabin(QWidget *parent) : QWidget(parent)
{
    cabinState = IDLE;
}

void Cabin::idleCabinSlot()
{
    cabinState = IDLE;
    emit idleCabinSingal();
}

void Cabin::movingPrepCabinSlot(size_t floor)
{
    cabinState = PREP_TO_MOVE;
    destFloor = floor;
    qDebug() << "Current floor:" << currentFloor;
    qDebug() << "Desired floor:" << destFloor << Qt::endl;
    emit movingPrepCabinSignal();
}

void Cabin::movingCabinSlot()
{
    if (cabinState == PREP_TO_MOVE)
    {
        cabinState = MOVING;
        qDebug() << Qt::endl << "Lift is going...";
        cabinTimer->start(FLOOR_TIME);
    }
    else if (cabinState == MOVING)
    {
        qDebug() << "Current floor:" << currentFloor;
        if (currentFloor < destFloor)
            currentFloor++;
        if (currentFloor > destFloor)
            currentFloor--;

        if (currentFloor != destFloor)
            cabinTimer->start(FLOOR_TIME);
        else
            emit arrivedCabinSignal();
    }
}

void Cabin::arrivalCabinSlot()
{
    qDebug() << "Lift arrived at" << currentFloor << "floor" << Qt::endl;
    cabinState = ARRIVAL;
    emit arrivalCabinSignal();
}
