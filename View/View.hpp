/*************************************************************************
View.hpp
包含界面类的头文件
zheng-y23 2024-8-5
*************************************************************************/

#pragma once

#include "../Controller/Controller.hpp"
#include <iostream>
#include <string>

/*************************************************************************
View
界面类
无参数
zheng-y23 2024-8-5
*************************************************************************/
class View {
public:
    enum class State {
        START,
        EDIT,
        DISPLAY
    };

    //获取界面类对象
    static View& GetInstance();
    //开始程序
    void Start(Controller& controller);
    //读取、输出文件
    void LoadFile(Controller& controller);
    void SaveFile(Controller& controller);
    //加载、执行指令
    void LoadCommand();
    void ExecuteCommand(Controller& controller);
    //执行展示命令
    void ExecuteDisplay(Controller& controller);
    //执行编辑命令
    void ExecuteEdit(Controller& controller);
    //显示用法
    void DisplayUsage();
private:
    std::string Command = "none";
    State m_State = State::START;
    //禁用拷贝构造函数和赋值运算符
    View() {}
    View(const View& Source) = delete;
    View& operator= (const View& Source) = delete;
};