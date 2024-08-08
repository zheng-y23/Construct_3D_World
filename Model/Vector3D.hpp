/*************************************************************************
【文件名】             Vector3D.hpp
【功能模块及目的】      实现三维、不同类型的向量类模版
【开发者及日期】        zheng-y23 2024-7-27
*************************************************************************/

#pragma once

#include "Vector.hpp"

/*************************************************************************
【类名】               Vector3D<T>
【接口说明】           Vector<T, 3> InnerCrossProduct(const Vector<T, 3>& Source);
【功能】               构建不同类型的三维向量
【开发者及日期】        zheng-y23 2024-7-26
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
【函数名称】            Vector3D
【函数功能】            默认构造函数
【参数】               无参数
【返回值】              无返回值
【开发者及日期】         zheng-y23 2024-7-26
*************************************************************************/
template <class T>
Vector3D<T>::Vector3D() {
    //空函数体
}

/*************************************************************************
【函数名称】             Vector3D
【函数功能】             拷贝构造函数
【参数】                 Vector3D常引用Source
【返回值】               无返回值
【开发者及日期】          zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Vector3D<T>::Vector3D(const Vector3D& Source) {
    if (this != &Source)
    {
       Vector<T, 3>::SetComponent(Source.Component);
    }
}

/*************************************************************************
【函数名称】             ~Vector3D
【函数功能】             析构函数
【参数】                 无参数
【返回值】               无返回值
【开发者及日期】          zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Vector3D<T>::~Vector3D() {
    //空函数体
}

/*************************************************************************
【函数名称】             operator=
【函数功能】             赋值运算符重载
【参数】                 Vector3D常引用
【返回值】               赋值后对象
【开发者及日期】          zheng-y23 2024-7-27
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
【函数名称】             InnerCrossProduct
【函数功能】             求三维向量外积
【参数】                 Vector3D常引用
【返回值】               向量的外积
【开发者及日期】          zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Vector<T, 3> Vector3D<T>::InnerCrossProduct(const Vector<T, 3>& Source) {
    Vector3D<T> Result;
    T t_x = Vector<T, 3>::Component[1] * Source.Component[2] - Vector<T, 3>::Component[2] * Source.Component[1];
    T t_y = Vector<T, 3>::Component[2] * Source.Component[0] - Vector<T, 3>::Component[0] * Source.Component[2];
    T t_z = Vector<T, 3>::Component[0] * Source.Component[1] - Vector<T, 3>::Component[1] * Source.Component[0];
    const T Components[] = {t_x, t_y, t_z};
    Result.SetComponent(Components);
    return Result;
}

