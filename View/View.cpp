/*************************************************************************
【文件名】               View.cpp
【功能模块和目的】       界面类的具体实现
【开发者及日期】         zheng-y23 2024-8-5
*************************************************************************/

#include "View.hpp"
#include <sstream>
#include <iomanip>

/*************************************************************************
【函数名称】             GetInstance
【函数功能】             获取唯一对象（单例模式）
【参数】                无参数
【返回值】              界面类的唯一对象
【开发者及日期】         zheng-y23 2024-8-5
*************************************************************************/
View& View::GetInstance() {
    static View view;
    return view;
}

/*************************************************************************
【函数名称】             Start
【函数功能】             开启所有程序
【参数】                控制器的引用
【返回值】              无返回值
【开发者及日期】         zheng-y23 2024-8-6
*************************************************************************/
void View::Start(Controller& controller) {
    std::cout << "######################################################################################################################################" << std::endl;
    std::cout << "====================================================Construct 3D World================================================================" << std::endl;
    std::cout << "######################################################################################################################################\n" << std::endl;

    std::cout << "Welcome to use our 3D World Constructor! \nTo get start, load your MODEL first.(enter 'q' to QUIT)\n" << std::endl;
    LoadFile(controller);

    DisplayUsage();

    while(true)
    {
        if (Command == "q")
        {
            SaveFile(controller);
        }
        LoadCommand();
        ExecuteCommand(controller);
    }
}

/*************************************************************************
【函数名称】             LoadFile
【函数功能】             读入用户提供的文件
【参数】                控制器的引用
【返回值】              无返回值
【开发者及日期】         zheng-y23 2024-8-6
*************************************************************************/
void View::LoadFile(Controller& controller) {
    std::cout << "> Please enter the FILE PATH: ";
    std::string sFilePath;
    std::getline(std::cin, sFilePath);
    if (sFilePath == "q")
    {
        exit(0);
    }
    Controller::RES rResult = controller.ReadModel(sFilePath);
    if (rResult == Controller::RES::READ_FILE_FAILURE)
    {
        while(controller.ReadModel(sFilePath) != Controller::RES::DONE)
        {
            std::cout << "> Invalid FILE PATH! Please enter again: ";
            std::getline(std::cin, sFilePath);
            if (sFilePath == "q")
            {
                exit(0);
            }
        }
    }
    std::cout << "> Done." << std::endl;
}

/*************************************************************************
【函数名称】             SaveFile
【函数功能】             将模型信息保存到用户提供的路径
【参数】                控制器的引用
【返回值】              无返回值
【开发者及日期】         zheng-y23 2024-8-6
*************************************************************************/
void View::SaveFile(Controller& controller) {
    std::string sIfSave;
    std::cout << "> Do you want to SAVE the changes to the model? (enter y/n) ";
    std::cin >> sIfSave;
    if (sIfSave == "y")
    {
        std::string sPath;
        std::cout << "> Where would you like to save (FILE PATH):  ";
        std::cin >> sPath;
        Controller::RES rResult = controller.WriteModel(sPath);
        if (rResult == Controller::RES::DONE)
        {
            std::cout << "> Done." << std::endl;
            std::cout << "====================================================SEE YOU NEXT TIME================================================================" << std::endl;
            exit(0);
        }
        else if (rResult == Controller::RES::WRITE_FILE_FAILURE)
        {
            std::cout << "[Error] INVALID FILE PATH" << std::endl;
            return;
        }
    }
    else if (sIfSave == "n")
    {
        std::cout << "====================================================SEE YOU NEXT TIME================================================================" << std::endl;
        exit(0);
    }
    else
    {
        std::cout << "[Error] INVALID COMMAND (try y/n)" << std::endl; 
        return;
    }
}

/*************************************************************************
【函数名称】             LoadCommand
【函数功能】             从用户输入中获取指令
【参数】                无参数
【返回值】              无返回值
【开发者及日期】         zheng-y23 2024-8-6
*************************************************************************/
void View::LoadCommand() {
    if (m_State == State::START)
    {
        std::cout << "> ";
    }
    if (m_State == State::EDIT)
    {
        std::cout << "[Edit] ";
    }
    if (m_State == State::DISPLAY)
    {
        std::cout << "[Display] ";
    }
    std::getline(std::cin, Command);
}

