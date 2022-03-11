#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>

class Controller : public QWidget
{
    Q_OBJECT
public:
    explicit Controller(QWidget *parent = nullptr);

    enum controllerStates
    {
        IDLE,
        BTN_PRESSED,
        UNPRESS_BTN
    };

    std::list<int> floorQueue;
    controllerStates controllerState = IDLE;

signals:
    void idleControllerSignal(size_t floor);
    void btnPressedControllerSignal(size_t floor);
    void unpressBtnSignal();

public slots:
    void idleControllerSlot();
    void btnPressedControllerSlot(size_t floor);
    void unpressBtnSlot();

};


#endif // CONTROLLER_H
