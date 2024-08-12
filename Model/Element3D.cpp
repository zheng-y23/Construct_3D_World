/*************************************************************************
【文件名】             Element3D.cpp
【功能模块和目的】      Element3D类的实现
【开发者及日期】        zheng-y23 2024-7-27
*************************************************************************/

#include "Element3D.hpp"

/*************************************************************************
【函数名称】            Element3D
【函数功能】            默认构造函数
【参数】               无参数
【返回值】             无返回值
【开发者及日期】        zheng-y23 2024-7-27
*************************************************************************/
Element3D::Element3D() {
    //空函数体
}
 
/*************************************************************************
【函数名称】            ELement3D
【函数功能】            构造函数
【参数】               无参数
【返回值】             无返回值
【开发者及日期】        zheng-y23 2024-7-27
*************************************************************************/
Element3D::Element3D(CountFixedSet<Point3D> Points) {
    m_Points = Points;
    m_Size = Points.Size;
}

/*************************************************************************
【函数名称】            Element3D
【函数功能】            拷贝构造函数
【参数】               Element3D常引用Source
【返回值】             无返回值
【开发者及日期】        zheng-y23 2024-7-27
*************************************************************************/
Element3D::Element3D(const Element3D& Source) {
    m_Points = Source.m_Points;
    m_Size = Source.Size;
}

/*************************************************************************
【函数名称】            ~ELement3D
【函数功能】            析构函数
【参数】               无参数
【返回值】             无返回值
【开发者及日期】        zheng-y23 2024-7-27
*************************************************************************/
Element3D::~Element3D() {
    //空函数体
}

/*************************************************************************
【函数名称】            operator=
【函数功能】            赋值运算符重载
【参数】               Element3D常引用Source
【返回值】             赋值后对象
【开发者及日期】        zheng-y23 2024-7-27
*************************************************************************/
Element3D& Element3D::operator= (const Element3D& Source) { 
    if (this != &Source)
    {
        m_Size = Source.Size;
        Point3D Points[m_Size];
        for (int i = 0; i < Size; i++)
        {
            Points[i] = Source[i];
        }
        CountFixedSet<Point3D> NewSet(Points, m_Size);
        m_Points = NewSet;
    }
    return *this;
}

/*************************************************************************
【函数名称】            operator[]
【函数功能】            下标运算符重载
【参数】               下标Index
【返回值】             下标对应的点
【开发者及日期】        zheng-y23 2024-7-31
*************************************************************************/
Point3D Element3D::operator[] (unsigned int Index) const {
    if (Index >= m_Size)
    {
        throw std::out_of_range("Index out of range");
    }
    return GetPoint(Index);
}

/*************************************************************************
【函数名称】            GetPoint
【函数功能】            获取点的坐标
【参数】               下标Index
【返回值】             下标对应的点
【开发者及日期】        zheng-y23 2024-7-28
*************************************************************************/
Point3D Element3D::GetPoint(unsigned int Index) const {
    if (Index < m_Points.Size)
    {
        return m_Points[Index];
    }
    else
    {
        throw std::out_of_range("Index out of range");
    }
}

/*************************************************************************
【函数名称】            SetPoint
【函数功能】            修改点的坐标
【参数】               点的编号Id，点Point
【返回值】             无返回值
【开发者及日期】        zheng-y23 2024-8-1
*************************************************************************/
void Element3D::SetPoint(int Id, Point3D Point) {
    int iflag = 0;
    for (int Index = 0; Index < m_Points.Size; Index++)
    {
        if (operator[](Index).ID == Id)
        {
            m_Points.SetELement(Index, Point);
            iflag = 1;
        }
    }
    if (iflag == 0)
    {
        throw std::out_of_range("ID out of range");
    }
}