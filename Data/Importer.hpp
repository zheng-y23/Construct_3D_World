/*************************************************************************
【文件名】            Importer.hpp
【功能模块和目的】     导入数据类
【开发者及日期】       zheng-y23 2024-8-3
*************************************************************************/

#pragma once

#include "../Model/Model3D.hpp"
#include <string>
#include <fstream>

/*************************************************************************
【类名】               Importer
【功能】               导入数据类（抽象类）
【接口说明】           构建导入文件类，实现读取文件和加载模型功能
                      void ReadFile(std::string FilePath, Model3D* Model);
                      virtual void LoadModel(std::ifstream& File, Model3D* Model) =0;
【开发者及日期】       zheng-y23 2024-8-3
*************************************************************************/
class Importer {
public:
    //读取文件
    void ReadFile(std::string FilePath, Model3D* Model);
protected:
    //加载模型
    virtual void LoadModel(std::ifstream& File, Model3D* Model) =0;
};