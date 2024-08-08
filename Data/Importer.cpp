/*************************************************************************
【文件名】            Importer.cpp
【功能模块和目的】     导入数据类的具体实现
【开发者及日期】       zheng-y23 2024-8-4
*************************************************************************/

#include "Importer.hpp"

/*************************************************************************
【函数名称】          ReadFile
【函数功能】          读取文件并调用加载模型
【参数】              文件路径FilePath和模型Model
【返回值】            无返回值
【开发者及日期】       zheng-y23 2024-8-4
*************************************************************************/
void Importer::ReadFile(std::string FilePath, Model3D* Model) {
    std::ifstream File;
    File.open(FilePath);
    if (File.is_open() == 1)
    {
        LoadModel(File, Model);
        File.close();
    } 
    else 
    {
        throw std::ios_base::failure("Fail to open file");
    }
}
