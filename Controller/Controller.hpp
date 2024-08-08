/*************************************************************************
【文件名】            Controller.hpp
【功能模块和目的】     包含控制器类的头文件
【开发者及日期】       zheng-y23 2024-8-2
*************************************************************************/

#pragma once

#include "../Model/Point3D.hpp"
#include "../Model/Line3D.hpp"
#include "../Model/Face3D.hpp"
#include "../Model/Model3D.hpp"
#include "../Data/OBJImporter.hpp"
#include "../Data/OBJExporter.hpp"
#include <string>
#include <vector>
#include <memory>

/*************************************************************************
【类名】            Controller
【功能】            控制器基类
【接口说明】         构建控制器类，实现模型的加载、写入，线段和平面的添加、删除、修改、获取
                    RES ReadModel(std::string FilePath);
                    RES WriteModel(std::string FilePath);
                    RES GetLinePoint(size_t ID, Point3D* Point) const;
                    RES GetFacePoint(size_t ID, Point3D* Point) const;
                    RES GetLine(size_t ID, Line3D* Line) const;
                    RES GetFace(size_t ID, Face3D* Face) const;
                    RES GetLineID(size_t Index, size_t* ID) const;
                    RES GetFaceID(size_t Index, size_t* ID) const;
                    RES AddLine(const double* X, const double* Y, const double* Z);
                    RES AddFace(const double* X, const double* Y, const double* Z);
                    RES DeleteLine(size_t ID);
                    RES DeleteFace(size_t ID);   
                    RES SetLinePoint(size_t LineID, size_t PointID, double X, double Y, double Z);
                    RES SetFacePoint(size_t LineID, size_t PointID, double X, double Y, double Z);
                    CountOfElements GetCount() const;
【开发者及日期】     zheng-y23 2024-8-2
*************************************************************************/
class Controller {
public:
    //获取唯一实例
    static Controller& GetInstance();
    //异常枚举类
    enum class RES {
        DONE,
        READ_FILE_FAILURE,
        WRITE_FILE_FAILURE,
        INVALID_FILE_FORMAT,
        INDEX_OUT_OF_RANGE,
        ID_OUT_OF_RANGE,
        INVALID_COORDINATE,
        INVALID_FILE_PATH
    };

    //统计数据
    struct CountOfElements {
        size_t CountofLines;
        size_t CountofFaces;
        size_t CountofPoints;
        size_t MaxPointID;
        size_t MaxLineID;
        size_t MaxFaceID;
        double TotalArea;
        double TotalLength;
        double BoxVolume;
    };
    //加载和写入模型
    RES ReadModel(std::string FilePath);
    RES WriteModel(std::string FilePath);
    //获取线段或平面中的点
    RES GetLinePoint(size_t ID, Point3D* Point) const;
    RES GetFacePoint(size_t ID, Point3D* Point) const;
    //获取线段或平面
    RES GetLine(size_t ID, Line3D* Line) const;
    RES GetFace(size_t ID, Face3D* Face) const;
    RES GetLineID(size_t Index, size_t* ID) const;
    RES GetFaceID(size_t Index, size_t* ID) const;
    //添加线段或平面
    RES AddLine(const double* X, const double* Y, const double* Z);
    RES AddFace(const double* X, const double* Y, const double* Z);
    //删除线段或平面
    RES DeleteLine(size_t ID);
    RES DeleteFace(size_t ID);   
    //修改线段或平面上的点
    RES SetLinePoint(size_t LineID, size_t PointID, double X, double Y, double Z);
    RES SetFacePoint(size_t LineID, size_t PointID, double X, double Y, double Z);
    //获取统计数据
    CountOfElements GetCount() const;
private:
    Model3D m_Model;
    //禁用构造函数和赋值运算符
    Controller() {}
    Controller(const Controller& Source) = delete;
    Controller& operator= (const Controller& Source) = delete;
};
