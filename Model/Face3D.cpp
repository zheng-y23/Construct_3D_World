/*************************************************************************
Face3D.cpp
三维平面类的具体实现
zheng-y23 2024-7-30
*************************************************************************/

#include "Face3D.hpp"

/*************************************************************************
Face3D
默认构造函数
无参数
无返回值
zheng-y23 2024-7-30
*************************************************************************/
Face3D::Face3D() {
    //空函数体
}

/*************************************************************************
Face3D
构造函数
三维点集合Points
无返回值
zheng-y23 2024-7-30
*************************************************************************/
Face3D::Face3D(CountFixedSet<Point3D> Points) : Element3D(Points) {
    //空函数体
    std::cout << "Face constructing" << std::endl;
    std::cout << Points[0].X << std::endl;
    std::cout << "face constructed" << std::endl;
}

/*************************************************************************
Face3D
拷贝构造函数
Face3D常引用Source
无返回值
zheng-y23 2024-7-30
*************************************************************************/
Face3D::Face3D(const Face3D& Source) : Element3D(Source) {
    //空函数体
}

/*************************************************************************
~Face3D
析构函数
无参数
无返回值
zheng-y23 2024-7-30
*************************************************************************/
Face3D::~Face3D() {
    //空函数体
}

/*************************************************************************
operator=
赋值构造函数重载
Face3D常引用Source
赋值后对象
zheng-y23 2024-7-30
*************************************************************************/
Face3D& Face3D::operator= (const Face3D& Source) {
    if (this != &Source)
    {
        Element3D::operator=(Source);
    }
    return *this;
}


double Face3D::GetArea() const {

}
double Face3D::GetLength() const {

}