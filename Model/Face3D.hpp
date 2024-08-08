/*************************************************************************
【文件名】                Face3D.hpp
【功能模块和目的】         三维平面类
【开发者及日期】           zheng-y23 2024-7-30
*************************************************************************/

#pragma once

#include "Element3D.hpp"

/*************************************************************************
【类名】                  Face3D
【功能】                  三维平面类
【接口说明】               继承Element3D类，实现对三维平面求周长、求面积
                          virtual double GetArea() const override;
                          virtual double GetLength() const override;
【开发者及日期】           zheng-y23 2024-7-30
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
    //等于运算符重载
    bool operator== (const Face3D& Source);
    //流运算符重载
    friend std::ostream& operator<< (std::ostream& out, const Face3D& Face);
    //设置序号
    void SetID(size_t ID);
    //获取面积、长度
    virtual double GetArea() const override;
    virtual double GetLength() const override;
private:
    size_t m_ID;
public:
    const size_t& ID {m_ID};
};
