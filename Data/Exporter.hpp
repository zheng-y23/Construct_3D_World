/*************************************************************************
【文件名】            Exporter.hpp
【功能模块和目的】     包含写入数据类的头文件
【开发者及日期】       zheng-y23 2024-8-4
*************************************************************************/

#pragma once

#include "../Model/Model3D.hpp"
#include <fstream>
#include <string>

/*************************************************************************
【类名】              Exporter
【功能】              写入数据类（抽象类）
【接口说明】           构建写入数据类，实现写入文件功能
                      void WriteFile(std::string FilePath, Model3D Model);
                      virtual void SaveModel(std::ofstream& File, const Model3D& Model) =0;
【开发者及日期】       zheng-y23 2024-8-4
*************************************************************************/
class Exporter {
public:
    //把模型写入文件
    void WriteFile(std::string FilePath, Model3D Model);
protected:
    //写入文件
    virtual void SaveModel(std::ofstream& File, const Model3D& Model) =0;
};