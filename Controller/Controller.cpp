/*************************************************************************
【文件名】                 Controller.cpp
【功能模块和目的】          控制器类的具体实现
【开发者及日期】            zheng-y23 2024-8-2
*************************************************************************/

#include "Controller.hpp"

/*************************************************************************
【函数名称】                ReadModel
【函数功能】                读取模型文件
【参数】                    文件路径
【返回值】                  操作结果
【开发者及日期】            zheng-y23 2024-8-4
*************************************************************************/
Controller::RES Controller::ReadModel(std::string FilePath) {
    OBJImporter Import;
    try
    {
        Import.ReadFile(FilePath, &m_Model);
        return RES::DONE;
    }
    catch (const std::ios_base::failure& ex)
    {
        return RES::READ_FILE_FAILURE;
    }
}

/*************************************************************************
【函数名称】                WriteModel
【函数功能】                把模型写入文件
【参数】                    文件路径
【返回值】                  操作结果
【开发者及日期】            zheng-y23 2024-8-4
*************************************************************************/
Controller::RES Controller::WriteModel(std::string FilePath) {
    OBJExporter Export;
    try
    {
        Export.WriteFile(FilePath, m_Model);
        return RES::DONE;
    }
    catch (const std::ios_base::failure& ex)
    {
        return RES::WRITE_FILE_FAILURE;
    }
}

/*************************************************************************
【函数名称】                GetInstance
【函数功能】                获取唯一对象（单例模式）
【参数】                    无参数
【返回值】                  控制器类的唯一对象
【开发者及日期】            zheng-y23 2024-8-2
*************************************************************************/
Controller& Controller::GetInstance() {
    static Controller controller;
    return controller;
}

/*************************************************************************
【函数名称】                GetLinePoint
【函数功能】                获取线段端点
【参数】                    点的序号ID和存储指针
【返回值】                  操作结果
【开发者及日期】            zheng-y23 2024-8-2
*************************************************************************/
Controller::RES Controller::GetLinePoint(size_t ID, Point3D* Point) const{
    try
    {
        for (int i = 0; i < m_Model.LineNum; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                if (m_Model.GetLine(i)[j].ID == ID)
                {
                    *Point = m_Model.GetLine(i)[j];
                    return RES::DONE;
                }
            }
        }
        return RES::ID_OUT_OF_RANGE;
    }
    catch (const std::out_of_range& ex)
    {
        return RES::INDEX_OUT_OF_RANGE;
    }
}

/*************************************************************************
【函数名称】                GetFacePoint
【函数功能】                获取平面端点
【参数】                    点的序号ID和存储指针
【返回值】                  操作结果
【开发者及日期】            zheng-y23 2024-8-2
*************************************************************************/
Controller::RES Controller::GetFacePoint(size_t ID, Point3D* Point) const{
    try
    {
        for (int i = 0; i < m_Model.FaceNum; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (m_Model.GetFace(i)[j].ID == ID)
                {
                    *Point = m_Model.GetFace(i)[j];
                    return RES::DONE;
                }
            }
        }
        return RES::ID_OUT_OF_RANGE;
    }
    catch (const std::out_of_range& ex)
    {
        return RES::INDEX_OUT_OF_RANGE;
    }
}

/*************************************************************************
【函数名称】                GetLine
【函数功能】                获取线段
【参数】                    线段的序号和指针
【返回值】                  操作结果
【开发者及日期】            zheng-y23 2024-8-2
*************************************************************************/
Controller::RES Controller::GetLine(size_t ID, Line3D* Line) const{
    try
    {
        Line3D LineTest;
        for (int i = 0; i < m_Model.LineNum; i++)
        {
            if (m_Model.GetLine(i).ID == ID)
            {
                (*Line) = m_Model.GetLine(i);
                return RES::DONE;
            }
        }
        return RES::ID_OUT_OF_RANGE;
    }
    catch (const std::out_of_range& ex)
    {
        return RES::INDEX_OUT_OF_RANGE;
    }
}

