/*************************************************************************
【文件名】             Point3D.hpp
【功能模块及目的】      三维点类
【开发者及日期】        zheng-y23 2024-7-27
*************************************************************************/

#pragma once

#include "Vector3D.hpp"

/*************************************************************************
【类名】               Point3D
【功能】               三维点类
【接口说明】           继承Vector3D<double>，构建三维点，实现坐标、序号设置和基类接口隐藏
                      void SetID(int ID);
                      void SetX(double x);
                      void SetY(double y);
                      void SetZ(double z);
                      void SetComponent(double x, double y, double z);
【开发者及日期】       zheng-y23 2024-7-27
*************************************************************************/
class Point3D : public Vector3D<double> {
public:
    //构造函数
    Point3D();
    Point3D(const Point3D& Source);
    //析构函数
    ~Point3D();
    //赋值运算符重载
    Point3D& operator= (const Point3D& Source);
    //等于运算符重载
    bool operator== (const Point3D& Source);
    //不等于运算符重载
    bool operator!= (const Point3D& Source);
    //流运算符重载
    friend std::ostream& operator<< (std::ostream& out, const Point3D& Point);
    //设置编号
    void SetID(int ID);
    //设置坐标
    void SetX(double x);
    void SetY(double y);
    void SetZ(double z);
    void SetComponent(double x, double y, double z);
private:
    unsigned int m_ID;
    //隐藏向量的运算接口
    using Vector<double, 3>::operator+;
    using Vector<double, 3>::operator+=;
    using Vector<double, 3>::operator-;
    using Vector<double, 3>::operator-=;
    using Vector<double, 3>::operator*;
    using Vector<double, 3>::operator*=;

    using Vector<double, 3>::CrossProduct;
    using Vector<double, 3>::InnerCrossProduct;

    using Vector<double, 3>::L0;
    using Vector<double, 3>::L1;
    using Vector<double, 3>::L2;
    using Vector<double, 3>::Lp;
    using Vector<double, 3>::Lmax;

    using Vector<double, 3>::InnerL;
public:
    //通过常引用获取点坐标及序号
    const double& X {Vector<double, 3>::Component[0]};
    const double& Y {Vector<double, 3>::Component[1]};
    const double& Z {Vector<double, 3>::Component[2]};
    const unsigned int& ID {m_ID};
};