/*************************************************************************
Face3D.hpp
三维平面类
zheng-y23 2024-7-30
*************************************************************************/

#pragma once

#include "Element3D.hpp"

/*************************************************************************
Face3D
三维平面类
无参数
zheng-y23 2024-7-30
*************************************************************************/
class Face3D : public Element3D {
public:
    //构造函数
    Face3D();
    Face3D(CountFixedSet<Point3D> Points);
    Face3D(const Face3D& Source);
    //析构函数
    ~Face3D();
    //赋值运算符重载
    Face3D& operator= (const Face3D& Source);
    //获取面积、长度
    virtual double GetArea() const override;
    virtual double GetLength() const override;
};