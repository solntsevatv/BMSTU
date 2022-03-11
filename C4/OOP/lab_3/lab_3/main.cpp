#include "mainwindow.h"
#include "commandcontroller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    */
    CommandController commandController;
    BaseManager baseManager = commandController.getRenderManager();
    baseManager.test();
    return 0;
}
