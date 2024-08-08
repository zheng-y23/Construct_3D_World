/*************************************************************************
【文件名】             OBJImporter.cpp
【功能模块和目的】      导入.obj文件类的具体实现
【开发者及日期】        zheng-y23 2024-8-4
*************************************************************************/

#include "OBJImporter.hpp"
#include <sstream>

/*************************************************************************
【函数名称】            LoadModel
【函数功能】            加载模型
【参数】               文件流File和模型Model
【返回值】              无返回值
【开发者及日期】         zheng-y23 2024-8-4
*************************************************************************/
void OBJImporter::LoadModel(std::ifstream& File, Model3D* Model) {
    Model3D mNewModel;
    std::string sline;
    std::vector<Point3D> vPoints;
    int iPointID = 0;
    int iLineID = 0;
    int iFaceID = 0;
    while(std::getline(File, sline))
    {
        char type = sline[0];
        char temp;
        std::stringstream Info(sline);
        switch (type)
        {
            case '#':
            {
                continue;
            }
            case 'g':
            {
                std::string name;
                Info >> temp >> name;
                mNewModel.SetName(name);
                break;
            }
            case 'v':
            {
                double Coordinate[3];
                Info >> temp >> Coordinate[0] >> Coordinate[1] >> Coordinate[2];
                Point3D Point;
                Point.SetComponent(Coordinate[0], Coordinate[1], Coordinate[2]);
                Point.SetID(iPointID + 1);
                vPoints.push_back(Point);
                iPointID += 1;
                break;
            }
            case 'l':
            {
                int ID[2] = {0};
                Info >> temp >> ID[0] >> ID[1];

                Point3D l_Point[2] = {vPoints[ID[0] - 1], vPoints[ID[1] - 1]};
                CountFixedSet<Point3D> Source(l_Point, 2);
                Line3D Line(Source);

                Line.SetID(iLineID + 1);
                mNewModel.AddLine(Line);
                iLineID += 1;
                break;
            }
            case 'f':
            {
                int ID[3] = {0};
                Info >> temp >> ID[0] >> ID[1] >> ID[2];

                Point3D f_Point[3] = {vPoints[ID[0] - 1], vPoints[ID[1] - 1], vPoints[ID[2] - 1]};
                CountFixedSet<Point3D> Source(f_Point, 3);
                Face3D Face(Source);

                Face.SetID(iFaceID + 1);
                mNewModel.AddFace(Face);
                iFaceID += 1;
                break;
            }
        }
    }
    *Model = mNewModel;
}