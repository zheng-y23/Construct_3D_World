/*************************************************************************
main.cpp
测试文件，请勿提交
zheng-y23 2024-7-27
*************************************************************************/

#include "Point3D.hpp"
#include "Line3D.hpp"
#include "Face3D.hpp"
#include <iostream>

int main() {
    Point3D p1;
    p1.SetComponent(2, 3, 4);
    Point3D p2 = p1;
    p2.SetX(5);
    Point3D p3;
    p3.SetComponent(4, 5, 13);
    Point3D p4 = p3;

    Point3D points1[] = {p1, p2};
    CountFixedSet<Point3D> Points1(points1, 2);
    Point3D points2[] = {p3, p4};
    CountFixedSet<Point3D> Points2(points2, 2);
    Points2 = Points1;
    std::cout << "Points1: "<< Points1[0].X << " " << Points1[0].Y << " " << Points1[0].Z << std::endl;
    std::cout << "======line constructing======" << std::endl;
    Face3D f1(Points2);
    std::cout << "=======getting length======" << std::endl;
    //std::cout << l1.GetLength() << std::endl;
    //std::cout << Points2[0].X << std::endl;

    std::cout << "hello" << std::endl;

    return 0;
}