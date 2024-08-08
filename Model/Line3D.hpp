/*************************************************************************
【文件名】              Line3D.hpp
【功能模块和目的】       三维线段类
【开发者及日期】         zheng-y23 2024-7-28
*************************************************************************/

#pragma once

#include "Element3D.hpp"

/*************************************************************************
【类名】                Line3D
【功能】                三维线段类
【接口说明】             继承Element3D类，实现面积、长度的获取
【开发者及日期】         zheng-y23 2024-7-28
*************************************************************************/
class Line3D : public Element3D {
public:
    //构造函数
    Line3D();
    Line3D(CountFixedSet<Point3D> Points);
    Line3D(const Line3D& Source);
    //赋值运算符重载
    Line3D& operator= (const Line3D& Source);
    //等于运算符重载
    bool operator== (const Line3D& Source);
    //流运算符重载
    friend std::ostream& operator<< (std::ostream& out, const Line3D& Line);
    //设置序号
    void SetID(size_t ID);
    //析构函数
    ~Line3D();
    //获取面积、长度
    virtual double GetArea() const override;
    virtual double GetLength() const override;
private:
    size_t m_ID;
public:
    const size_t& ID {m_ID};
};