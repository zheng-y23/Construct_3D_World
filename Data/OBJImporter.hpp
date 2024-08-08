/*************************************************************************
【文件名】            OBJImporter.hpp
【功能模块和目的】     包含导入.obj文件类的头文件
【开发者及日期】       zheng-y23 2024-8-4
*************************************************************************/

#pragma once

#include "Importer.hpp"

/*************************************************************************
【类名】              OBJImporter
【功能】              导入.obj文件类
【接口说明】           继承Importer类，实现对模型的加载
                      virtual void LoadModel(std::ifstream& File, Model3D* Model) override;
【开发者及日期】       zheng-y23 2024-8-4
*************************************************************************/
class OBJImporter : public Importer {
protected:
    //重载加载模型函数
    virtual void LoadModel(std::ifstream& File, Model3D* Model) override;
};