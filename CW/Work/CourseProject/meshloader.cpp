#include "meshloader.h"
#include "QDebug"


MeshLoader::MeshLoader()
{

}

bool MeshLoader::LoadModel(Mesh &mesh, string filename)
{
    ifstream f(filename);
    if (!f.is_open())
        return false;
    mesh.clearValues();

    mesh.position_ = {0, 0, 0};
    mesh.rotation_ = {0, 0, 0};
    mesh.scale_ = {1.0, 1.0, 1.0};

    vector<Vector3> vec_temp;

    while (!f.eof())
    {
        char line[128];
        f.getline(line, 128);
        strstream s;
        s << line;

        char junk;

        if (line[0] == 'p')
        {
            s >> junk >> mesh.position_.x_ >> mesh.position_.y_ >> mesh.position_.z_;
        }

        if (line[0] == 'r')
        {
            s >> junk >> mesh.rotation_.x_ >> mesh.rotation_.y_ >> mesh.rotation_.z_;
        }

        if (line[0] == '~')
        {
            s >> junk >> mesh.scale_.x_ >> mesh.scale_.y_ >> mesh.scale_.z_;
        }

        if (line[0] == 'v')
        {
            Vector3 vertex;
            s >> junk >> vertex.x_ >> vertex.y_ >> vertex.z_;
            vec_temp.push_back(vertex);
        }

        if (line[0] == 'f')
        {
            int f[3];

            string str_1, str_2, str_3;
            s >> junk >> str_1 >> str_2 >> str_3;
            std::string delimiter = "/";
            std::string f_1 = str_1.substr(0, str_1.find(delimiter));
            std::string f_2 = str_2.substr(0, str_2.find(delimiter));
            std::string f_3 = str_3.substr(0, str_3.find(delimiter));
            f[0] = stoi(f_1);
            f[1] = stoi(f_2);
            f[2] = stoi(f_3);
            mesh.tris.push_back({vec_temp[f[0] - 1], vec_temp[f[1] - 1], vec_temp[f[2] - 1]});
        }
    }

    return true;
}

bool MeshLoader::SaveModel(Mesh mesh, string filename)
{
    vector<string> vert_temp;
    vector<string> tri_temp;

    QString fname = QString::fromStdString(filename + ".obj");
    QFile file(fname);
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);

        int f_count = 1;

        stream << "p " << mesh.position_.x_ << ' ' << mesh.position_.y_ << ' ' << mesh.position_.z_ << Qt::endl;
        stream << "r " << mesh.rotation_.x_ << ' ' << mesh.rotation_.y_ << ' ' << mesh.rotation_.z_ << Qt::endl;
        stream << "~ " << mesh.scale_.x_ << ' ' << mesh.scale_.y_ << ' ' << mesh.scale_.z_ << Qt::endl;

        for (auto tri : mesh.tris)
        {
            for (int i = 0; i < 3; i++)
                stream << "v " << tri.vertices[i].x_ << ' ' << tri.vertices[i].y_ << ' ' << tri.vertices[i].z_ << Qt::endl;
            stream << "f " << f_count << '/' << f_count << '/' << f_count << ' '\
                    << f_count + 1 << '/' << f_count + 1 << '/' << f_count + 1 << ' '\
                        << f_count + 2 << '/' << f_count + 2 << '/' << f_count + 2 << Qt::endl;
            f_count += 3;
        }
        file.close();

        return true;
    }
    return false;
}
