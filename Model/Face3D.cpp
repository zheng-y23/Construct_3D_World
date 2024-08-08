/*************************************************************************
【文件名】               Face3D.cpp
【功能模块和目的】        三维平面类的具体实现
【开发者及日期】          zheng-y23 2024-7-30
*************************************************************************/

#include "Face3D.hpp"
#include <math.h>

/*************************************************************************
【函数名称】               Face3D
【函数功能】               默认构造函数
【参数】                  无参数
【返回值】                无返回值
【开发者及日期】          zheng-y23 2024-7-30
*************************************************************************/
Face3D::Face3D() {
    //空函数体
}

/*************************************************************************
【函数名称】               Face3D
【函数功能】               构造函数
【参数】                  三维点集合Points
【返回值】                无返回值
【开发者及日期】          zheng-y23 2024-7-30
*************************************************************************/
Face3D::Face3D(CountFixedSet<Point3D> Points) : Element3D(Points) {
    //空函数体
}

/*************************************************************************
【函数名称】               Face3D
【函数功能】               拷贝构造函数
【参数】                   Face3D常引用Source
【返回值】                无返回值
【开发者及日期】          zheng-y23 2024-7-30
*************************************************************************/
Face3D::Face3D(const Face3D& Source) : Element3D(Source) {
    m_ID = Source.ID;
}

/*************************************************************************
【函数名称】               ~Face3D
【函数功能】               析构函数
【参数】                  无参数
【返回值】                无返回值
【开发者及日期】          zheng-y23 2024-7-30
*************************************************************************/
Face3D::~Face3D() {
    //空函数体
}

/*************************************************************************
【函数名称】               operator=
【函数功能】               赋值运算符重载
【参数】                  Face3D常引用Source
【返回值】                赋值后对象
【开发者及日期】          zheng-y23 2024-7-30
*************************************************************************/
Face3D& Face3D::operator= (const Face3D& Source) {
    if (this != &Source)
    {
        Element3D::operator=(Source);
        m_ID = Source.ID;
    }
    return *this;
}

/*************************************************************************
【函数名称】               operator==
【函数功能】               等于运算符重载
【参数】                  Face3D常引用Source
【返回值】                两平面是否相同
【开发者及日期】          zheng-y23 2024-7-30
*************************************************************************/
bool Face3D::operator== (const Face3D& Source) {
    int iflag = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (Element3D::operator[](i) == Source[j])
            {
                iflag += 1;
            }
        }
    }
    return iflag == 3;
}

/*************************************************************************
【函数名称】               operator<<
【函数功能】               流运算符重载
【参数】                  输出流引用out和Face3D常引用Source
【返回值】                输出流
【开发者及日期】          zheng-y23 2024-8-6
*************************************************************************/
std::ostream& operator<< (std::ostream& out, const Face3D& Face) {
    out << "face " << Face.ID << ": ";
    out << "Point " << Face[0].ID << " (" << Face[0].X << ", " << Face[0].Y << ", " << Face[0].Z << ") ";
    out << "Point " << Face[1].ID << " (" << Face[1].X << ", " << Face[1].Y << ", " << Face[1].Z << ") ";
    out << "Point " << Face[2].ID << " (" << Face[2].X << ", " << Face[2].Y << ", " << Face[2].Z << ") ";
    out << "Area: " << Face.GetArea();
    return out;
}

/*************************************************************************
【函数名称】               SetID
【函数功能】               设置序号
【参数】                  序号ID
【返回值】                无返回值
【开发者及日期】          zheng-y23 2024-8-2
*************************************************************************/
void Face3D::SetID(size_t ID) {
    m_ID = ID;
}

/*************************************************************************
【函数名称】               GetArea
【函数功能】               获取三角形面积
【参数】                  无参数
【返回值】                三角形面积
【开发者及日期】          zheng-y23 2024-7-31
*************************************************************************/
double Face3D::GetArea() const {
    double Length1 = sqrt(std::pow(Element3D::GetPoint(0).X - Element3D::GetPoint(1).X, 2) 
        + pow(Element3D::GetPoint(0).Y - Element3D::GetPoint(1).Y, 2) + pow(Element3D::GetPoint(0).Z - Element3D::GetPoint(1).Z, 2));
    double Length2 = sqrt(std::pow(Element3D::GetPoint(2).X - Element3D::GetPoint(1).X, 2) 
        + pow(Element3D::GetPoint(2).Y - Element3D::GetPoint(1).Y, 2) + pow(Element3D::GetPoint(2).Z - Element3D::GetPoint(1).Z, 2));
    double Length3 = sqrt(std::pow(Element3D::GetPoint(0).X - Element3D::GetPoint(2).X, 2) 
        + pow(Element3D::GetPoint(0).Y - Element3D::GetPoint(2).Y, 2) + pow(Element3D::GetPoint(0).Z - Element3D::GetPoint(2).Z, 2));
    double p = (Length1 + Length2 + Length3) / 2;
    double Result = p * (p - Length1) * (p - Length2) * (p - Length3);
    return sqrt(Result);
}

/*************************************************************************
【函数名称】               GetLength
【函数功能】               获取周长
【参数】                  无参数
【返回值】                三角形周长
【开发者及日期】          zheng-y23 2024-7-31
*************************************************************************/
double Face3D::GetLength() const {
    double Length1 = sqrt(std::pow(Element3D::GetPoint(0).X - Element3D::GetPoint(1).X, 2) 
        + pow(Element3D::GetPoint(0).Y - Element3D::GetPoint(1).Y, 2) + pow(Element3D::GetPoint(0).Z - Element3D::GetPoint(1).Z, 2));
    double Length2 = sqrt(std::pow(Element3D::GetPoint(2).X - Element3D::GetPoint(1).X, 2) 
        + pow(Element3D::GetPoint(2).Y - Element3D::GetPoint(1).Y, 2) + pow(Element3D::GetPoint(2).Z - Element3D::GetPoint(1).Z, 2));
    double Length3 = sqrt(std::pow(Element3D::GetPoint(0).X - Element3D::GetPoint(2).X, 2) 
        + pow(Element3D::GetPoint(0).Y - Element3D::GetPoint(2).Y, 2) + pow(Element3D::GetPoint(0).Z - Element3D::GetPoint(2).Z, 2));
    double Result = Length1 + Length2 + Length3;
    return Result;
}
