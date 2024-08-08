/*************************************************************************
【文件名】               Group.hpp
【功能模块和目的】        实现大小、类型可变的“组”类模版
【开发者及日期】          zheng-y23 2024-7-27
*************************************************************************/

#pragma once

#include<vector>
#include <iostream>

/*************************************************************************
【类名】                 Group
【功能】                 “组”类模版
【接口说明】              构建元素的“组”，实现对元素的添加、修改、查找、删除
                         virtual void AddElement(T element);
                         void DeleteElement(T element);
                         void DeleteElement(int Index);
                         virtual void SetElement(int Index, T element);
                         size_t Find(T element);
【开发者及日期】          zheng-y23 2024-7-27
*************************************************************************/
template <class T>
class Group {
public:
    //构造函数
    Group();
    Group(const Group& Source);
    //析构函数
    ~Group();
    //赋值运算符重载
    Group& operator= (const Group& Source);
    //下标运算符重载
    T operator[] (int Index) const;
    //添加、删除、修改元素（虚函数）
    virtual void AddElement(T element);
    void DeleteElement(T element);
    void DeleteElement(int Index);
    virtual void SetElement(int Index, T element);
    //查找元素并返回下标
    size_t Find(T element);
private:
    std::vector<T> m_Group;
    unsigned int m_Size {0};
public:
    //获取大小
    const unsigned int& Size {m_Size};
    //获取迭代器
    typename std::vector<T>::iterator Begin();
    typename std::vector<T>::iterator End();
};

/*************************************************************************
【函数名称】                Group
【函数功能】                默认构造函数
【参数】                    无参数
【返回值】                  无返回值
【开发者及日期】            zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Group<T>::Group() {
    //空函数体
}

/*************************************************************************
【函数名称】                Group
【函数功能】                拷贝构造函数
【参数】                    Group常引用Source
【返回值】                  无返回值
【开发者及日期】            zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Group<T>::Group(const Group& Source) {
    for (int i = 0; i < Source.Size; i++)
    {
        m_Group.push_back(Source[i]);
    }
    m_Size = Source.Size;
}

/*************************************************************************
【函数名称】                ~Group
【函数功能】                析构函数
【参数】                    无参数
【返回值】                  无返回值
【开发者及日期】            zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Group<T>::~Group() {
    //空函数体
}

/*************************************************************************
【函数名称】                operator=
【函数功能】                赋值运算符重载
【参数】                    Group常引用Source
【返回值】                  赋值后对象
【开发者及日期】            zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Group<T>& Group<T>::operator= (const Group& Source) {
    if (this != &Source)
    {   
        m_Size = Source.Size;
        m_Group.clear();
        for (int i = 0; i < Source.Size; i++)
        {
            m_Group.push_back(Source[i]);
        }
    }
    return *this;
}

/*************************************************************************
【函数名称】                operator[]
【函数功能】                下标运算符重载
【参数】                    下标Index
【返回值】                  下标对应值
【开发者及日期】            zheng-y23 2024-7-27
*************************************************************************/
template <class T>
T Group<T>::operator[] (int Index) const {
    return m_Group[Index];
}

/*************************************************************************
【函数名称】                AddElement
【函数功能】                添加元素
【参数】                    要添加的元素
【返回值】                  无返回值
【开发者及日期】            zheng-y23 2024-7-27
*************************************************************************/
template <class T>
void Group<T>::AddElement(T element) {
    m_Group.push_back(element);
    m_Size += 1;
}

/*************************************************************************
【函数名称】                DeleteElement
【函数功能】                删除元素
【参数】                    要删除的元素
【返回值】                  无返回值
【开发者及日期】            zheng-y23 2024-7-27
*************************************************************************/
template <class T>
void Group<T>::DeleteElement(T element) {
    for (int i = 0; i < Size; i++)
    {
        if (operator[](i) == element)
        {
            typename std::vector<T>::iterator iter = m_Group.begin() + i;
            m_Group.erase(iter);
            m_Size -= 1;
        }
    }
}

/*************************************************************************
【函数名称】                DeleteElement
【函数功能】                删除元素
【参数】                    要删除元素的下标
【返回值】                  无返回值
【开发者及日期】            zheng-y23 2024-7-27
*************************************************************************/
template <class T>
void Group<T>::DeleteElement(int Index) {
    m_Group.erase(m_Group.begin() + Index);
    m_Size -= 1;
}

/*************************************************************************
【函数名称】                SetElement
【函数功能】                修改元素
【参数】                    无参数
【返回值】                  无返回值
【开发者及日期】            zheng-y23 2024-7-27
*************************************************************************/
template <class T>
void Group<T>::SetElement(int Index, T element) {
    if (Index < m_Size)
    {
        m_Group[Index] = element;
    }
}

/*************************************************************************
【函数名称】                Find
【函数功能】                查找元素
【参数】                    要查找的元素
【返回值】                  若存在，返回元素的下标；若不存在，返回Group的大小
【开发者及日期】            zheng-y23 2024-7-27
*************************************************************************/
template <class T>
size_t Group<T>::Find(T element) {
    size_t Index = Size;
    for (int i = 0; i < Size; i++)
    {
        if (m_Group[i] == element)
        {
            Index = i;
        }
    }
    return Index;
}

/*************************************************************************
【函数名称】                Begin
【函数功能】                获取begin()迭代器
【参数】                    无参数
【返回值】                  begin()迭代器
【开发者及日期】            zheng-y23 2024-7-27
*************************************************************************/
template <class T>
typename std::vector<T>::iterator Group<T>::Begin() {
    return m_Group.begin();
}

/*************************************************************************
【函数名称】                End
【函数功能】                获取end()迭代器
【参数】                    无参数
【返回值】                  end()迭代器
【开发者及日期】            zheng-y23 2024-7-27
*************************************************************************/
template <class T>
typename std::vector<T>::iterator Group<T>::End() {
    return m_Group.end();
}