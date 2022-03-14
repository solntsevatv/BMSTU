#ifndef MESHLOADER_H
#define MESHLOADER_H

#include "mesh.h"
#include "fstream"
#include "strstream"
#include <QFile>
#include <QTextStream>

class MeshLoader
{
public:
    MeshLoader();
    bool LoadModel(Mesh &mesh, string filename);
    bool SaveModel(Mesh mesh, string filename);
};

#endif // MESHLOADER_H
