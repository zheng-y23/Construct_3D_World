/*************************************************************************
【文件名】               Model3D
【功能模块和目的】        三维点类具体实现
【开发者及日期】          zheng-y23 2024-7-31
*************************************************************************/

#include "Model3D.hpp"
#include <math.h>
#include <stdexcept>

/*************************************************************************
【函数名称】               Model3D
【函数功能】              默认构造函数
【参数】                  无参数
【返回值】                无返回值
【开发者及日期】          zheng-y23 2024-7-31
*************************************************************************/
Model3D::Model3D() {
    //空函数体
}

/*************************************************************************
【函数名称】               Model3D
【函数功能】              拷贝构造函数
【参数】                  Model3D常引用Source
【返回值】                无返回值
【开发者及日期】          zheng-y23 2024-7-31
*************************************************************************/
Model3D::Model3D(const Model3D& Source) {
    for (int i = 0; i < Source.LineNum; i++)
    {
        m_Line.push_back(Source.GetLine(i));
    }
    for (int i = 0; i < Source.FaceNum; i++)
    {
        m_Face.push_back(Source.GetFace(i));
    }
    m_LineNum = m_Line.size();
    m_FaceNum = m_Face.size();
    m_Name = Source.Name;
}

/*************************************************************************
【函数名称】               Model3D
【函数功能】              构造函数
【参数】                  线段与平面向量
【返回值】                无返回值
【开发者及日期】          zheng-y23 2024-8-1
*************************************************************************/
Model3D::Model3D(std::vector<Line3D> Lines, std::vector<Face3D> Faces) {
    for (int i = 0; i < Lines.size(); i++)
    {
        AddLine(Lines[i]);
    }
    for (int i = 0; i < Faces.size(); i++)
    {
        AddFace(Faces[i]);
    }
}

/*************************************************************************
【函数名称】               ~Model3D
【函数功能】              析构函数
【参数】                  无参数
【返回值】                无返回值
【开发者及日期】          zheng-y23 2024-8-1
*************************************************************************/
Model3D::~Model3D() {
    //空函数体
}

/*************************************************************************
【函数名称】               operator=
【函数功能】              赋值运算符重载
【参数】                  Model3D常引用Source
【返回值】                赋值后对象
【开发者及日期】          zheng-y23 2024-7-31
*************************************************************************/
Model3D& Model3D::operator= (const Model3D& Source) {
    if (this != &Source)
    {
        m_Line.clear();
        for (int i = 0; i < Source.LineNum; i++)
        {
            m_Line.push_back(Source.GetLine(i));
        }
        m_Face.clear();
        for (int i = 0; i < Source.FaceNum; i++)
        {
            m_Face.push_back(Source.GetFace(i));
        }
        m_LineNum = m_Line.size();
        m_FaceNum = m_Face.size();
        m_Name = Source.Name;
    }
    return *this;
}

/*************************************************************************
【函数名称】               GetLine
【函数功能】              获取线段
【参数】                  下标Index
【返回值】                下标对应的线段
【开发者及日期】          zheng-y23 2024-7-31
*************************************************************************/
Line3D Model3D::GetLine(int Index) const {
    if (Index >= m_Line.size())
    {
        throw std::out_of_range("Index out of range");
    }
    else
    {
        return m_Line[Index];
    }
}

/*************************************************************************
【函数名称】               AddLine
【函数功能】              添加线段
【参数】                  Line3D常引用Source
【返回值】                无返回值
【开发者及日期】          zheng-y23 2024-7-31
*************************************************************************/
void Model3D::AddLine(const Line3D& Source) {
    bool bIfnExist = 1;
    for (int i = 0; i < LineNum; i++)
    {
        bIfnExist *= (1 - (m_Line[i] == Source));
    }
    if (bIfnExist == 1)
    {
        m_LineNum += 1;
        m_Line.push_back(Source);
    }
    else 
    {
        throw std::invalid_argument("Invalid coordinate");
    }
}

/*************************************************************************
【函数名称】               AddLine
【函数功能】              添加线段
【参数】                  构成线段的两端点
【返回值】                无返回值
【开发者及日期】          zheng-y23 2024-7-31
*************************************************************************/
void Model3D::AddLine(const Point3D& Point1, const Point3D& Point2) {
    Point3D Points[] = {Point1, Point2};
    CountFixedSet<Point3D> Source(Points, 2);
    Line3D NewLine(Source);
    bool bIfnExist = 1;
    for (int i = 0; i < LineNum; i++)
    {
        bIfnExist *= (1 - (m_Line[i] == NewLine));
    }
    if (bIfnExist == 1)
    {
        m_Line.push_back(NewLine);
        m_LineNum += 1;
    }
    else 
    {
        throw std::invalid_argument("Invalid argument");
    }
}

