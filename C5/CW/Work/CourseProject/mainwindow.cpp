#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include "QKeyEvent"
#include "QDebug"
#include "mesh.h"
#include "math.h"
#include "QFileDialog"
#include "QFile"
#include "QMessageBox"

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

void MainWindow::init_mesh(Mesh mesh)
{
    ui->RenderScreen->clearCanvas();

    RenderParams renderParams = {
        (float)ui->RenderScreen->size().height() / ui->RenderScreen->size().width(),
        0.001f,
        1000.0f,
        15.0f, // Fov
    };
    sceneManager.SetRenderParams(renderParams);
    sceneManager.render(*ui->RenderScreen, mesh);

    resetMesh = mesh;

    // PARAM RENGERING
    ui->m_move_x->setValue(mesh.position_.x_);
    ui->m_move_y->setValue(mesh.position_.y_);
    ui->m_move_z->setValue(mesh.position_.z_);

    float rot = mesh.rotation_.x_ * 180 / M_PI;
    ui->m_rotation_x->setValue(rot);
    rot = mesh.rotation_.y_ * 180 / M_PI;
    ui->m_rotation_y->setValue(rot);
    rot = mesh.rotation_.z_ * 180 / M_PI;
    ui->m_rotation_z->setValue(rot);

    ui->m_scale_x->setValue(mesh.scale_.x_);
    ui->m_scale_y->setValue(mesh.scale_.y_);
    ui->m_scale_z->setValue(mesh.scale_.z_);

    // CAMERA PARAM
    ui->c_move_x->setValue(sceneManager.mainCamera.position_.x_);
    ui->c_move_y->setValue(sceneManager.mainCamera.position_.y_);
    ui->c_move_z->setValue(sceneManager.mainCamera.position_.z_);

    rot = sceneManager.mainCamera.rotation_.x_ * 180 / M_PI;
    ui->c_rotate_x->setValue(rot);
    rot = sceneManager.mainCamera.rotation_.y_ * 180 / M_PI;
    ui->c_rotate_y->setValue(rot);
    rot = sceneManager.mainCamera.rotation_.z_ * 180 / M_PI;
    ui->c_rotate_z->setValue(rot);

    // LIGHT PARAM
    ui->l_dir_x->setValue(sceneManager.directionalLight.direction.x_);
    ui->l_dir_y->setValue(sceneManager.directionalLight.direction.y_);
    ui->l_dir_z->setValue(sceneManager.directionalLight.direction.z_);
    ui->light_intence->setValue(sceneManager.directionalLight.power);
}

#include <chrono>
using namespace std::chrono;

void MainWindow::draw(Mesh mesh)
{
    ui->RenderScreen->clearCanvas();

    //auto start = high_resolution_clock::now();
    sceneManager.render(*ui->RenderScreen, mesh);
    //auto stop = high_resolution_clock::now();
    //auto duration = duration_cast<nanoseconds>(stop - start);
    //qDebug() << duration.count();

    // MODEL PARAM RENGERING
    ui->m_move_x->setValue(mesh.position_.x_);
    ui->m_move_y->setValue(mesh.position_.y_);
    ui->m_move_z->setValue(mesh.position_.z_);

    float rot = mesh.rotation_.x_ * 180 / M_PI;
    ui->m_rotation_x->setValue(rot);
    rot = mesh.rotation_.y_ * 180 / M_PI;
    ui->m_rotation_y->setValue(rot);
    rot = mesh.rotation_.z_ * 180 / M_PI;
    ui->m_rotation_z->setValue(rot);

    ui->m_scale_x->setValue(mesh.scale_.x_);
    ui->m_scale_y->setValue(mesh.scale_.y_);
    ui->m_scale_z->setValue(mesh.scale_.z_);

    // CAMERA PARAM
    ui->c_move_x->setValue(sceneManager.mainCamera.position_.x_);
    ui->c_move_y->setValue(sceneManager.mainCamera.position_.y_);
    ui->c_move_z->setValue(sceneManager.mainCamera.position_.z_);

    rot = sceneManager.mainCamera.rotation_.x_ * 180 / M_PI;
    ui->c_rotate_x->setValue(rot);
    rot = sceneManager.mainCamera.rotation_.y_ * 180 / M_PI;
    ui->c_rotate_y->setValue(rot);
    rot = sceneManager.mainCamera.rotation_.z_ * 180 / M_PI;
    ui->c_rotate_z->setValue(rot);

    // LIGHT PARAM
    ui->l_dir_x->setValue(sceneManager.directionalLight.direction.x_);
    ui->l_dir_y->setValue(sceneManager.directionalLight.direction.y_);
    ui->l_dir_z->setValue(sceneManager.directionalLight.direction.z_);
    ui->light_intence->setValue(sceneManager.directionalLight.power);
}

