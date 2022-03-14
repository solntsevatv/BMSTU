#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "canvaslabel.h"
#include "mesh.h"
#include "matrix.h"
#include "camera.h"
#include "directionallight.h"
#include "meshloader.h"
#include <list>

//NOT COMPLETE

struct RenderParams
{
    float fAspectRatio;
    float fNear;
    float fFar;
    float fFov;
};

class SceneManager
{
public:
    SceneManager();
    SceneManager(RenderParams params); //v

    Camera mainCamera;
    RenderParams renderParams_;
    MeshLoader meshLoader_;
    DirectionalLight directionalLight;
    Mesh mesh;

    void SetRenderParams(RenderParams params);
    void render(CanvasLabel &RenderScreen, Mesh &mesh);

protected:
    Matrix projMatrix_;

    void formProjMatrix(); //v
};

#endif // SCENEMANAGER_H