/*************************************************************************
【函数名称】               SetLinePoint
【函数功能】              修改线段端点
【参数】                  端点的ID，新端点
【返回值】                无返回值
【开发者及日期】          zheng-y23 2024-8-1
*************************************************************************/
void Model3D::SetLinePoint(size_t LineID, size_t PointID, const Point3D& Point) {
    int iLineIndex = m_Line.size();
    for (int i = 0; i < m_Line.size(); i++)
    {
        if (m_Line[i].ID == LineID)
        {
            iLineIndex = i;
        } 
    }
    if (iLineIndex == m_Line.size())
    {
        throw std::out_of_range("ID out of range");
        return;
    }
    bool bIfExist = 0;
    for (int i = 0; i < 2; i++)
    {
        if (m_Line[iLineIndex][i].ID == PointID)
        {
            bIfExist = 1;
            break;
        }
    }
    if (bIfExist == 0)
    {
        throw std::out_of_range("ID out of range");
        return;
    }
    for (int i = 0; i < 2; i++)
    {
        if (m_Line[iLineIndex][i] == Point)
        {
            throw std::invalid_argument("Invalid argument");
            return;
        }
    }
    Line3D Line = m_Line[iLineIndex];
    Line.SetPoint(PointID, Point);
    for (int i = 0; i < m_Line.size(); i++)
    {
        if (Line == m_Line[i])
        {
            throw std::invalid_argument("Invalid arguments");
            return;
        }
    }
    m_Line[iLineIndex].SetPoint(PointID, Point);
}

/*************************************************************************
【函数名称】               DeleteLine
【函数功能】              删除线段
【参数】                  删除的线段
【返回值】                是否成功删除
【开发者及日期】          zheng-y23 2024-8-1
*************************************************************************/
void Model3D::DeleteLine(int ID) {
    bool bIfnExist = 1;
    for (int i = 0; i < m_Line.size(); i++)
    {
        bIfnExist *= (1 - m_Line[i].ID == ID);
        if (m_Line[i].ID == ID)
        {
            m_Line.erase(m_Line.begin() + i);
            m_LineNum -= 1;
        }
    }
    if (bIfnExist == 1)
    {
        throw std::out_of_range("ID out of range");
    }
}

/*************************************************************************
【函数名称】               GetFace
【函数功能】              获取平面
【参数】                  下标Index
【返回值】                下标对应的平面
【开发者及日期】          zheng-y23 2024-7-31
*************************************************************************/
Face3D Model3D::GetFace(int Index) const {
    if (Index >= m_Face.size())
    {
        throw std::out_of_range("Index out of range");
    }
    else
    {
        return m_Face[Index];
    }
}

/*************************************************************************
【函数名称】               AddFace
【函数功能】              添加平面
【参数】                  Face3D常引用Source
【返回值】                无返回值
【开发者及日期】          zheng-y23 2024-7-31
*************************************************************************/
void Model3D::AddFace(const Face3D& Source) {
    bool bIfnExist = 1;
    for (int i = 0; i < m_Face.size(); i++)
    {
        bIfnExist *= (1 - (m_Face[i] == Source));
    }
    if (bIfnExist == 1)
    {
        m_Face.push_back(Source);
        m_FaceNum += 1;
    }
    else
    {
        throw std::invalid_argument("Invalid argument");
    }
}

/*************************************************************************
【函数名称】               AddFace
【函数功能】              添加平面
【参数】                  构成平面的三个点
【返回值】                无返回值
【开发者及日期】          zheng-y23 2024-7-31
*************************************************************************/
void Model3D::AddFace(const Point3D& Point1, const Point3D& Point2, const Point3D& Point3) {
    Point3D Points[] = {Point1, Point2, Point3};
    CountFixedSet<Point3D> CFSet(Points, 3);
    Face3D Source(CFSet);
    bool bIfnExist = 1;
    for (int i = 0; i < m_Face.size(); i++)
    {
        bIfnExist *= (1 - (m_Face[i] == Source));
    }
    if (bIfnExist == 1)
    {
        m_Face.push_back(Source);
        m_FaceNum += 1;
    }
}

