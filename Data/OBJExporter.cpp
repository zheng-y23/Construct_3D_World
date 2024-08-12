/*************************************************************************
【文件名】           OBJExporter.cpp
【功能模块和目的】    写入.obj文件类的具体实现
【开发者及日期】      zheng-y23 2024-8-4
*************************************************************************/

#include "OBJExporter.hpp"
#include "../Controller/Controller.hpp"
#include <sstream>
#include <iomanip>

/*************************************************************************
【函数名称】          SaveModel
【函数功能】          把模型数据写入文件
【参数】              文件流File和模型Model
【返回值】            无返回值
【开发者及日期】       zheng-y23 2024-8-4
*************************************************************************/
void OBJExporter::SaveModel(std::ofstream& File, const Model3D& Model) {
    //写入几何体名
    File << "g  " << Model.Name << std::endl;
    //写入点坐标
    std::vector<Point3D> vPoints;
    for (int i = 0; i < Model.LineNum; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            bool bIfnExist = 1;
            for (int k = 0; k < vPoints.size(); k++)
            {
                bIfnExist *= (1 - (vPoints[k].ID == Model.GetLine(i)[j].ID));
            }
            if (bIfnExist == 1)
            {
                vPoints.push_back(Model.GetLine(i)[j]);
            }
        }
    }
    for (int i = 0; i < Model.FaceNum; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            bool bIfnExist = 1;
            for (int k = 0; k < vPoints.size(); k++)
            {
                bIfnExist *= (1 - (vPoints[k].ID == Model.GetFace(i)[j].ID));
            }
            if (bIfnExist == 1)
            {
                vPoints.push_back(Model.GetFace(i)[j]);
            }
        }
    }

    //将点按序号排序
    Point3D pTemp;
    for (int i = 0; i < vPoints.size() - 1; i++)
    {
        for (int j = 0; j < vPoints.size() - i - 1; j++)
        {
            if (vPoints[j + 1].ID < vPoints[j].ID)
            {
                pTemp = vPoints[j];
                vPoints[j] = vPoints[j + 1];
                vPoints[j + 1] = pTemp;
            }
        }
    }

    for (int i = 0; i < vPoints.size(); i++)
    {
        File << "v  " << std::fixed << std::setprecision(1) << vPoints[i].X << "  " << vPoints[i].Y << "  " << vPoints[i].Z << std::endl;
    }

    //写入线段序号
    for (int i = 0; i < Model.LineNum; i++)
    {
        File << "l  " << Model.GetLine(i)[0].ID << "  " << Model.GetLine(i)[1].ID << std::endl; 
    }

    //写入平面序号
    for (int i = 0; i < Model.FaceNum; i++)
    {
        File << "f  " << Model.GetFace(i)[0].ID << "  " << Model.GetFace(i)[1].ID << "  " 
            << Model.GetFace(i)[2].ID << std::endl;
    }
}