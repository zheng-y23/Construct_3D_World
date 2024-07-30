/*************************************************************************
Element3D.hpp
包含数量一定的点的虚基类
zheng-y23 2024-7-27
*************************************************************************/

#pragma once

#include "CountFixedSet.hpp"
#include "Point3D.hpp"

/*************************************************************************
Element3D
包含一定数量的点的虚基类
无参数
zheng-y23 2024-7-27
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
    //获取点的坐标
    Point3D GetPoint(int Index) const;
    //求面积、长度（派生类中重载）
    virtual double GetArea() const =0;
    virtual double GetLength() const =0;
private:
    CountFixedSet<Point3D> m_Points;
};