/*************************************************************************
【函数名称】               SetFacePoint
【函数功能】              修改平面上的点
【参数】                  编号ID和点
【返回值】                无返回值
【开发者及日期】          zheng-y23 2024-8-1
*************************************************************************/
void Model3D::SetFacePoint(size_t FaceID, size_t PointID, const Point3D& Point) {
    int FaceIndex = m_Face.size();
    for (int i = 0; i < m_Face.size(); i++)
    {
        if (m_Face[i].ID == FaceID)
        {
            FaceIndex = i;
        } 
    }
    if (FaceIndex == m_Face.size())
    {
        throw std::out_of_range("ID out of range");
        return;
    }
    bool bIfExist = 0;
    for (int i = 0; i < 3; i++)
    {
        if (m_Face[FaceIndex][i].ID == PointID)
        {
            bIfExist = 1;
            break;
        }
    }
    if (bIfExist == 0)
    {
        throw std::out_of_range("ID out of range");
        return;
    }
    for (int i = 0; i < 2; i++)
    {
        if (m_Face[FaceIndex][i] == Point)
        {
            throw std::invalid_argument("Invalid coordinate");
            return;
        }
    }
    Face3D Face = m_Face[FaceIndex];
    Face.SetPoint(PointID, Point);
    bIfExist = 0;
    for (int i = 0; i < m_Face.size(); i++)
    {
        if (Face == m_Face[i])
        {
            throw std::invalid_argument("Invalid coordinate");
            return;
        }
    }
    m_Face[FaceIndex].SetPoint(PointID, Point);
}

/*************************************************************************
【函数名称】               DeleteFace
【函数功能】              删除平面
【参数】                  平面的序号
【返回值】                无返回值
【开发者及日期】          zheng-y23 2024-8-1
*************************************************************************/
void Model3D::DeleteFace(int ID) {
    bool bIfExist = 0;
    for (int i = 0; i < m_Face.size(); i++)
    {
        if (m_Face[i].ID == ID)
        {
            bIfExist = 1;
            m_Face.erase(m_Face.begin() + i);
            m_FaceNum -= 1;
        }
    }
    if (bIfExist == 0)
    {
        throw std::out_of_range("ID out of range");
    }
}

/*************************************************************************
【函数名称】               SetName
【函数功能】              设置几何体的名字
【参数】                  名字的字符串
【返回值】                无返回值
【开发者及日期】          zheng-y23 2024-8-1
*************************************************************************/
void Model3D::SetName(std::string NewName) {
    m_Name = NewName;
}

/*************************************************************************
【函数名称】               BoxVolume
【函数功能】              获取最小包围立方体的体积
【参数】                  无参数
【返回值】                最小包围立方体的体积
【开发者及日期】          zheng-y23 2024-8-1
*************************************************************************/
double Model3D::BoxVolume() const {
    std::vector<double*> dCoordinates;
    for (int i = 0; i < m_Line.size(); i++)
    {
        double dCoordinate1[3] = {m_Line[i][0].X, m_Line[i][0].Y, m_Line[i][0].Z};
        double dCoordinate2[3] = {m_Line[i][1].X, m_Line[i][1].Y, m_Line[i][1].Z};
        dCoordinates.push_back(dCoordinate1);
        dCoordinates.push_back(dCoordinate2);
    }
    for (int i = 0; i < m_Face.size(); i++)
    {
        double dCoordinate1[3] = {m_Face[i][0].X, m_Face[i][0].Y, m_Face[i][0].Z};
        double dCoordinate2[3] = {m_Face[i][1].X, m_Face[i][1].Y, m_Face[i][1].Z};
        double dCoordinate3[3] = {m_Face[i][2].X, m_Face[i][2].Y, m_Face[i][2].Z};
        dCoordinates.push_back(dCoordinate1);
        dCoordinates.push_back(dCoordinate2);
        dCoordinates.push_back(dCoordinate3);
    }
    double dSides[3] = {0};
    double dXMax = 0;
    double dXMin = 0;
    for (int i = 0; i < dCoordinates.size(); i++)
    {
        if (dXMax < dCoordinates[i][0])
        {
            dXMax = dCoordinates[i][0];
        }
        if (dXMin > dCoordinates[i][0])
        {
            dXMin = dCoordinates[i][0];
        }
    }
    dSides[0] = dXMax - dXMin;
    
    double dYMax = 0;
    double dYMin = 0;
    for (int i = 0; i < dCoordinates.size(); i++)
    {
        if (dYMax < dCoordinates[i][1])
        {
            dYMax = dCoordinates[i][1];
        }
        if (dYMin > dCoordinates[i][1])
        {
            dYMin = dCoordinates[i][1];
        }
    }
    dSides[1] = dYMax - dYMin;

    double dZMax = 0;
    double dZMin = 0;
    for (int i = 0; i < dCoordinates.size(); i++)
    {
        if (dZMax < dCoordinates[i][2])
        {
            dZMax = dCoordinates[i][2];
        }
        if (dZMin > dCoordinates[i][2])
        {
            dZMin = dCoordinates[i][2];
        }
    }
    dSides[2] = dZMax - dZMin;

    double dMax = 0;
    for (int i = 0; i < 3; i++)
    {
        if (dMax < dSides[i])
        {
            dMax = dSides[i];
        }
    }
    return pow(dMax, 3);
}