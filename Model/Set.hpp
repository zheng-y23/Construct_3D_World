/*************************************************************************
【文件名】                Set.hpp
【功能模块和目的】         实现大小、类型可变的集合类模版
【开发者及日期】           zheng-y23 2024-7-27
*************************************************************************/

#pragma once

#include "Group.hpp"
#include <iostream>

/*************************************************************************
【类名】                   Set
【功能】                   集合类模版
【接口说明】               继承Group类，构建集合类模版，实现集合的添加、修改元素以及交并补运算
                           virtual void AddElement(T element);
                           virtual void SetELement(int Index, T element);
                           Set Intersection(const Set& Source);
                           Set Union(const Set& Source);
                           Set Difference(const Set& Source);
【开发者及日期】             zheng-y23 2024-7-27
*************************************************************************/
template <class T>
class Set : public Group<T> {
public:
    //构造函数
    Set();
    Set(const Set& Source);
    //析构函数
    ~Set();
    //赋值运算符重载
    Set& operator= (const Set& Source);
    //下标运算符重载
    T operator[] (unsigned int Index) const;
    //添加、修改元素
    virtual void AddElement(T element);
    virtual void SetELement(unsigned int Index, T element);
    //求集合的交集、并集、差集
    Set Intersection(const Set& Source);
    Set Union(const Set& Source);
    Set Difference(const Set& Source);
private:
    unsigned int m_Size;
public:
    const unsigned int& Size {m_Size};
};

/*************************************************************************
【函数名称】                Set
【函数功能】                默认构造函数
【参数】                    无参数
【返回值】                  无返回值
【开发者及日期】             zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Set<T>::Set() {
    m_Size = 0;
}

/*************************************************************************
【函数名称】                Set
【函数功能】                拷贝构造函数
【参数】                    Set类型常引用Source
【返回值】                  无返回值
【开发者及日期】            zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Set<T>::Set(const Set& Source) : Group<T>(Source) {
    m_Size = Source.Size;
}

/*************************************************************************
【函数名称】                ~Set
【函数功能】                析构函数
【参数】                    无参数
【返回值】                  无返回值
【开发者及日期】            zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Set<T>::~Set() {
    //空函数体
}

/*************************************************************************
【函数名称】                operator=
【函数功能】                赋值运算符重构
【参数】                    Set类型常引用Source
【返回值】                  赋值后对象
【开发者及日期】             zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Set<T>& Set<T>::operator= (const Set& Source) {
    if (this != &Source)
    {
        Group<T>::operator= (Source);
        m_Size = Source.Size;
    }
    return *this;
}

/*************************************************************************
【函数名称】                 operator[]
【函数功能】                下标运算符重构
【参数】                    下标
【返回值】                  下标对应的元素
【开发者及日期】             zheng-y23 2024-7-27
*************************************************************************/
template <class T>
T Set<T>::operator[] (unsigned int Index) const{
    if (Index >= m_Size)
    {
        throw std::out_of_range("Index out of range");
    }
    return Group<T>::operator[](Index);
}

/*************************************************************************
【函数名称】                 AddElement
【函数功能】                添加元素（互不重复）
【参数】                    要添加的元素
【返回值】                  无返回值
【开发者及日期】             zheng-y23 2024-7-27
*************************************************************************/
template <class T>
void Set<T>::AddElement(T element) {
    bool b_IfnExist = 1;
    for (int i = 0; i < m_Size; i++)
    {
        if (Group<T>::operator[](i) == element)
        {
            b_IfnExist *= 0;
            break;
        }
    }
    if (b_IfnExist == 1)
    {
        Group<T>::AddElement(element);
        m_Size += 1;
    }
}

/*************************************************************************
【函数名称】                 SetElement
【函数功能】                设置元素（互不重复）
【参数】                    要设置的元素及其下标
【返回值】                  无返回值
【开发者及日期】             zheng-y23 2024-7-27
*************************************************************************/
template <class T>
void Set<T>::SetELement(unsigned int Index, T element) {
    bool b_IfExist = 1;
    for (int i = 0; i < m_Size; i++)
    {
        b_IfExist *= operator[](i) == element;
    }
    if (b_IfExist != 1)
    {
        Group<T>::SetElement(Index, element);
    }
}

/*************************************************************************
【函数名称】                 Intersection
【函数功能】                求集合的交集
【参数】                    集合Source
【返回值】                  返回两集合的交集
【开发者及日期】             zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Set<T> Set<T>::Intersection(const Set& Source) {
    Set<T> s_Result;
    for (int i = 0; i < m_Size; i++)
    {
        for (int j = 0; j < Source.Size; j++)
        {
            if (operator[](i) == Source[j])
            {
                s_Result.AddElement(Source[j]);
            }
        }
    }
    return s_Result;
}

/*************************************************************************
【函数名称】                 Union
【函数功能】                求集合的并集
【参数】                    集合Source
【返回值】                  返回两集合的并集
【开发者及日期】             zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Set<T> Set<T>::Union(const Set& Source) {
    Set<T> s_Result = Source;
    for (int i = 0; i < Group<T>::Size; i++)
    {
        s_Result.AddElement(operator[](i));
    }
    return s_Result;
}

/*************************************************************************
【函数名称】                 Difference
【函数功能】                求集合的差集
【参数】                    集合Source
【返回值】                  返回两集合的差集
【开发者及日期】             zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Set<T> Set<T>::Difference(const Set& Source) {
    Set<T> s_Result;
    for (int i = 0; i < m_Size; i++)
    {
        if (Group<T>::Find(operator[](i)) != Group<T>::Size && Source.Find(operator[](i)) == Source.Size)
        {
            s_Result.AddElement(operator[](i));
        }
    }
    return s_Result;
}