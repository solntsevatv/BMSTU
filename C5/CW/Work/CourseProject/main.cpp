#include "mainwindow.h"

#include <QApplication>
#include <thread>
#include <time.h>
#include <filesystem>

#include "mesh.h"
#include "QDebug"
#include "QDir"
#include "QFile"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    string path = QApplication::applicationDirPath().toStdString() + "/PresetModels/Cube.obj";
    w.sceneManager.meshLoader_.LoadModel(w.mesh, path);

    w.sceneManager.mainCamera.move(Vector3(0, 0, -6.0));

    w.setWindowState(Qt::WindowMaximized);
    w.show();
    w.init_mesh(w.mesh);

    return a.exec();
}
