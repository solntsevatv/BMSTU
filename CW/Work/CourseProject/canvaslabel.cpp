#include "canvaslabel.h"
#include "math.h"
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QResizeEvent>

#define EPS 0.0001

CanvasLabel::CanvasLabel()
{
    QPixmap canvasPix = QPixmap(this->size());
    canvasPix.fill(bgColor);
    canvas = canvasPix.toImage();
    updateCanvas();
}

CanvasLabel::CanvasLabel(QWidget *&widget)
{
    QPixmap canvasPix = QPixmap(this->size());
    canvasPix.fill(bgColor);
    canvas = canvasPix.toImage();
    updateCanvas();
}

void CanvasLabel::clearCanvas()
{
    canvas.fill(bgColor);
    updateCanvas();
}

void CanvasLabel::resizeEvent(QResizeEvent *event)
{
    canvas = canvas.scaled(this->size());
    updateCanvas();
}

void CanvasLabel::setPixelColor(int x, int y, QColor color)
{
    if (x > this->size().width()/2)
        x = this->size().width()/2 - 1;
    if (x < -this->size().width()/2)
        x = -this->size().width()/2 + 1;

    if (y > this->size().height()/2)
        y = this->size().height()/2 - 1;
    if (y < -this->size().height()/2)
        y = -this->size().height()/2 + 1;

    canvas.setPixelColor(x + this->size().width()/2, this->size().height()/2 - y , color);
}

void CanvasLabel::setPixelColor(int x, int y, QColor color, QImage &image)
{
    if (x > this->size().width()/2)
        x = this->size().width()/2 - 1;
    if (x < -this->size().width()/2)
        x = -this->size().width()/2 + 1;

    if (y > this->size().height()/2)
        y = this->size().height()/2 - 1;
    if (y < -this->size().height()/2)
        y = -this->size().height()/2 + 1;

    image.setPixelColor(x + this->size().width()/2, this->size().height()/2 - y , color);
}

void CanvasLabel::DrawLine(int x_start, int y_start, int x_end, int y_end, QColor color)
{
    int delta_x = abs(x_end - x_start);
    int delta_y = abs(y_end - y_start);

    if (delta_x > delta_y)
    {
        if (x_end - x_start < 0)
        {
            int temp = x_start;
            x_start = x_end;
            x_end = temp;

            temp = y_start;
            y_start = y_end;
            y_end = temp;
        }

        int error = 0;
        int derror = delta_y + 1;
        int y = y_start;
        int diry = y_end - y_start;

        if (diry > 0)
            diry = 1;
        if (diry < 0)
            diry =  -1;

        for (int x = x_start; x <= x_end; x++)
        {
            setPixelColor(x, y, color);
            error += derror;
            if (error >= delta_x + 1)
            {
                y += diry;
                error -= delta_x + 1;
            }
        }
    }

    if (delta_x < delta_y)
    {
        if (y_end - y_start < 0)
        {
            int temp = x_start;
            x_start = x_end;
            x_end = temp;

            temp = y_start;
            y_start = y_end;
            y_end = temp;
        }

        int error = 0;
        int derror = delta_x + 1;
        int x = x_start;
        int dirx = x_end - x_start;

        if (dirx > 0)
            dirx = 1;
        if (dirx < 0)
            dirx =  -1;

        for (int y = y_start; y <= y_end; y++)
        {
            setPixelColor(x, y, color);
            error += derror;
            if (error >= delta_y + 1)
            {
                x += dirx;
                error -= delta_y + 1;
            }
        }
    }

    if (delta_x == delta_y)
    {
        if (x_end - x_start < 0)
        {
            int temp = x_start;
            x_start = x_end;
            x_end = temp;

            temp = y_start;
            y_start = y_end;
            y_end = temp;
        }

        int y = y_start;
        int diry = y_end - y_start;

        if (diry > 0)
            diry = 1;
        if (diry < 0)
            diry =  -1;

        for (int x = x_start; x < x_end; x++)
        {
            setPixelColor(x, y, color);
            y += diry;
        }
    }
    updateCanvas();
}

