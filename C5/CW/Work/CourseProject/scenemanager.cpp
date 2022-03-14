#include "scenemanager.h"
#include <iterator>
#include <QDebug>
#include <limits>

SceneManager::SceneManager()
{

}

SceneManager::SceneManager(RenderParams params)
{
    renderParams_ = params;
    directionalLight.direction = Vector3(0, 0, -1.0);
    formProjMatrix();
}

void SceneManager::SetRenderParams(RenderParams params)
{
    renderParams_ = params;
    directionalLight.direction = Vector3(0, 0, -1.0);
    formProjMatrix();
}

void SceneManager::render(CanvasLabel &RenderScreen, Mesh &mesh)
{
    Matrix viewMatrix;
    viewMatrix = mainCamera.formViewMatrix();

    std::vector<std::vector<float>> z_buff(RenderScreen.size().height(), std::vector<float>(RenderScreen.size().width()));

    for (auto &row : z_buff)
    {
        for (auto &elem : row)
        {
           elem = std::numeric_limits<float>::max();
        }
    }

    vector<Triangle> vecTrianglesToRaster;

    for (auto &tri : mesh.tris)
    {
        vecTrianglesToRaster.clear();

        float dp = directionalLight.direction.normalized().scalar(tri.getNormal());

        QColor color;
        if (dp <= 0)
        {
            color.setRgb(0, 0, 0);
        }
        else
        {
            int colorVal = dp * 255 * directionalLight.power;
            if (colorVal > 255)
                colorVal = 255;
            color.setRgb(colorVal, colorVal, colorVal);
        }
        tri.color = color;

        Triangle triangleProjected, triangleViewed;

        tri.vertices[0].vdot(viewMatrix, triangleViewed.vertices[0]);
        tri.vertices[1].vdot(viewMatrix, triangleViewed.vertices[1]);
        tri.vertices[2].vdot(viewMatrix, triangleViewed.vertices[2]);

        int clipped_num;
        Triangle clipped[2];
        clipped_num = triangleViewed.ClipAgainstPlane({0.0f, 0.0f, renderParams_.fNear}, {0.0f, 0.0f, 1.0f}, triangleViewed, clipped[0], clipped[1], triangleViewed.getNormal());

        for (int n = 0; n < clipped_num; n++)
        {
            clipped[n].vertices[0].vdot(projMatrix_, triangleProjected.vertices[0]);
            clipped[n].vertices[1].vdot(projMatrix_, triangleProjected.vertices[1]);
            clipped[n].vertices[2].vdot(projMatrix_, triangleProjected.vertices[2]);

            triangleProjected.vertices[0].z_ = clipped[n].vertices[0].z_;
            triangleProjected.vertices[1].z_ = clipped[n].vertices[1].z_;
            triangleProjected.vertices[2].z_ = clipped[n].vertices[2].z_;

            vecTrianglesToRaster.push_back(triangleProjected);
        }

        for (auto &triToRaster : vecTrianglesToRaster)
        {
            triToRaster.vertices[0].x_ *= 0.1 * RenderScreen.size().width();
            triToRaster.vertices[0].y_ *= 0.1 * RenderScreen.size().height();

            triToRaster.vertices[1].x_ *= 0.1 * RenderScreen.size().width();
            triToRaster.vertices[1].y_ *= 0.1 * RenderScreen.size().height();

            triToRaster.vertices[2].x_ *= 0.1 * RenderScreen.size().width();
            triToRaster.vertices[2].y_ *= 0.1 * RenderScreen.size().height();

            Triangle clipped[2];
            Triangle test_temp;
            list<Triangle> listTriangles;

            listTriangles.push_back(triToRaster);
            int nNewTriangles = 1;


            for (int p = 0; p < 4; p++)
            {
                int nTrisToAdd = 0;
                while (nNewTriangles > 0)
                {
                    Triangle test = listTriangles.front();
                    listTriangles.pop_front();
                    nNewTriangles--;
                    switch (p)
                    {
                    case 0:
                        nTrisToAdd = test_temp.ClipAgainstPlane({ 0.0f, (float)RenderScreen.height()/2 - 1, 0.0f }, { 0.0f, -1.0f, 0.0f }, test, clipped[0], clipped[1], test.getNormal());
                        break;
                    case 1:
                        nTrisToAdd = test_temp.ClipAgainstPlane({ 0.0f, -(float)RenderScreen.height()/2 + 1, 0.0f }, { 0.0f, 1.0f, 0.0f }, test, clipped[0], clipped[1], test.getNormal());
                        break;
                    case 2:
                        nTrisToAdd = test_temp.ClipAgainstPlane({ (float)RenderScreen.width()/2 - 1, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, test, clipped[0], clipped[1], test.getNormal());
                        break;
                    case 3:
                        nTrisToAdd = test_temp.ClipAgainstPlane({ -(float)RenderScreen.width()/2 + 1, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, test, clipped[0], clipped[1], test.getNormal());
                        break;
                    }

                    for (int w = 0; w < nTrisToAdd; w++)
                        listTriangles.push_back(clipped[w]);

                }
                nNewTriangles = listTriangles.size();
            }


            for (auto &tris : listTriangles)
            {
                RenderScreen.FillTriangleWithZBuffer(
                    tris.vertices[0],
                    tris.vertices[1],
                    tris.vertices[2],
                    tri.color,
                    z_buff
                 );
            }
        }
    }

    RenderScreen.updateCanvas();
}

void SceneManager::formProjMatrix()
{
    float fFovRad = 1.0f / tanf(renderParams_.fFov * 0.5f / 180.0f * M_PI);
    projMatrix_.data_[0][0] = renderParams_.fAspectRatio * fFovRad;
    projMatrix_.data_[1][1] = fFovRad;
    projMatrix_.data_[2][2] = renderParams_.fFar / (renderParams_.fFar - renderParams_.fNear);
    projMatrix_.data_[3][2] = (-renderParams_.fFar * renderParams_.fNear) / (renderParams_.fFar - renderParams_.fNear);
    projMatrix_.data_[2][3] = 1.0f;
    projMatrix_.data_[3][3] = 0.0f;
}