CanvasLabel* MainWindow::GetRenderScreen()
{
    return ui->RenderScreen;
}


//===========CONTROLS===========//
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (!rotating && !moving)
        return;

    QPointF mousePosCurrent = event->localPos();
    QPointF deltaMove = mousePosCurrent - mousePosPrevious;
    mousePosPrevious = mousePosCurrent;

    if (rotating)
    {
        mesh.rotate(Vector3(-deltaMove.y() / 100, -deltaMove.x() / 100, 0));
    }

    draw(mesh);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    mousePosPrevious = event->localPos();

    if (event->button() == Qt::MouseButton::LeftButton)
    {
        if (QApplication::queryKeyboardModifiers().testFlag(Qt::KeyboardModifier::ControlModifier))
            moving = true;
        else
            rotating = true;
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    moving = false;
    rotating = false;
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    float k = event->angleDelta().y() / 180.0;
    if (k < 0)
    {
        mesh.scale(Vector3(-k + 1, -k + 1, -k + 1));
    }
    else
    {
        mesh.scale(Vector3(k, k, k));
    }

    draw(mesh);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    float key_param = 0.1f;
    Vector3 tempPos;
    if(event->key() == Qt::Key_W)
    {
        tempPos = sceneManager.mainCamera.lookDir_;
        sceneManager.mainCamera.move(tempPos * key_param);
    }

    if(event->key() == Qt::Key_S)
    {
        tempPos = sceneManager.mainCamera.lookDir_;
        sceneManager.mainCamera.move(tempPos * -key_param);
    }

    if(event->key() == Qt::Key_A)
    {
        tempPos = sceneManager.mainCamera.right_;
        sceneManager.mainCamera.move(tempPos * -key_param);
    }

    if(event->key() == Qt::Key_D)
    {
        tempPos = sceneManager.mainCamera.right_;
        sceneManager.mainCamera.move(tempPos * key_param);
    }

    if(event->key() == Qt::Key_Q)
    {
        sceneManager.mainCamera.position_.y_ += key_param;
    }

    if(event->key() == Qt::Key_E)
    {
        sceneManager.mainCamera.position_.y_ -= key_param;
    }

    //ROTATION

    float rot_param = 0.1f;

    if(event->key() == Qt::Key_F)
    {
        sceneManager.mainCamera.rotate(Vector3(0, -rot_param, 0));
    }

    if(event->key() == Qt::Key_H)
    {
        sceneManager.mainCamera.rotate(Vector3(0, rot_param, 0));
    }

    if(event->key() == Qt::Key_G)
    {

        sceneManager.mainCamera.localRotation(Vector3(rot_param, 0, 0));
    }

    if(event->key() == Qt::Key_T)
    {
        sceneManager.mainCamera.localRotation(Vector3(-rot_param, 0, 0));
    }

    draw(mesh);
}

void MainWindow::on_m_next_page_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

void MainWindow::on_c_prev_page_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
}

void MainWindow::on_c_next_page_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

void MainWindow::on_l_prev_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
}

void MainWindow::on_l_next_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
}

void MainWindow::on_modelBtn_clicked()
{
    mesh = resetMesh;

    Vector3 temp;
    temp = mesh.position_ * -1;
    mesh.move(temp);
    temp.x_ = ui->m_move_x->value();
    temp.y_ = ui->m_move_y->value();
    temp.z_ = ui->m_move_z->value();
    mesh.move(temp);

    temp.x_ = ui->m_scale_x->value();
    temp.y_ = ui->m_scale_y->value();
    temp.z_ = ui->m_scale_z->value();
    mesh.scale(temp);

    temp.x_ = ui->m_rotation_x->value() * M_PI / 180.0f;
    temp.y_ = ui->m_rotation_y->value() * M_PI / 180.0f;
    temp.z_ = ui->m_rotation_z->value() * M_PI / 180.0f;
    mesh.rotate(temp);

    draw(mesh);
}

void MainWindow::on_resetModel_clicked()
{
    mesh = resetMesh;
    draw(mesh);
}



void MainWindow::on_pushButton_6_clicked()
{
    std::string path = QApplication::applicationDirPath().toStdString() + preset_paths[ui->PresetModels->currentIndex()];
    sceneManager.meshLoader_.LoadModel(mesh, path);
    resetMesh = mesh;
    draw(mesh);
}