/*************************************************************************
【函数名称】             ExecuteCommand
【函数功能】             执行读入的指令
【参数】                控制器的引用
【返回值】              无返回值
【开发者及日期】         zheng-y23 2024-8-6
*************************************************************************/
void View::ExecuteCommand(Controller& controller) {
    if (Command == "s")
    {
        m_State = State::START;
        DisplayUsage();
    }
    else if (Command == "e")
    {
        m_State = State::EDIT;
        DisplayUsage();
    }
    else if (Command == "d")
    {
        m_State = State::DISPLAY;
        DisplayUsage();
    }
    else if (Command == "h")
    {
        DisplayUsage();
    }
    else 
    {
        if (m_State == State::DISPLAY)
        {
            ExecuteDisplay(controller);
        }
        if (m_State == State::EDIT)
        {
            ExecuteEdit(controller);
        }
    }
}

/*************************************************************************
【函数名称】             ExecuteDisplay
【函数功能】             执行展示模式下的指令
【参数】                控制器的引用
【返回值】              无返回值
【开发者及日期】         zheng-y23 2024-8-6
*************************************************************************/
void View::ExecuteDisplay(Controller& controller) {
    std::stringstream ssCommand(Command);
    std::string sType;
    int iID;
    Line3D Line;
    Face3D Face;
    Controller::CountOfElements cCount = controller.GetCount();

    ssCommand >> sType;
    if (ssCommand.fail() == 1)
    {
        std::cout << "[Error] INVALID COMMAND (enter 'h' for help)" << std::endl;
        return; 
    }

    if (Command == "l")
    {   
        size_t LineID;
        std::cout << "[Display] ";
        if (cCount.CountofLines == 0)
        {
            std::cout << "NO LINES IN MODEL" << std::endl;
            return;
        }
        for (int i = 0; i < cCount.CountofLines; i++)
        {
            controller.GetLineID(i, &LineID);
            controller.GetLine(LineID, &Line);
            if (i != 0)
            {
                std::cout << "          ";
            }
            std::cout << Line << std::endl;
        }
    }
    else if (Command == "f")
    {
        size_t FaceID;
        std::cout << "[Display] ";
        if (cCount.CountofFaces == 0)
        {
            std::cout << "NO FACES IN MODEL" << std::endl;
            return;
        }
        for (int i = 0; i < cCount.CountofFaces; i++)
        {
            controller.GetFaceID(i, &FaceID);
            controller.GetFace(FaceID, &Face);
             if (i != 0)
            {
                std::cout << "          ";
            }
            std::cout << Face << std::endl;
        } 
    }
    else if (Command[0] == 'l')
    {
        ssCommand.str(Command);
        ssCommand >> sType >> iID;
        if (ssCommand.fail() == 1)
        {
            std::cout << "[Error] INVALID ARGUMENT" << std::endl;
            return;
        }
        Controller::RES rResult = controller.GetLine(iID, &Line);
        if (rResult == Controller::RES::ID_OUT_OF_RANGE)
        {
            std::cout << "[Error] ";
            std::cout << "LINE " << iID << " DOES NOT EXIST" << std::endl;
            return; 
        }
        std::cout << "[Display] ";
        std::cout << Line << std::endl;
    }
    else if (Command[0] == 'f')
    {
        ssCommand.str(Command);
        ssCommand >> sType >> iID;
        if (ssCommand.fail() == 1)
        {
            std::cout << "[Error] INVALID ARGUMENT" << std::endl;
            return;
        }
        Controller::RES rResult = controller.GetFace(iID, &Face);
        if (rResult == Controller::RES::ID_OUT_OF_RANGE)
        {
            std::cout << "[Error] ";
            std::cout << "FACE " << iID << " DOES NOT EXIST" << std::endl;
            return;
        }
        std::cout << "[Display] ";
        std::cout << Face << std::endl;
    }
    else if (Command == "i")
    {
        Controller::CountOfElements cCount = controller.GetCount();
        std::cout << "[Display] IN MODEL: " << cCount.CountofPoints << " points, " << cCount.CountofLines << " lines, " << cCount.CountofFaces << " faces," << std::endl;
        std::cout << "          total length of lines: " << cCount.TotalLength << ", total area of faces: " << cCount.TotalArea << ", " << " Box Volume: " << cCount.BoxVolume << std::endl;
    } 
}

