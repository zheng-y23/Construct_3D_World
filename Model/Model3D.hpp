/*************************************************************************
【文件名】             Model3D
【功能模块和目的】      三维几何体类
【开发者及日期】        zheng-y23 2024-7-31
*************************************************************************/

#pragma once

#include "Point3D.hpp"
#include "Line3D.hpp"
#include "Face3D.hpp"
#include <vector>

/*************************************************************************
【类名】               Model3D
【功能】               三维几何体类
【接口说明】           三维几何体类是Model的核心，包括了在几何体中增加、删除、修改点的接口，还有统计几何体中线段、平面总数
                      以及计算包围盒体积的函数
                      Line3D GetLine(int Index) const;
                      void AddLine(const Line3D& Source);
                      void AddLine(const Point3D& Point1, const Point3D& Point2);
                      void SetLinePoint(size_t LineID, size_t PointID, const Point3D& Point);
                      void DeleteLine(int ID);
                      Face3D GetFace(int Index) const;
                      void AddFace(const Face3D& Source);
                      void AddFace(const Point3D& Point1, const Point3D& Point2, const Point3D& Point3);
                      void SetFacePoint(size_t FaceID, size_t PointID, const Point3D& Point);
                      void DeleteFace(int ID);
                      void SetName(std::string Name);
                      double BoxVolume() const;
【开发者及日期】       zheng-y23 2024-7-31
*************************************************************************/
class Model3D {
public:
    //构造函数
    Model3D();
    Model3D(const Model3D& Source);
    Model3D(std::vector<Line3D> Lines, std::vector<Face3D> Faces);
    //析构函数
    ~Model3D();
    //赋值运算符重载
    Model3D& operator= (const Model3D& Source);
    //访问线段成员
    Line3D GetLine(unsigned int Index) const;
    //添加线段
    void AddLine(const Line3D& Source);
    void AddLine(const Point3D& Point1, const Point3D& Point2);
    //修改线段端点
    void SetLinePoint(size_t LineID, size_t PointID, const Point3D& Point);
    //删除线段
    void DeleteLine(int ID);
    //获取面成员
    Face3D GetFace(unsigned int Index) const;
    //添加面
    void AddFace(const Face3D& Source);
    void AddFace(const Point3D& Point1, const Point3D& Point2, const Point3D& Point3);
    //修改平面上的点
    void SetFacePoint(size_t FaceID, size_t PointID, const Point3D& Point);
    //删除平面
    void DeleteFace(int ID);
    //设置名字
    void SetName(std::string Name);
    //求最小包围立方体
    double BoxVolume() const;
private:
    std::vector<Line3D> m_Line;
    std::vector<Face3D> m_Face;
    size_t m_LineNum {m_Line.size()};
    size_t m_FaceNum {m_Face.size()};
    std::string m_Name;
public:
    const size_t& LineNum {m_LineNum};
    const size_t& FaceNum {m_FaceNum};
    const std::string& Name {m_Name};
};