/*************************************************************************
View.cpp
界面类的具体实现
zheng-y23 2024-8-5
*************************************************************************/

#include "View.hpp"
#include <sstream>
#include <iomanip>

/*************************************************************************
GetInstance
获取唯一对象（单例模式）
无参数
界面类的唯一对象
zheng-y23 2024-8-5
*************************************************************************/
View& View::GetInstance() {
    static View view;
    return view;
}

/*************************************************************************
Start
开启所有程序
控制器的引用
无返回值
zheng-y23 2024-8-6
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
LoadFile
读入用户提供的文件
控制器的引用
无返回值
zheng-y23 2024-8-6
*************************************************************************/
void View::LoadFile(Controller& controller) {
    std::cout << "> Please enter the FILE PATH: ";
    std::string FilePath;
    std::getline(std::cin, FilePath);
    if (FilePath == "q")
    {
        exit(0);
    }
    Controller::RES Result = controller.ReadModel(FilePath);
    if (Result == Controller::RES::READ_FILE_FAILURE)
    {
        while(controller.ReadModel(FilePath) != Controller::RES::DONE)
        {
            std::cout << "> Invalid FILE PATH! Please enter again: ";
            std::getline(std::cin, FilePath);
            if (FilePath == "q")
            {
                exit(0);
            }
        }
    }
    std::cout << "> Done." << std::endl;
}

