/*************************************************************************
【文件名称】             Element3D.hpp
【功能模块和目的】       包含数量一定的点的虚基类
【开发者及日期】         zheng-y23 2024-7-27
*************************************************************************/

#pragma once

#include "CountFixedSet.hpp"
#include "Point3D.hpp"

/*************************************************************************
【类名】                Element3D
【功能】                包含一定数量的点的虚基类
【接口说明】             构建包含固定点集的元素类（抽象类），被平面和线段继承，实现元素内点的修改、元素的求面积、体积
                        Point3D GetPoint(int Index) const;
                        void SetPoint(int ID, Point3D Point);
                        virtual double GetArea() const =0;
                        virtual double GetLength() const =0;
【开发者及日期】         zheng-y23 2024-7-27
*************************************************************************/
class Element3D {
public:
    //构造函数
    Element3D();
    Element3D(CountFixedSet<Point3D> Points);
    Element3D(const Element3D& Source);
    //析构函数
    ~Element3D();
    //赋值运算符重载
    Element3D& operator= (const Element3D& Source);
    //下标运算符重载
    Point3D operator[] (unsigned int Index) const;
    //获取点的坐标
    Point3D GetPoint(unsigned int Index) const;
    //修改点的坐标
    void SetPoint(int ID, Point3D Point);
    //求面积、长度（派生类中重载）
    virtual double GetArea() const =0;
    virtual double GetLength() const =0;
private:
    CountFixedSet<Point3D> m_Points;
    unsigned int m_Size {m_Points.Size};
public:
    const unsigned int& Size {m_Size};
};
