#ifndef MESH_H
#define MESH_H

//NOT COMPLETE

#include "triangle.h"
#include "baseobject.h"
#include <QColor>
#include <vector>


using namespace std;

class Mesh : public BaseObject
{
public:
    Mesh(); //v

    vector<Triangle> tris;
    QColor wireframeColor = Qt::white;

    void rotate(Vector3 delta) override;
    void move(Vector3 delta) override;
    void scale(Vector3 koef) override;

    void clearValues();
};

#endif // MESH_H