/*************************************************************************
【函数名称】             ExecuteEdit
【函数功能】             执行编辑模式下的指令
【参数】                控制器的引用
【返回值】              无返回值
【开发者及日期】         zheng-y23 2024-8-6
*************************************************************************/
void View::ExecuteEdit(Controller& controller) {
    std::stringstream ssCommand(Command);
    int iID = 0;
    int iPointID = 0;
    double dX[3] = {0};
    double dY[3] = {0};
    double dZ[3] = {0};
    std::string sType;
    try
    {
        ssCommand >> sType;
    }
    catch (const std::exception& e)
    {
        std::cout << "[Error] INVALID COMMAND (Enter 'h' for help)" << std::endl;
        return;
    }
    
    if (sType == "slp")
    {
        ssCommand.str(Command);
        ssCommand >> sType >> iID  >> iPointID >> dX[0] >> dY[0] >> dZ[0];
        if (ssCommand.fail() == 1)
        {
            std::cout << "[Error] INVALID ARGUMENT" << std::endl;
            return;
        }
        Controller::RES rResult = controller.SetLinePoint(iID, iPointID, dX[0], dY[0], dZ[0]);
        switch(rResult)
        {
            case Controller::RES::DONE:
            {
                std::cout << "[Edit] Done" << std::endl;
                break;
            }
            case Controller::RES::ID_OUT_OF_RANGE:
            {
                std::cout << "[Error] ELEMENT DOES NOT EXIST" << std::endl;
                return;
            }
            case Controller::RES::INVALID_COORDINATE:
            {
                std::cout << "[Error] INVALID COORDINATE" << std::endl;
                return;
            }
        }
    }
    else if (sType == "sfp")
    {
        ssCommand.str(Command);
        ssCommand >> sType >> iID  >> iPointID >> dX[0] >> dY[0] >> dZ[0];
        if (ssCommand.fail() == 1)
        {
            std::cout << "[Error] INVALID ARGUMENT" << std::endl;
            return;
        }
        Controller::RES rResult = controller.SetFacePoint(iID, iPointID, dX[0], dY[0], dZ[0]);
        switch(rResult)
        {
            case Controller::RES::DONE:
            {
                std::cout << "[Edit] Done" << std::endl;
                break;
            }
            case Controller::RES::ID_OUT_OF_RANGE:
            {
                std::cout << "[Error] ELEMENT DOES NOT EXIST" << std::endl;
                return;
            }
            case Controller::RES::INVALID_COORDINATE:
            {
                std::cout << "[Error] INVALID COORDINATE (IDENTICAL TO OTHER ELEMENTS)" << std::endl;
                return;
            }
        }

    }
    else if (sType == "al")
    {
        ssCommand.str(Command);
        ssCommand >> sType >> dX[0] >> dY[0] >> dZ[0] >> dX[1] >> dY[1] >> dZ[1];
        if (ssCommand.fail() == 1)
        {
            std::cout << "[Error] INVALID ARGUMENT" << std::endl;
            return;
        }
        Controller::RES rResult = controller.AddLine(dX, dY, dZ);
        if (rResult == Controller::RES::DONE)
        {
            std::cout << "[Edit] Done." << std::endl;
        }
        else if (rResult == Controller::RES::INVALID_COORDINATE)
        {
            std::cout << "[Error] INVALID COORDINATE (IDENTICAL TO OTHER ELEMENTS)" << std::endl;
        }
    }
    else if (sType == "af")
    {
        ssCommand.str(Command);
        ssCommand >> sType >> dX[0] >> dY[0] >> dZ[0] >> dX[1] >> dY[1] >> dZ[1] >> dX[2] >> dY[2] >> dZ[2];
        if (ssCommand.fail() == 1)
        {
            std::cout << "[Error] INVALID ARGUMENT" << std::endl;
            return;
        }
        Controller::RES rResult = controller.AddFace(dX, dY, dZ);
        if (rResult == Controller::RES::DONE)
        {
            std::cout << "[Edit] Done." << std::endl;
        }
        else if (rResult == Controller::RES::INVALID_COORDINATE)
        {
            std::cout << "[Error] INVALID COORDINATE (IDENTICAL TO OTHER ELEMENTS)" << std::endl;
        }
    }
    else if (sType == "dl")
    {
        ssCommand.str(Command);
        ssCommand >> sType >> iID;
        if (ssCommand.fail() == 1)
        {
            std::cout << "[Error] INVALID ARGUMENT" << std::endl;
            return;
        }
        Controller::RES rResult = controller.DeleteLine(iID);
        if (rResult == Controller::RES::DONE)
        {
            std::cout << "[Edit] Done." << std::endl;
        }
        else if (rResult == Controller::RES::ID_OUT_OF_RANGE)
        {
            std::cout << "[Error] LINE " << iID << " DOES NOT EXIST" << std::endl;
            return;
        }
    }
    else if (sType == "df")
    {
        ssCommand.str(Command);
        ssCommand >> sType >> iID;
        if (ssCommand.fail() == 1)
        {
            std::cout << "[Error] INVALID ARGUMENT" << std::endl;
            return;
        }
        Controller::RES rResult = controller.DeleteFace(iID);
        if (rResult == Controller::RES::DONE)
        {
            std::cout << "[Edit] Done." << std::endl;
        }
        else if (rResult == Controller::RES::ID_OUT_OF_RANGE)
        {
            std::cout << "[Error] Face " << iID << " DOES NOT EXIST" << std::endl;
            return;
        }
    }

}

