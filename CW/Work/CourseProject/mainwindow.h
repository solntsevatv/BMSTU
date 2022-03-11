#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Python.h"
#include <QMainWindow>
#include "scenemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool moving = false;
    bool rotating = false;
    QPointF mousePosPrevious;

    void init_mesh(Mesh mesh);
    void draw(Mesh mesh);
    SceneManager sceneManager;
    CanvasLabel* GetRenderScreen();

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    void keyPressEvent(QKeyEvent *event);

    //DEBUG
    Mesh mesh;
    Mesh resetMesh;

    string preset_paths[8] = {
        "/PresetModels/Cube.obj",
        "/PresetModels/Tetraedr.obj",
        "/PresetModels/Pyramid.obj",
        "/PresetModels/Sphere.obj",
        "/PresetModels/IsoSphere.obj",
        "/PresetModels/Torus.obj",
        "/PresetModels/Cylinder.obj",
        "/PresetModels/Cone.obj"
    };

private slots:

    void on_m_next_page_clicked();

    void on_c_prev_page_clicked();

    void on_c_next_page_clicked();

    void on_l_prev_btn_clicked();

    void on_l_next_btn_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_modelBtn_clicked();

    void on_resetModel_clicked();

    void on_pushButton_6_clicked();

    void on_load_m_from_file_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_cameraBtn_clicked();

    void on_lightBtn_clicked();

    void on_renderBtn_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
