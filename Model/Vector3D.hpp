/*************************************************************************
Vector3D.hpp
实现三维、不同类型的向量类模版
zheng-y23 2024-7-27
*************************************************************************/

#pragma once

#include "Vector.hpp"

/*************************************************************************
Vector3D<T>
三维T类型的向量类模版
类型T
zheng-y23 2024-7-26
*************************************************************************/
template <class T>
class Vector3D : public Vector<T, 3> {
public:
    //构造函数
    Vector3D();
    Vector3D(const Vector3D& Source);
    //析构函数
    virtual ~Vector3D();
    //赋值运算符重载
    Vector3D& operator= (const Vector3D& Source);
    //求三维向量外积
    Vector<T, 3> InnerCrossProduct(const Vector<T, 3>& Source);
};

/*************************************************************************
Vector3D
默认构造函数
无参数
无返回值
zheng-y23 2024-7-26
*************************************************************************/
template <class T>
Vector3D<T>::Vector3D() {
    //空函数体
}

/*************************************************************************
Vector3D
拷贝构造函数
Vector3D常引用Source
无返回值
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Vector3D<T>::Vector3D(const Vector3D& Source) {
    if (this != &Source)
    {
       Vector<T, 3>::SetComponent(Source.Component);
    }
}

/*************************************************************************
~Vector3D
析构函数
无参数
无返回值
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Vector3D<T>::~Vector3D() {
    //空函数体
}

/*************************************************************************
operator=
赋值运算符重载
Vector3D常引用
赋值后对象
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Vector3D<T>& Vector3D<T>::operator= (const Vector3D& Source) {
    if (this != &Source)
    {
       Vector<T, 3>::SetComponent(Source.Component);
    }
    return *this;
}

/*************************************************************************
InnerCrossProduct
求三维向量外积
Vector3D常引用
向量的外积
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Vector<T, 3> Vector3D<T>::InnerCrossProduct(const Vector<T, 3>& Source) {
    Vector3D<T> Result;
    T x = Vector<T, 3>::Component[1] * Source.Component[2] - Vector<T, 3>::Component[2] * Source.Component[1];
    T y = Vector<T, 3>::Component[2] * Source.Component[0] - Vector<T, 3>::Component[0] * Source.Component[2];
    T z = Vector<T, 3>::Component[0] * Source.Component[1] - Vector<T, 3>::Component[1] * Source.Component[0];
    const T Components[] = {x, y, z};
    Result.SetComponent(Components);
    return Result;
}

