#ifndef CANVASLABEL_H
#define CANVASLABEL_H

#include <QLabel>
#include <QWidget>
#include <vector>
#include <vector3.h>

// VERIFIED

class CanvasLabel : public QLabel
{
private:
    QImage canvas;
    int lineSize = 1;

public:
    CanvasLabel();
    CanvasLabel(QWidget*& widget);
    void clearCanvas();

    QColor color = Qt::white;
    QColor bgColor = Qt::black;

public slots:
    void updateCanvas();
    void updateCanvas(QImage image);

public:
    void setPixelColor(int x, int y, QColor color);
    void setPixelColor(int x, int y, QColor color, QImage &image);
    void setPixelColorZBuffer(int x, int y, int z, QColor color);

    void DrawLine(int x_start, int y_start, int x_end, int y_end, QColor color);
    void DrawLine(int x_start, int y_start, int x_end, int y_end, QColor color, QImage &image);

    void DrawTriangle(int x_1, int y_1, int x_2, int y_2, int x_3, int y_3, QColor color);
    void DrawTriangle(Vector3 p_1, Vector3 p_2, Vector3 p_3, QColor color);

    void FillTriangle(int x_1, int y_1, int x_2, int y_2, int x_3, int y_3, QColor color);
    void FillTriangleWithZBuffer(Vector3 p_1, Vector3 p_2, Vector3 p_3, QColor color, std::vector<std::vector<float>> &z_buff);

    QColor getPixelColor(int x, int y) const;

    QImage getCanvas();
    void setCanvas(QImage newCanvas);

protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // CANVASLABEL_H