/*************************************************************************
【函数名称】             DisplayUsage
【函数功能】             显示各模式用法
【参数】                无参数
【返回值】              无返回值
【开发者及日期】         zheng-y23 2024-8-6
*************************************************************************/
void View::DisplayUsage() {
    switch(m_State)
    {
        case State::START:
        {
            std::cout << "[help] You could enter 'e' to EDIT the model, or enter 'd' to DISPLAY the model.";
            std::cout << "(enter 'h' for help)" << std::endl;
            break;
        }
        case State::EDIT:
        {
            std::cout << "[help] Under EDIT mode, you could edit points, lines and faces by using commands below:" << std::endl;
            std::cout << "       use 'slp [LineID] [PointID] [X] [Y] [Z]' to set point in lines by ID," << std::endl;
            std::cout << "       use 'sfp [FaceID] [PointID] [X] [Y] [Z]' to set point in faces by ID" << std::endl;
            std::cout << "       use 'al [X1] [Y1] [Z1] [X2] [Y2] [Z2]' to add line with coordinates," << std::endl;
            std::cout << "       use 'af [X1] [Y1] [Z1] [X2] [Y2] [Z2] [X3] [Y3] [Z3]' to add face with coordinates," << std::endl;
            std::cout << "       use 'dl [ID]' to delete line by ID," << std::endl;
            std::cout << "       use 'df [ID]' to delete face by ID" << std::endl;
            break;
        }
        case State::DISPLAY:
        {
            std::cout << "[help] Under DISPLAY mode, you could display points, lines and faces by using commands below:" << std::endl;
            std::cout << "       use 'l [ID]' to display lines by ID," << std::endl;
            std::cout << "       use 'f [ID]' to display faces by ID," << std::endl;
            std::cout << "       use 'i' to display information of the model," << std::endl;
            std::cout << "       or just use 'l' or 'f' to display all lines or faces." << std::endl;
            break;
        }
    }
}
