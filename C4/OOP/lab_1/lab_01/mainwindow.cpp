#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QFile>
#include <Qt>

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



void MainWindow::printMessage(const char *messageText)
{
    QMessageBox::critical(
      this,
      tr("Лабораторная работа №1"),
                tr(messageText) );
}

void MainWindow::processErrorMessage(Status errorCode)
{
    if (errorCode == success)
        return;
    else if (errorCode == err_load_file_incorrect)
        printMessage("Ошибка!\n Файл загружен некорректно!");
    else if (errorCode == err_load_file_data_empty)
        printMessage("Ошибка!\n Загружаемый файл пуст!");
    else if (errorCode == err_load_file_data_incorrect)
        printMessage("Ошибка!\n В загружаемом файле содержится\n некорректная информация!");
    else if (errorCode == err_model_empty)
        printMessage("Ошибка! Модель ещё не загружена!");
    else if (errorCode == err_memory_allocation_error)
        printMessage("Ошибка! Произошло некорректное выделения памяти!");
    else if (errorCode == err_save_file_name_incorrect)
        printMessage("Ошибка! Имя файла сохранения некорректно!");
    else if (errorCode == err_unknown_action_type)
        printMessage("Ошибка! Неизвестный тип действия!");

}

std::string MainWindow::getSaveFileName()
{
    QString filter = "Text file (*.txt)";
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить модель", "D://Storage//Andrew//BMSTU//C4//OOP//lab_1", filter);
    std::string fname = fileName.toStdString();
    return fname;
}

void MainWindow::updateProjection()
{
    action.type = PROJECT;
    Status statusCode = modelOperator(currentProj, action);
    processErrorMessage(statusCode);
    update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (!rotating && !moving)
        return;

    QPointF mousePosCurrent = event->localPos();
    QPointF deltaMove = mousePosCurrent - mousePosPrevious;
    mousePosPrevious = mousePosCurrent;

    if (moving)
    {
        action.moveVector.dx = deltaMove.x();
        action.moveVector.dy = deltaMove.y();
        action.moveVector.dz = 0;
        action.type = MOVE;
    }
    else if (rotating)
    {
        action.rotationAngle.degX = -deltaMove.y() / 50.0;
        action.rotationAngle.degY = deltaMove.x() / 50.0;
        action.rotationAngle.degZ = 0;
        action.type = ROTATE;
    }

    Status statusCode = modelOperator(currentProj, action);
    processErrorMessage(statusCode);
    if (statusCode == success)
        updateProjection();
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
    action.type = SCALE;
    float k = event->angleDelta().y() / 180.0;
    if (k < 0)
    {
        action.scaleRatio.ratioX = -k + 1;
        action.scaleRatio.ratioY = -k + 1;
        action.scaleRatio.ratioZ = -k + 1;
    }
    else
    {
        action.scaleRatio.ratioX = k;
        action.scaleRatio.ratioY = k;
        action.scaleRatio.ratioZ = k;
    }

    Status statusCode = modelOperator(currentProj, action);
    processErrorMessage(statusCode);
    if (statusCode == success)
        updateProjection();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen linePen(Qt::black);
    linePen.setWidth(3);
    QPen pointPen(Qt::black);
    pointPen.setWidth(9);

    painter.eraseRect(0, 0, 2000, 2000);

    painter.setPen(linePen);
    for (int i = 0; i < currentProj.lines.lineCount; i++)
    {
        painter.drawLine(
        currentProj.canvasPoints.canvasPointArr[currentProj.lines.lineArr[i].start].x,\
        currentProj.canvasPoints.canvasPointArr[currentProj.lines.lineArr[i].start].y,\
        currentProj.canvasPoints.canvasPointArr[currentProj.lines.lineArr[i].end].x,\
        currentProj.canvasPoints.canvasPointArr[currentProj.lines.lineArr[i].end].y\
                         );
    }

    painter.setPen(pointPen);
    for (int i = 0; i < currentProj.canvasPoints.pointCount; i++)
        painter.drawPoint(currentProj.canvasPoints.canvasPointArr[i].x, currentProj.canvasPoints.canvasPointArr[i].y);
}

std::string MainWindow::getLoadFileName()
{
    QString filter = "Text file (*.txt)";
    QString fileName = QFileDialog::getOpenFileName(this, "Загрузить модель", "D://Storage//Andrew//BMSTU//C4//OOP//lab_1", filter);
    std::string fname = fileName.toStdString();
    return fname;
}

void MainWindow::on_LoadFileBtn_triggered()
{
    std::string filename = MainWindow::getLoadFileName();
    char *fname = (char *)malloc(filename.size() + 1);
    memcpy(fname, filename.c_str(), filename.size() + 1);
    action.filename = fname;
    action.type = LOAD;
    Status statusCode = modelOperator(currentProj, action);
    processErrorMessage(statusCode);
    if (statusCode == success)
        updateProjection();
    free(fname);
}

void MainWindow::on_SaveFileBtn_triggered()
{
    action.type = SAVE;
    std::string filename = MainWindow::getSaveFileName();
    char *fname = (char *)malloc(filename.size() + 1);
    memcpy(fname, filename.c_str(), filename.size() + 1);
    action.filename = fname;
    Status statusCode = modelOperator(currentProj, action);
    processErrorMessage(statusCode);
    free(fname);
}