/*************************************************************************
SaveFile
将模型信息保存到用户提供的路径
控制器的引用
无返回值
zheng-y23 2024-8-6
*************************************************************************/
void View::SaveFile(Controller& controller) {
    std::string IfSave;
    std::cout << "> Do you want to SAVE the changes to the model? (enter y/n) ";
    std::cin >> IfSave;
    if (IfSave == "y")
    {
        std::string Path;
        std::cout << "> Where would you like to save (FILE PATH):  ";
        std::cin >> Path;
        Controller::RES Result = controller.WriteModel(Path);
        if (Result == Controller::RES::DONE)
        {
            std::cout << "> Done." << std::endl;
            std::cout << "====================================================SEE YOU NEXT TIME================================================================" << std::endl;
            exit(0);
        }
        else if (Result == Controller::RES::WRITE_FILE_FAILURE)
        {
            std::cout << "[Error] INVALID FILE PATH" << std::endl;
            return;
        }
    }
    else if (IfSave == "n")
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
LoadCommand
从用户输入中获取指令
无参数
无返回值
zheng-y23 2024-8-6
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
ExecuteCommand
执行读入的指令
控制器的引用
无返回值
zheng-y23 2024-8-6
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
ExecuteDisplay
执行展示模式下的指令
控制器的引用
无返回值
zheng-y23 2024-8-6
*************************************************************************/
void View::ExecuteDisplay(Controller& controller) {
    std::stringstream command(Command);
    std::string type;
    int ID;
    Line3D Line;
    Face3D Face;
    Controller::CountOfElements count = controller.GetCount();

    command >> type;
    if (command.fail() == 1)
    {
        std::cout << "[Error] INVALID COMMAND (enter 'h' for help)" << std::endl;
        return; 
    }

    if (Command == "l")
    {   
        size_t LineID;
        std::cout << "[Display] ";
        if (count.CountofLines == 0)
        {
            std::cout << "NO LINES IN MODEL" << std::endl;
            return;
        }
        for (int i = 0; i < count.CountofLines; i++)
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
        if (count.CountofFaces == 0)
        {
            std::cout << "NO FACES IN MODEL" << std::endl;
            return;
        }
        for (int i = 0; i < count.CountofFaces; i++)
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
        command.str(Command);
        command >> type >> ID;
        if (command.fail() == 1)
        {
            std::cout << "[Error] INVALID ARGUMENT" << std::endl;
            return;
        }
        Controller::RES Result = controller.GetLine(ID, &Line);
        if (Result == Controller::RES::ID_OUT_OF_RANGE)
        {
            std::cout << "[Error] ";
            std::cout << "LINE " << ID << " DOES NOT EXIST" << std::endl;
            return; 
        }
        std::cout << "[Display] ";
        std::cout << Line << std::endl;
    }
    else if (Command[0] == 'f')
    {
        command.str(Command);
        command >> type >> ID;
        bool IfExist = 0;
        if (command.fail() == 1)
        {
            std::cout << "[Error] INVALID ARGUMENT" << std::endl;
            return;
        }
        Controller::RES Result = controller.GetFace(ID, &Face);
        if (Result == Controller::RES::ID_OUT_OF_RANGE)
        {
            std::cout << "[Error] ";
            std::cout << "FACE " << ID << " DOES NOT EXIST" << std::endl;
            return;
        }
        std::cout << "[Display] ";
        std::cout << Face << std::endl;
    }
    else if (Command == "i")
    {
        Controller::CountOfElements count = controller.GetCount();
        std::cout << "[Display] IN MODEL: " << count.CountofPoints << " points, " << count.CountofLines << " lines, " << count.CountofFaces << " faces," << std::endl;
        std::cout << "          total length of lines: " << count.TotalLength << ", total area of faces: " << count.TotalArea << ", " << " Box Volume: " << count.BoxVolume << std::endl;
    } 
}

/*************************************************************************
ExecuteEdit
执行编辑模式下的指令
控制器的引用
无返回值
zheng-y23 2024-8-6
*************************************************************************/
void View::ExecuteEdit(Controller& controller) {
    std::stringstream command(Command);
    int ID;
    int PointID;
    double X[3];
    double Y[3];
    double Z[3];
    std::string type;
    try
    {
        command >> type;
    }
    catch (const std::exception& e)
    {
        std::cout << "[Error] INVALID COMMAND (Enter 'h' for help)" << std::endl;
        return;
    }
    
    if (type == "slp")
    {
        command.str(Command);
        command >> type >> ID  >> PointID >> X[0] >> Y[0] >> Z[0];
        if (command.fail() == 1)
        {
            std::cout << "[Error] INVALID ARGUMENT" << std::endl;
            return;
        }
        Controller::RES Result = controller.SetLinePoint(ID, PointID, X[0], Y[0], Z[0]);
        switch(Result)
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
    else if (type == "sfp")
    {
        command.str(Command);
        command >> type >> ID  >> PointID >> X[0] >> Y[0] >> Z[0];
        if (command.fail() == 1)
        {
            std::cout << "[Error] INVALID ARGUMENT" << std::endl;
            return;
        }
        Controller::RES Result = controller.SetFacePoint(ID, PointID, X[0], Y[0], Z[0]);
        switch(Result)
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
    else if (type == "al")
    {
        command.str(Command);
        command >> type >> X[0] >> Y[0] >> Z[0] >> X[1] >> Y[1] >> Z[1];
        if (command.fail() == 1)
        {
            std::cout << "[Error] INVALID ARGUMENT" << std::endl;
            return;
        }
        Controller::RES Result = controller.AddLine(X, Y, Z);
        if (Result == Controller::RES::DONE)
        {
            std::cout << "[Edit] Done." << std::endl;
        }
        else if (Result == Controller::RES::INVALID_COORDINATE)
        {
            std::cout << "[Error] INVALID COORDINATE (IDENTICAL TO OTHER ELEMENTS)" << std::endl;
        }
    }
    else if (type == "af")
    {
        command.str(Command);
        command >> type >> X[0] >> Y[0] >> Z[0] >> X[1] >> Y[1] >> Z[1] >> X[2] >> Y[2] >> Z[2];
        if (command.fail() == 1)
        {
            std::cout << "[Error] INVALID ARGUMENT" << std::endl;
            return;
        }
        Controller::RES Result = controller.AddFace(X, Y, Z);
        if (Result == Controller::RES::DONE)
        {
            std::cout << "[Edit] Done." << std::endl;
        }
        else if (Result == Controller::RES::INVALID_COORDINATE)
        {
            std::cout << "[Error] INVALID COORDINATE (IDENTICAL TO OTHER ELEMENTS)" << std::endl;
        }
    }
    else if (type == "dl")
    {
        command.str(Command);
        command >> type >> ID;
        if (command.fail() == 1)
        {
            std::cout << "[Error] INVALID ARGUMENT" << std::endl;
            return;
        }
        Controller::RES Result = controller.DeleteLine(ID);
        if (Result == Controller::RES::DONE)
        {
            std::cout << "[Edit] Done." << std::endl;
        }
        else if (Result == Controller::RES::ID_OUT_OF_RANGE)
        {
            std::cout << "[Error] LINE " << ID << " DOES NOT EXIST" << std::endl;
            return;
        }
    }
    else if (type == "df")
    {
        command.str(Command);
        command >> type >> ID;
        if (command.fail() == 1)
        {
            std::cout << "[Error] INVALID ARGUMENT" << std::endl;
            return;
        }
        Controller::RES Result = controller.DeleteFace(ID);
        if (Result == Controller::RES::DONE)
        {
            std::cout << "[Edit] Done." << std::endl;
        }
        else if (Result == Controller::RES::ID_OUT_OF_RANGE)
        {
            std::cout << "[Error] Face " << ID << " DOES NOT EXIST" << std::endl;
            return;
        }
    }

}

/*************************************************************************
DisplayUsage
显示各模式用法
无参数
无返回值
zheng-y23 2024-8-6
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
