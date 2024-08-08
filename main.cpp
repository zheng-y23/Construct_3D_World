/*************************************************************************
main.cpp
测试文件，请勿提交
zheng-y23 2024-7-27
*************************************************************************/

#include "Model/Model3D.hpp"
#include "Controller/Controller.hpp"
#include "View/View.hpp"
#include <iostream>

int main() {
    Controller &controller = Controller::GetInstance();
    View &view = View::GetInstance();

    view.Start(controller);

    return 0;
}

/********************************************* 
Controller单例模式的实例化方法如下
int main() {
    Singleton &s = Singleton::getInstance();
    s.test();
    return 0;
}
*********************************************/
