/*************************************************************************
【文件名】               Exporter.cpp
【功能模块和目的】        写入模型类的具体实现
【开发者及日期】          zheng-y23 2024-8-4
*************************************************************************/

#include "Exporter.hpp"

/*************************************************************************
【函数名称】             WriteFile
【函数功能】             读取文件并调用写入文件
【参数】                文件路径FilePath和模型Model
【返回值】               无返回值
【开发者及日期】         zheng-y23 2024-8-4
*************************************************************************/
void Exporter::WriteFile(std::string FilePath, Model3D Model) {
    std::ofstream File;
    File.open(FilePath);
    if (File.is_open() == 1)
    {
        SaveModel(File, Model);
        File.close();
    }
    else
    {
        throw std::ios_base::failure("Fail to open file");
    }
}