/*************************************************************************
【函数名称】                GetFace
【函数功能】                获取平面
【参数】                    平面的序号和指针
【返回值】                  操作结果
【开发者及日期】            zheng-y23 2024-8-2
*************************************************************************/
Controller::RES Controller::GetFace(size_t ID, Face3D* Face) const{
    try
    {
        for (int i = 0; i < m_Model.FaceNum; i++)
        {
            if (m_Model.GetFace(i).ID == ID)
            {
                *Face = m_Model.GetFace(i);
                return RES::DONE;
            }
        }
        return RES::ID_OUT_OF_RANGE;
    }
    catch (const std::out_of_range& ex)
    {
        return RES::INDEX_OUT_OF_RANGE;
    }
}

/*************************************************************************
【函数名称】                GetLineID
【函数功能】                将线段下标转化为序号
【参数】                    下标和序号指针
【返回值】                  操作结果
【开发者及日期】            zheng-y23 2024-8-7
*************************************************************************/
Controller::RES Controller::GetLineID(size_t Index, size_t* ID) const {
    try
    {
        *ID = m_Model.GetLine(Index).ID;
        return RES::DONE;
    }
    catch(const std::out_of_range& e)
    {
        return RES::INDEX_OUT_OF_RANGE;
    }
}

/*************************************************************************
【函数名称】                GetFaceID
【函数功能】                将平面的下标转化为序号
【参数】                    下标和序号指针
【返回值】                  操作结果
【开发者及日期】            zheng-y23 2024-8-7
*************************************************************************/
Controller::RES Controller::GetFaceID(size_t Index, size_t* ID) const {
    try
    {
        *ID = m_Model.GetFace(Index).ID;
        return RES::DONE;
    }
    catch(const std::out_of_range& e)
    {
        return RES::INDEX_OUT_OF_RANGE;
    }
}

/*************************************************************************
【函数名称】                AddLine
【函数功能】                添加线段
【参数】                    端点的坐标
【返回值】                  操作结果
【开发者及日期】            zheng-y23 2024-8-2
*************************************************************************/
Controller::RES Controller::AddLine(const double* X, const double* Y, const double* Z) {
    Point3D Points[2];
    CountOfElements count = GetCount();
    for (int i = 0; i < 2; i++)
    {
        Points[i].SetComponent(X[i], Y[i], Z[i]);
        Points[i].SetID(count.MaxPointID + 1 + i);
    }
    CountFixedSet<Point3D> Source(Points, 2);
    Line3D Line(Source);
    Line.SetID(count.MaxLineID + 1);
    try
    {
        m_Model.AddLine(Line);
        return RES::DONE;
    }
    catch(const std::invalid_argument& e)
    {
        return RES::INVALID_COORDINATE;
    }
    
}

/*************************************************************************
【函数名称】                AddFace
【函数功能】                添加平面
【参数】                    确定平面的点坐标
【返回值】                  操作结果
【开发者及日期】            zheng-y23 2024-8-2
*************************************************************************/
Controller::RES Controller::AddFace(const double* X, const double* Y, const double* Z) {
    Point3D Points[3];
    CountOfElements count = GetCount();
    for (int i = 0; i < 3; i++)
    {
        Points[i].SetComponent(X[i], Y[i], Z[i]);
        Points[i].SetID(count.MaxPointID + i + 1);
    }
    CountFixedSet<Point3D> Source(Points, 3);
    Face3D Face(Source);
    Face.SetID(count.MaxFaceID + 1);
    try
    {
        m_Model.AddFace(Face);
        return RES::DONE;
    }
    catch(const std::invalid_argument& e)
    {
        return RES::INVALID_COORDINATE;
    }
    
}

/*************************************************************************
【函数名称】                DeleteLine
【函数功能】                删除线段
【参数】                    线段的序号
【返回值】                  操作结果
【开发者及日期】            zheng-y23 2024-8-2
*************************************************************************/
Controller::RES Controller::DeleteLine(size_t ID) {
    try
    {
        m_Model.DeleteLine(ID);
        return RES::DONE;
    }
    catch (const std::out_of_range& ex)
    {
        return RES::ID_OUT_OF_RANGE;
    }
}

/*************************************************************************
【函数名称】                DeleteFace
【函数功能】                删除平面
【参数】                    平面的序号
【返回值】                  操作结果
【开发者及日期】            zheng-y23 2024-8-2
*************************************************************************/
Controller::RES Controller::DeleteFace(size_t ID) {
    try
    {
        m_Model.DeleteFace(ID);
        return RES::DONE;
    }
    catch (const std::out_of_range& ex)
    {
        return RES::ID_OUT_OF_RANGE;
    }
    
}