void CanvasLabel::DrawLine(int x_start, int y_start, int x_end, int y_end, QColor color, QImage &image)
{
    int delta_x = abs(x_end - x_start);
    int delta_y = abs(y_end - y_start);

    if (delta_x > delta_y)
    {
        if (x_end - x_start < 0)
        {
            int temp = x_start;
            x_start = x_end;
            x_end = temp;

            temp = y_start;
            y_start = y_end;
            y_end = temp;
        }

        int error = 0;
        int derror = delta_y + 1;
        int y = y_start;
        int diry = y_end - y_start;

        if (diry > 0)
            diry = 1;
        if (diry < 0)
            diry =  -1;

        for (int x = x_start; x <= x_end; x++)
        {
            setPixelColor(x, y, color);
            error += derror;
            if (error >= delta_x + 1)
            {
                y += diry;
                error -= delta_x + 1;
            }
        }
    }

    if (delta_x < delta_y)
    {
        if (y_end - y_start < 0)
        {
            int temp = x_start;
            x_start = x_end;
            x_end = temp;

            temp = y_start;
            y_start = y_end;
            y_end = temp;
        }

        int error = 0;
        int derror = delta_x + 1;
        int x = x_start;
        int dirx = x_end - x_start;

        if (dirx > 0)
            dirx = 1;
        if (dirx < 0)
            dirx =  -1;

        for (int y = y_start; y <= y_end; y++)
        {
            setPixelColor(x, y, color);
            error += derror;
            if (error >= delta_y + 1)
            {
                x += dirx;
                error -= delta_y + 1;
            }
        }
    }

    if (delta_x == delta_y)
    {
        int y = y_start;
        int diry = y_end - y_start;

        if (diry > 0)
            diry = 1;
        if (diry < 0)
            diry =  -1;

        for (int x = x_start; x < x_end; x++)
        {
            setPixelColor(x, y, color, image);
            y += diry;
        }
    }
    updateCanvas(image);
}

void CanvasLabel::DrawTriangle(Vector3 p_1, Vector3 p_2, Vector3 p_3, QColor color)
{
    int x_1 = p_1.x_;
    int x_2 = p_2.x_;
    int x_3 = p_3.x_;

    int y_1 = p_1.y_;
    int y_2 = p_2.y_;
    int y_3 = p_3.y_;

    DrawLine(x_1, y_1, x_2, y_2, color);
    DrawLine(x_2, y_2, x_3, y_3, color);
    DrawLine(x_3, y_3, x_1, y_1, color);
}

void CanvasLabel::DrawTriangle(int x_1, int y_1, int x_2, int y_2, int x_3, int y_3, QColor color)
{
    DrawLine(x_1, y_1, x_2, y_2, color);
    DrawLine(x_2, y_2, x_3, y_3, color);
    DrawLine(x_3, y_3, x_1, y_1, color);
}

int maxIndex(int a, int b, int c)
{
    if (a >= b && a >= c)
        return 0;
    if (b >= a && b >= c)
        return 1;
    if (c >= a && c >= b)
        return 2;
    return 0;
}

int minIndex(int a, int b, int c)
{
    if (a < b && a < c)
        return 0;
    if (b < a && b < c)
        return 1;
    if (c < a && c < b)
        return 2;
    return 0;
}

struct Vector
{
    float x;
    float y;
};

float TestPoint(int x_p, int y_p, int x_s, int y_s, int x_e, int y_e)
{
    Vector a;
    a.x = x_p - x_s;
    a.y = y_p - y_s;

    Vector b;
    b.x = x_p - x_e;
    b.y = y_p - y_e;

    return a.x * b.y - a.y * b.x;
}

void CanvasLabel::FillTriangle(int x_1, int y_1, int x_2, int y_2, int x_3, int y_3, QColor color)
{
    int x_max = x_1;
    if (x_max < x_2)
        x_max = x_2;
    if (x_max < x_3)
        x_max = x_3;

    int x_min = x_1;
    if (x_min > x_2)
        x_min = x_2;
    if (x_min > x_3)
        x_min = x_3;

    int y_max = y_1;
    if (y_max < y_2)
        y_max = y_2;
    if (y_max < y_3)
        y_max = y_3;

    int y_min = y_1;
    if (y_min > y_2)
        y_min = y_2;
    if (y_min > y_3)
        y_min = y_3;

    for (int y = y_min; y < y_max; y++)
    {
        for (int x = x_min; x < x_max; x++)
        {
            float e21 = TestPoint(x, y, x_2, y_2, x_1, y_1);
            float e32 = TestPoint(x, y, x_3, y_3, x_2, y_2);
            float e13 = TestPoint(x, y, x_1, y_1, x_3, y_3);

            if (e21 >= 0.0f && e32 >= 0.0f && e13 >= 0.0f)
            {
                setPixelColor(x, y, color);
            }
        }
    }
}

