/*************************************************************************
Element3D.cpp
Element3D类的实现
zheng-y23 2024-7-27
*************************************************************************/

#include "Element3D.hpp"

/*************************************************************************
Element3D
默认构造函数
无参数
无返回值
zheng-y23 2024-7-27
*************************************************************************/
Element3D::Element3D() {
    //空函数体
}
 
/*************************************************************************
ELement3D
构造函数
无参数
无返回值
zheng-y23 2024-7-27
*************************************************************************/
Element3D::Element3D(CountFixedSet<Point3D> Points) {
    m_Points = Points;
    std::cout << "Element constructing" << std::endl;
    //std::cout << "In Elements:" << m_Points[0].X << std::endl;
    std::cout << "Element Constructed" << std::endl;
}

/*************************************************************************
ELement3D
拷贝构造函数
Element3D常引用Source
无返回值
zheng-y23 2024-7-27
*************************************************************************/
Element3D::Element3D(const Element3D& Source) {
    m_Points = Source.m_Points;
}

/*************************************************************************
~ELement3D
析构函数
无参数
无返回值
zheng-y23 2024-7-27
*************************************************************************/
Element3D::~Element3D() {
    //空函数体
}

/*************************************************************************
operator=
赋值运算符重载
Element3D常引用Source
赋值后对象
zheng-y23 2024-7-27
*************************************************************************/
Element3D& Element3D::operator= (const Element3D& Source) {
    m_Points = Source.m_Points;
    return *this;
}

/*************************************************************************
GetPoint
获取点的坐标
下标Index
下标对应的点
zheng-y23 2024-7-28
*************************************************************************/
Point3D Element3D::GetPoint(int Index) const {
    if (Index < m_Points.Size)
    {
        return m_Points[Index];
    }
    else
    {
        return m_Points[m_Points.Size - 1];
    }
}