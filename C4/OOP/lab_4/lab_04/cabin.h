#ifndef CABIN_H
#define CABIN_H

#include <QObject>
#include <QWidget>
#include <QTimer>

class Cabin : public QWidget
{
    Q_OBJECT
public:
    explicit Cabin(QWidget *parent = nullptr);

    enum cabinStates
    {
        IDLE,
        PREP_TO_MOVE,
        MOVING,
        ARRIVAL
    };

    cabinStates cabinState = IDLE;
    size_t currentFloor = 0; // нулевой этаж
    size_t destFloor = 0;

    QTimer *cabinTimer;

signals:
    void idleCabinSingal();
    void movingPrepCabinSignal();
    void movingCabinSignal();
    void arrivalCabinSignal();
    void arrivedCabinSignal();

public slots:
    void idleCabinSlot();
    void movingPrepCabinSlot(size_t floor);
    void movingCabinSlot();
    void arrivalCabinSlot();

};

#endif // CABIN_H