int get_max(int a, int b, int c)
{
    int max = a;
    if (max < b)
        max = b;
    if (max < c)
        max = c;
    return max;
}

int get_min(int a, int b, int c)
{
    int max = a;
    if (max > b)
        max = b;
    if (max > c)
        max = c;
    return max;
}


void CanvasLabel::FillTriangleWithZBuffer(Vector3 p_1, Vector3 p_2, Vector3 p_3, QColor color, std::vector<std::vector<float>> &z_buff)
{
    int x_max = get_max(p_1.x_, p_2.x_, p_3.x_);
    int y_max = get_max(p_1.y_, p_2.y_, p_3.y_);

    int x_min = get_min(p_1.x_, p_2.x_, p_3.x_);
    int y_min = get_min(p_1.y_, p_2.y_, p_3.y_);

    Vector3 temp_p_1;
    Vector3 temp_p_2;
    Vector3 temp_p_3;

    temp_p_1.y_ = y_max;
    if (int(temp_p_1.y_) == int(p_1.y_))
        temp_p_1 = p_1;
    if (int(temp_p_1.y_) == int(p_2.y_))
        temp_p_1 = p_2;
    if (int(temp_p_1.y_) == int(p_3.y_))
        temp_p_1 = p_3;

    temp_p_3.y_ = y_min;
    if (int(temp_p_3.y_) == int(p_1.y_) && int(temp_p_1.y_) != int(p_1.y_))
        temp_p_3 = p_1;
    if (int(temp_p_3.y_) == int(p_2.y_) && int(temp_p_1.y_) != int(p_2.y_))
        temp_p_3 = p_2;
    if (int(temp_p_3.y_) == int(p_3.y_) && int(temp_p_1.y_) != int(p_3.y_))
        temp_p_3 = p_3;

    if ((temp_p_1 == p_1 && temp_p_3 == p_2) || (temp_p_1 == p_2 && temp_p_3 == p_1))
        temp_p_2 = p_3;
    if ((temp_p_1 == p_1 && temp_p_3 == p_3) || (temp_p_1 == p_3 && temp_p_3 == p_1))
        temp_p_2 = p_2;
    if ((temp_p_1 == p_2 && temp_p_3 == p_3) || (temp_p_1 == p_3 && temp_p_3 == p_2))
        temp_p_2 = p_1;

    for (int y = y_min; y < y_max; y++)
    {
        for (int x = x_min; x < x_max; x++)
        {
            if (abs(x) < this->size().width()/2 && abs(y) < this->size().height()/2)
            {
                float e21 = TestPoint(x, y, p_2.x_, p_2.y_, p_1.x_, p_1.y_);
                float e32 = TestPoint(x, y, p_3.x_, p_3.y_, p_2.x_, p_2.y_);
                float e13 = TestPoint(x, y, p_1.x_, p_1.y_, p_3.x_, p_3.y_);

                if (e21 >= 0.0f && e32 >= 0.0f && e13 >= 0.0f)
                {
                    if (y == y_max || y == y_min)
                    {
                        if ((y == int(temp_p_2.y_) && (y == int(temp_p_1.y_))))
                        {
                            float z = temp_p_1.z_ + (temp_p_2.z_ - temp_p_1.z_) * ((x - temp_p_1.x_)/(temp_p_2.x_ - temp_p_1.x_));
                            if (z < z_buff[this->size().height()/2 - y][x + this->size().width()/2])
                            {
                                setPixelColor(x, y, color);
                                z_buff[this->size().height()/2 - y][x + this->size().width()/2] = z;
                            }
                            //setPixelColor(x, y, color);
                        }
                        else if ((y == int(temp_p_2.y_) && (y == int(temp_p_3.y_))))
                        {
                            float z = temp_p_3.z_ + (temp_p_2.z_ - temp_p_3.z_) * ((x - temp_p_3.x_)/(temp_p_2.x_ - temp_p_3.x_));
                            if (z < z_buff[this->size().height()/2 - y][x + this->size().width()/2])
                            {
                                setPixelColor(x, y, color);
                                z_buff[this->size().height()/2 - y][x + this->size().width()/2] = z;
                            }
                            //setPixelColor(x, y, color);
                        }
                        else if (y == int(temp_p_1.y_))
                        {
                            float z = temp_p_1.z_;
                            if (z < z_buff[this->size().height()/2 - y][x + this->size().width()/2])
                            {
                                setPixelColor(x, y, color);
                                z_buff[this->size().height()/2 - y][x + this->size().width()/2] = z;
                            }
                            //setPixelColor(x, y, color);
                        }
                        else if (y == int(temp_p_3.y_))
                        {
                            float z = temp_p_3.z_;
                            if (z < z_buff[this->size().height()/2 - y][x + this->size().width()/2])
                            {
                                setPixelColor(x, y, color);
                                z_buff[this->size().height()/2 - y][x + this->size().width()/2] = z;
                            }
                            //setPixelColor(x, y, color);
                        }
                    }
                    else if (y >= int(temp_p_2.y_))
                    {
                        int x_a = temp_p_1.x_ + (temp_p_2.x_ - temp_p_1.x_)*((y - temp_p_1.y_)/(temp_p_2.y_ - temp_p_1.y_));
                        int x_b = temp_p_1.x_ + (temp_p_3.x_ - temp_p_1.x_)*((y - temp_p_1.y_)/(temp_p_3.y_ - temp_p_1.y_));
                        float z_a = temp_p_1.z_ + (temp_p_2.z_ - temp_p_1.z_)*((y - temp_p_1.y_)/(temp_p_2.y_ - temp_p_1.y_));
                        float z_b = temp_p_1.z_ + (temp_p_3.z_ - temp_p_1.z_)*((y - temp_p_1.y_)/(temp_p_3.y_ - temp_p_1.y_));

                        if (x_a != x_b)
                        {
                            float z = z_a + (z_b - z_a)*((x - x_a)/(x_b - x_a));

                            if (z < z_buff[this->size().height()/2 - y][x + this->size().width()/2])
                            {
                                setPixelColor(x, y, color);
                                z_buff[this->size().height()/2 - y][x + this->size().width()/2] = z;
                            }
                        }
                        else
                        {
                            if (z_a < z_buff[this->size().height()/2 - y][x + this->size().width()/2])
                            {
                                setPixelColor(x, y, color);
                                z_buff[this->size().height()/2 - y][x + this->size().width()/2] = z_a;
                            }
                        }
                    }
                    else if (y < int(temp_p_2.y_))
                    {
                        int x_a = temp_p_2.x_ + (temp_p_3.x_ - temp_p_2.x_)*((y - temp_p_2.y_)/(temp_p_3.y_ - temp_p_2.y_));
                        int x_b = temp_p_1.x_ + (temp_p_3.x_ - temp_p_1.x_)*((y - temp_p_1.y_)/(temp_p_3.y_ - temp_p_1.y_));
                        float z_a = temp_p_2.z_ + (temp_p_3.z_ - temp_p_2.z_)*((y - temp_p_2.y_)/(temp_p_3.y_ - temp_p_2.y_));
                        float z_b = temp_p_1.z_ + (temp_p_3.z_ - temp_p_1.z_)*((y - temp_p_1.y_)/(temp_p_3.y_ - temp_p_1.y_));

                        if (x_a != x_b)
                        {
                            float z = z_a + (z_b - z_a)*((x - x_a)/(x_b - x_a));

                            if (z < z_buff[this->size().height()/2 - y][x + this->size().width()/2])
                            {
                                setPixelColor(x, y, color);
                                z_buff[this->size().height()/2 - y][x + this->size().width()/2] = z;
                            }
                            //setPixelColor(x, y, color);
                        }
                        else
                        {
                            if (z_a < z_buff[this->size().height()/2 - y][x + this->size().width()/2])
                            {
                                setPixelColor(x, y, color);
                                z_buff[this->size().height()/2 - y][x + this->size().width()/2] = z_a;
                            }
                        }
                    }
                }
            }
        }
    }
}

QColor CanvasLabel::getPixelColor(int x, int y) const
{
    return canvas.pixelColor(x + this->size().width()/2, this->size().height()/2 - y);
}

QImage CanvasLabel::getCanvas()
{
    return canvas;
}

void CanvasLabel::setCanvas(QImage newCanvas)
{
    canvas = newCanvas;
}

void CanvasLabel::updateCanvas()
{
    this->setPixmap(QPixmap::fromImage(canvas));
}

void CanvasLabel::updateCanvas(QImage image)
{
    this->setPixmap(QPixmap::fromImage(image));
}