void MainWindow::on_load_m_from_file_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Загрузить модель", "D://", tr("OBJ (*.obj)"), 0, QFileDialog::DontUseNativeDialog);

    if (sceneManager.meshLoader_.LoadModel(mesh, filename.toStdString()))
    {
        resetMesh = mesh;
        draw(mesh);
    }
    else
    {
        QMessageBox::warning(this, "Ошибка!", "Модель не была загружена!");
    }
}

// model save
void MainWindow::on_pushButton_5_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "Сохранить модель", "D://", tr("OBJ (*.obj)"), 0, QFileDialog::DontUseNativeDialog );
    if (sceneManager.meshLoader_.SaveModel(mesh, filename.toStdString()))
    {
        QMessageBox::information(this, "Сообщение", "Модель успешно сохранена!");
    }
    else
    {
        QMessageBox::warning(this, "Ошибка!", "Модель не была загружена!");
    }
}

// camera reset
void MainWindow::on_pushButton_4_clicked()
{
    sceneManager.mainCamera.position_ = {0, 0, -6};
    sceneManager.mainCamera.rotation_ = {0, 0, 0};
    sceneManager.mainCamera.up_ = {0, 1, 0};
    sceneManager.mainCamera.lookDir_ = {0, 0, 1};
    sceneManager.mainCamera.right_ = {1, 0, 0};
    sceneManager.mainCamera.localRotation_ = {0, 0, 0};
    draw(mesh);
}

void MainWindow::on_cameraBtn_clicked()
{
    sceneManager.mainCamera.position_ = {0, 0, 0};
    sceneManager.mainCamera.rotation_ = {0, 0, 0};
    sceneManager.mainCamera.up_ = {0, 1, 0};
    sceneManager.mainCamera.lookDir_ = {0, 0, 1};
    sceneManager.mainCamera.right_ = {1, 0, 0};
    sceneManager.mainCamera.localRotation_ = {0, 0, 0};

    Vector3 temp;

    temp = sceneManager.mainCamera.position_ * -1;
    sceneManager.mainCamera.move(temp);
    temp.x_ = ui->c_move_x->value();
    temp.y_ = ui->c_move_y->value();
    temp.z_ = ui->c_move_z->value();
    sceneManager.mainCamera.move(temp);


    temp.x_ = ui->c_rotate_x->value() * M_PI / 180.0f;
    temp.y_ = ui->c_rotate_y->value() * M_PI / 180.0f;
    temp.z_ = ui->c_rotate_z->value() * M_PI / 180.0f;
    sceneManager.mainCamera.rotate(temp);

    draw(mesh);
}

void MainWindow::on_lightBtn_clicked()
{
    Vector3 temp;
    temp.x_ = ui->l_dir_x->value();
    temp.y_ = ui->l_dir_y->value();
    temp.z_ = ui->l_dir_z->value();
    sceneManager.directionalLight.direction = temp;
    sceneManager.directionalLight.power = ui->light_intence->value();
    draw(mesh);
}

void MainWindow::on_renderBtn_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "Сохранить снимок", "D:\\", tr("All files (*.*)"), 0, QFileDialog::DontUseNativeDialog );
    QFile file(filename + ".png");

    if (file.open(QIODevice::WriteOnly))
    {
        GetRenderScreen()->pixmap()->save(&file, "PNG");
        QMessageBox::information(this, "Сообщение", "Снимок был успешно сохранен!");
    }
    else
    {
        QMessageBox::warning(this, "Ошибка!", "Снимок не был сохранен!");
    }
}

