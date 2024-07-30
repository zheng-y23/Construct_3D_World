/*************************************************************************
Line3D.hpp
三维线段类
zheng-y23 2024-7-28
*************************************************************************/

#pragma once

#include "Element3D.hpp"

/*************************************************************************
Line3D
三维线段类
无参数
zheng-y23 2024-7-28
*************************************************************************/
class Line3D : public Element3D {
public:
    //构造函数
    Line3D();
    Line3D(CountFixedSet<Point3D> Points);
    Line3D(const Line3D& Source);
    //析构函数
    ~Line3D();
    //获取面积、长度
    virtual double GetArea() const override;
    virtual double GetLength() const override;
};