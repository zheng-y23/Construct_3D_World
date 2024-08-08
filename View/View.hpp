/*************************************************************************
【文件名】              View.hpp
【功能模块和目的】       包含界面类的头文件
【开发者及日期】         zheng-y23 2024-8-5
*************************************************************************/

#pragma once

#include "../Controller/Controller.hpp"
#include <iostream>
#include <string>

/*************************************************************************
【类名】                View
【功能】                界面类
【接口说明】             构建命令行用户界面，实现对控制器功能的调用、用户命令的读取和错误处理
                        static View& GetInstance();
                        void Start(Controller& controller);
                        void LoadFile(Controller& controller);
                        void SaveFile(Controller& controller);
                        void LoadCommand();
                        void ExecuteCommand(Controller& controller);
                        void ExecuteDisplay(Controller& controller);
                        void ExecuteEdit(Controller& controller);
                        void DisplayUsage();
【开发者及日期】         zheng-y23 2024-8-5
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