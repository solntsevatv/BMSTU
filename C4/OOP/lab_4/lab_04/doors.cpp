#include "doors.h"
#include <QDebug>


Doors::Doors(QWidget *parent) : QWidget(parent)
{
    doorsState = OPENED;
}

void Doors::closedDoorsSlot()
{
    doorsState = CLOSED;
    qDebug() << "Doors are closed";
    emit closedDoorsSignal();
}

void Doors::openingDoorsSlot()
{
    doorsState = OPENING;
    qDebug() << "Doors are opening";
    openDoorTimer->start(DOOR_TIME);
}

void Doors::openedDoorsSlot()
{
    doorsState = OPENED;
    qDebug() << "Doors are opened";
    emit openedDoorsSignal();
}

void Doors::closingDoorsSlot()
{
    doorsState = CLOSING;
    qDebug() << "Doors are closing";
    closeDoorTimer->start(DOOR_TIME);
}
