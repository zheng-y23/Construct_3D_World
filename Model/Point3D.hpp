/*************************************************************************
Point3D.hpp
三维点类
zheng-y23 2024-7-27
*************************************************************************/

#pragma once

#include "Vector3D.hpp"

/*************************************************************************
Point3D
三维点类
无参数
zheng-y23 2024-7-27
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
    //设置坐标
    void SetX(double x);
    void SetY(double y);
    void SetZ(double z);
    void SetComponent(double x, double y, double z);
private:
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
    const double& X {Vector<double, 3>::Component[0]};
    const double& Y {Vector<double, 3>::Component[1]};
    const double& Z {Vector<double, 3>::Component[2]};

};