/*************************************************************************
【函数名称】                SetLinePoint
【函数功能】                设置线段端点
【参数】                    端点序号和新点坐标
【返回值】                  操作结果
【开发者及日期】            zheng-y23 2024-8-2
*************************************************************************/
Controller::RES Controller::SetLinePoint(size_t LineID, size_t PointID, double X, double Y, double Z) {
    try
    {
        CountOfElements count = GetCount();
        Point3D Point;
        Point.SetComponent(X, Y, Z);
        Point.SetID(count.MaxPointID + 1);
        m_Model.SetLinePoint(LineID, PointID, Point);
        return RES::DONE;
    }
    catch (const std::out_of_range& ex)
    {
        return RES::ID_OUT_OF_RANGE;
    }
    catch (const std::invalid_argument& ex)
    {
        return RES::INVALID_COORDINATE;
    }
}

/*************************************************************************
【函数名称】                SetFacePoint
【函数功能】                设置平面上的点
【参数】                    点序号和新点坐标
【返回值】                  操作结果
【开发者及日期】            zheng-y23 2024-8-2
*************************************************************************/
Controller::RES Controller::SetFacePoint(size_t FaceID, size_t PointID, double X, double Y, double Z) {
    try
    {
        CountOfElements count = GetCount();
        Point3D Point;
        Point.SetComponent(X, Y, Z);
        Point.SetID(count.MaxPointID + 1);
        m_Model.SetFacePoint(FaceID, PointID, Point);
        return RES::DONE;
    }
    catch (const std::out_of_range& ex)
    {
        return RES::ID_OUT_OF_RANGE;
    }
    catch (const std::invalid_argument& ex)
    {
        return RES::INVALID_COORDINATE;
    }
}

/*************************************************************************
【函数名称】                GetCount
【函数功能】                获取统计数据
【参数】                    无参数
【返回值】                  返回包含统计数据的结构体
【开发者及日期】            zheng-y23 2024-8-2
*************************************************************************/
Controller::CountOfElements Controller::GetCount() const {
    CountOfElements Count;
    //线段数和平面数
    Count.CountofFaces = m_Model.FaceNum;
    Count.CountofLines = m_Model.LineNum;
    //点数
    std::vector<Point3D> Points;
    for (int i = 0; i < m_Model.FaceNum; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            bool IfnExist = 1;
            for (int k = 0; k < Points.size(); k++)
            {
                IfnExist *= (1 - (m_Model.GetFace(i)[j] == Points[k]));
            }
            if (IfnExist == 1)
            {
                Points.push_back(m_Model.GetFace(i)[j]);
            }
        }
    }
    for (int i = 0; i < m_Model.LineNum; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            bool IfnExist = 1;
            for (int k = 0; k < Points.size(); k++)
            {
                IfnExist *= (1 - (m_Model.GetLine(i)[j] == Points[k]));
            }
            if (IfnExist == 1)
            {
                Points.push_back(m_Model.GetLine(i)[j]);
            }
        }
    }
    Count.CountofPoints = Points.size();
    //最大点序号
    Count.MaxPointID = 0;
    for (int i = 0; i < Points.size(); i++)
    {
        if (Count.MaxPointID < Points[i].ID)
        {
            Count.MaxPointID = Points[i].ID;
        }
    }
    //最大线段序号
    Count.MaxLineID = 0;
    for (int i = 0; i < Count.CountofLines; i++)
    {
        if (Count.MaxLineID < m_Model.GetLine(i).ID)
        {
            Count.MaxLineID = m_Model.GetLine(i).ID;
        }
    }
    //最大平面序号
    Count.MaxFaceID = 0;
    for (int i = 0; i < Count.CountofFaces; i++)
    {
        if (Count.MaxFaceID < m_Model.GetFace(i).ID)
        {
            Count.MaxFaceID = m_Model.GetFace(i).ID;
        }
    }
    //总长度
    Count.TotalLength = 0;
    for (int i = 0; i < m_Model.LineNum; i++)
    {
        Count.TotalLength += m_Model.GetLine(i).GetLength();
    }
    //总面积
    Count.TotalArea = 0;
    for (int i = 0; i < m_Model.FaceNum; i++)
    {
        Count.TotalArea += m_Model.GetFace(i).GetArea();
    }
    //包围盒体积
    Count.BoxVolume = m_Model.BoxVolume();
    return Count;
}