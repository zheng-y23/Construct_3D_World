/*************************************************************************
【文件名】           OBJExporter.hpp
【功能模块和目的】    包含写入.obj文件类的头文件
【开发者及日期】      zheng-y23 2024-8-4
*************************************************************************/

#pragma once

#include "Exporter.hpp"

/*************************************************************************
【类名】             OBJExporter
【功能】             写入.obj文件类
【接口说明】          继承Exporter类，实现模型写入功能
                     virtual void SaveModel(std::ofstream& File, const Model3D& Model) override;
【开发者及日期】      zheng-y23 2024-8-4
*************************************************************************/
class OBJExporter : public Exporter {
protected:
    //写入模型函数重载
    virtual void SaveModel(std::ofstream& File, const Model3D& Model) override;
};