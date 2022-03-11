#ifndef DOORS_H
#define DOORS_H

#include <QObject>
#include <QTimer>
#include <head.h>
#include <QWidget>
#include <QTextStream>
#include <iostream>
#include <QCoreApplication>

class Doors : public QWidget
{
    Q_OBJECT
public:
    explicit Doors(QWidget *parent = nullptr);

    enum states
    {
        CLOSED,
        OPENING,
        OPENED,
        CLOSING
    };

    states doorsState = OPENED;

    QTimer *openDoorTimer;
    QTimer *closeDoorTimer;

signals:
    void closedDoorsSignal();
    void openingDoorsSignal();
    void openedDoorsSignal();
    void closingDoorsSignal();

public slots:
    void closedDoorsSlot();
    void openingDoorsSlot();
    void openedDoorsSlot();
    void closingDoorsSlot();

};

#endif // DOORS_H