// create train data
void MainWindow::on_pushButton_7_clicked()
{
    /*
    QDir directory("D:/Storage/Andrew/BMSTU/BMSTU/CW/Work/Experimens/Experiment_2");
    QStringList images = directory.entryList(QStringList() << "*.jpg" << "*.JPG",QDir::Files);
    Py_Initialize();
    foreach(QString filename, images) {
        QString fname = "D:/Storage/Andrew/BMSTU/BMSTU/CW/Work/Experimens/Experiment_2/" + filename;
        PyObject* myModuleString = PyUnicode_FromString((char*)"predict");
        PyObject* myModule = PyImport_Import(myModuleString);

        PyObject* myFunction = PyObject_GetAttrString(myModule,(char*)"predict_model");
        PyObject* args = PyTuple_Pack(1, PyUnicode_FromString(fname.toStdString().c_str()));

        PyObject* myResult = PyObject_CallObject(myFunction, args);
        int result = int(PyFloat_AsDouble(myResult));

        if (result == -1)
            result = 0;
        qDebug() << filename << ":" << result;
    }
    Py_Finalize();
    */

    QString filename = QFileDialog::getOpenFileName(this, "Загрузить двумерный снимок модели", "D://", tr("(*.*)"), 0, QFileDialog::DontUseNativeDialog);

    Py_Initialize();
    PyObject* myModuleString = PyUnicode_FromString((char*)"predict");
    PyObject* myModule = PyImport_Import(myModuleString);

    PyObject* myFunction = PyObject_GetAttrString(myModule,(char*)"predict_model");
    PyObject* args = PyTuple_Pack(1, PyUnicode_FromString(filename.toStdString().c_str()));

    PyObject* myResult = PyObject_CallObject(myFunction, args);
    int result = int(PyFloat_AsDouble(myResult));

    Py_Finalize();

    if (result == -1)
        result = 0;
    std::string path = QApplication::applicationDirPath().toStdString() + preset_paths[result];
    sceneManager.meshLoader_.LoadModel(mesh, path);
    resetMesh = mesh;
    draw(mesh);

    /*
    int count = 0;
    for (int i = 0; i < 8; i++)
    {
        string path = preset_paths[i];
        sceneManager.meshLoader_.LoadModel(mesh, path);
        resetMesh = mesh;
        float rot_x = 0;
        float rot_y = 0;
        float rot_z = 0;

        for (int j = 0; j < 180; j++)
        {
            draw(mesh);
            string filename = "D:/Storage/Andrew/BMSTU/BMSTU/CW/Work/CourseProject/TrainMaterials/train_";
            string render_name = filename + std::to_string(i) + "_" + std::to_string(count) + ".jpg";
            string obj_name = filename + std::to_string(count);
            QFile file_png(QString::fromStdString(render_name));
            file_png.open(QIODevice::WriteOnly);
            GetRenderScreen()->pixmap()->save(&file_png, "JPEG");
            file_png.close();

            mesh = resetMesh;
            mesh.rotate(Vector3(rot_x * M_PI / 180.0f, rot_y * M_PI / 180.0f, rot_z * M_PI / 180.0f));
            rot_x += 1;
            rot_y += 1;
            rot_z += 1;
            count += 1;
        }

        resetMesh = mesh;
        rot_x = 0;
        rot_y = 0;
        rot_z = 0;

        for (int j = 0; j < 180; j++)
        {
            draw(mesh);
            string filename = "D:/Storage/Andrew/BMSTU/BMSTU/CW/Work/CourseProject/TrainMaterials/train_";
            string render_name = filename + std::to_string(i) + "_" + std::to_string(count) + ".jpg";
            string obj_name = filename + std::to_string(count);
            QFile file_png(QString::fromStdString(render_name));
            file_png.open(QIODevice::WriteOnly);
            GetRenderScreen()->pixmap()->save(&file_png, "JPEG");
            file_png.close();

            mesh = resetMesh;
            mesh.rotate(Vector3(rot_x * M_PI / 180.0f, rot_y * M_PI / 180.0f, rot_z * M_PI / 180.0f));
            rot_x -= 1;
            rot_y += 1;
            rot_z += 1;
            count += 1;
        }

        resetMesh = mesh;
        rot_x = 0;
        rot_y = 0;
        rot_z = 0;

        for (int j = 0; j < 180; j++)
        {
            draw(mesh);
            string filename = "D:/Storage/Andrew/BMSTU/BMSTU/CW/Work/CourseProject/TrainMaterials/train_";
            string render_name = filename + std::to_string(i) + "_" + std::to_string(count) + ".jpg";
            string obj_name = filename + std::to_string(count);
            QFile file_png(QString::fromStdString(render_name));
            file_png.open(QIODevice::WriteOnly);
            GetRenderScreen()->pixmap()->save(&file_png, "JPEG");
            file_png.close();

            mesh = resetMesh;
            mesh.rotate(Vector3(rot_x * M_PI / 180.0f, rot_y * M_PI / 180.0f, rot_z * M_PI / 180.0f));
            rot_x += 1;
            rot_y -= 1;
            rot_z += 1;
            count += 1;
        }

        resetMesh = mesh;
        rot_x = 0;
        rot_y = 0;
        rot_z = 0;

        for (int j = 0; j < 180; j++)
        {
            draw(mesh);
            string filename = "D:/Storage/Andrew/BMSTU/BMSTU/CW/Work/CourseProject/TrainMaterials/train_";
            string render_name = filename + std::to_string(i) + "_" + std::to_string(count) + ".jpg";
            string obj_name = filename + std::to_string(count);
            QFile file_png(QString::fromStdString(render_name));
            file_png.open(QIODevice::WriteOnly);
            GetRenderScreen()->pixmap()->save(&file_png, "JPEG");
            file_png.close();

            mesh = resetMesh;
            mesh.rotate(Vector3(rot_x * M_PI / 180.0f, rot_y * M_PI / 180.0f, rot_z * M_PI / 180.0f));
            rot_x += 1;
            rot_y += 1;
            rot_z -= 1;
            count += 1;
        }

        resetMesh = mesh;
        rot_x = 0;
        rot_y = 0;
        rot_z = 0;

        for (int j = 0; j < 180; j++)
        {
            draw(mesh);
            string filename = "D:/Storage/Andrew/BMSTU/BMSTU/CW/Work/CourseProject/TrainMaterials/train_";
            string render_name = filename + std::to_string(i) + "_" + std::to_string(count) + ".jpg";
            string obj_name = filename + std::to_string(count);
            QFile file_png(QString::fromStdString(render_name));
            file_png.open(QIODevice::WriteOnly);
            GetRenderScreen()->pixmap()->save(&file_png, "JPEG");
            file_png.close();

            mesh = resetMesh;
            mesh.rotate(Vector3(rot_x * M_PI / 180.0f, rot_y * M_PI / 180.0f, rot_z * M_PI / 180.0f));
            rot_x -= 1;
            rot_y -= 1;
            rot_z += 1;
            count += 1;
        }

        resetMesh = mesh;
        rot_x = 0;
        rot_y = 0;
        rot_z = 0;

        for (int j = 0; j < 180; j++)
        {
            draw(mesh);
            string filename = "D:/Storage/Andrew/BMSTU/BMSTU/CW/Work/CourseProject/TrainMaterials/train_";
            string render_name = filename + std::to_string(i) + "_" + std::to_string(count) + ".jpg";
            string obj_name = filename + std::to_string(count);
            QFile file_png(QString::fromStdString(render_name));
            file_png.open(QIODevice::WriteOnly);
            GetRenderScreen()->pixmap()->save(&file_png, "JPEG");
            file_png.close();

            mesh = resetMesh;
            mesh.rotate(Vector3(rot_x * M_PI / 180.0f, rot_y * M_PI / 180.0f, rot_z * M_PI / 180.0f));
            rot_x -= 1;
            rot_y += 1;
            rot_z -= 1;
            count += 1;
        }

        resetMesh = mesh;
        rot_x = 0;
        rot_y = 0;
        rot_z = 0;

        for (int j = 0; j < 180; j++)
        {
            draw(mesh);
            string filename = "D:/Storage/Andrew/BMSTU/BMSTU/CW/Work/CourseProject/TrainMaterials/train_";
            string render_name = filename + std::to_string(i) + "_" + std::to_string(count) + ".jpg";
            string obj_name = filename + std::to_string(count);
            QFile file_png(QString::fromStdString(render_name));
            file_png.open(QIODevice::WriteOnly);
            GetRenderScreen()->pixmap()->save(&file_png, "JPEG");
            file_png.close();

            mesh = resetMesh;
            mesh.rotate(Vector3(rot_x * M_PI / 180.0f, rot_y * M_PI / 180.0f, rot_z * M_PI / 180.0f));
            rot_x += 1;
            rot_y -= 1;
            rot_z -= 1;
            count += 1;
        }

        resetMesh = mesh;
        rot_x = 0;
        rot_y = 0;
        rot_z = 0;

        for (int j = 0; j < 180; j++)
        {
            draw(mesh);
            string filename = "D:/Storage/Andrew/BMSTU/BMSTU/CW/Work/CourseProject/TrainMaterials/train_";
            string render_name = filename + std::to_string(i) + "_" + std::to_string(count) + ".jpg";
            string obj_name = filename + std::to_string(count);
            QFile file_png(QString::fromStdString(render_name));
            file_png.open(QIODevice::WriteOnly);
            GetRenderScreen()->pixmap()->save(&file_png, "JPEG");
            file_png.close();

            mesh = resetMesh;
            mesh.rotate(Vector3(rot_x * M_PI / 180.0f, rot_y * M_PI / 180.0f, rot_z * M_PI / 180.0f));
            rot_x -= 1;
            rot_y -= 1;
            rot_z -= 1;
            count += 1;
        }
    }
    */
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}
