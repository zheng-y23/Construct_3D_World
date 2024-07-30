/*************************************************************************
Set.hpp
实现大小、类型可变的集合类模版
zheng-y23 2024-7-27
*************************************************************************/

#pragma once

#include "Group.hpp"
#include <iostream>

/*************************************************************************
Set
集合类模版
类型T
zheng-y23 2024-7-27
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
    T operator[] (int Index) const;
    //添加、修改元素
    virtual void AddElement(T element);
    virtual void SetELement(int Index, T element);
    //求集合的交集、并集、差集
    Set Intersection(const Set& Source);
    Set Union(const Set& Source);
    Set Difference(const Set& Source);
};

/*************************************************************************
Set
默认构造函数
无参数
无返回值
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Set<T>::Set() {
    //空函数体
}

/*************************************************************************
Set
拷贝构造函数
Set类型常引用Source
无返回值
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Set<T>::Set(const Set& Source) : Group<T>(Source) {
    //空函数体
}

/*************************************************************************
~Set
析构函数
无参数
无返回值
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Set<T>::~Set() {
    //空函数体
}

/*************************************************************************
operator=
赋值运算符重构
Set类型常引用Source
赋值后对象
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Set<T>& Set<T>::operator= (const Set& Source) {
    if (this != &Source)
    {
        Group<T>::operator= (Source);
    }
    return *this;
}

/*************************************************************************
operator[]
下标运算符重构
下标
下标对应的元素
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
T Set<T>::operator[] (int Index) const{
    return Group<T>::operator[](Index);
}

/*************************************************************************
AddElement
添加元素（互不重复）
要添加的元素
无返回值
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
void Set<T>::AddElement(T element) {
    Group<T>::AddElement(element);
    int Number = 0;
    for (auto iter = Group<T>::Begin(); iter != Group<T>::End(); ++iter)
    {
        if (*iter == element)
        {
            Number += 1;
        }
    }
    if (Number == 2)
    {
        Group<T>::DeleteElement(Group<T>::Size - 1);
    }
}

/*************************************************************************
SetElement
设置元素（互不重复）
要设置的元素及其下标
无返回值
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
void Set<T>::SetELement(int Index, T element) {
    Group<T>::SetElement(Index, element);
    int Number = 0;
    for (int i = 0; i < Group<T>::Size; i++)
    {   
        if (Group<T>::operator[](i) == element)
        {
            Number += 1;
        }
    }
    if (Number == 2)
    {
        Group<T>::DeleteElement(Index);
    }
}

/*************************************************************************
Intersection
求集合的交集
集合Source
返回两集合的交集
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Set<T> Set<T>::Intersection(const Set& Source) {
    Set<T> Result;
    for (int i = 0; i < Group<T>::Size; i++)
    {
        for (int j = 0; j < Source.Size; j++)
        {
            if (operator[](i) == Source[j])
            {
                Result.AddElement(Source[j]);
            }
        }
    }
    return Result;
}

/*************************************************************************
Union
求集合的并集
集合Source
返回两集合的并集
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Set<T> Set<T>::Union(const Set& Source) {
    Set<T> Result = Source;
    for (auto iter = Group<T>::Begin(); iter != Group<T>::End(); ++iter)
    {
        Result.AddElement(*iter);
    }
    return Result;
}

/*************************************************************************
Difference
求集合的差集
集合Source
返回两集合的差集
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Set<T> Set<T>::Difference(const Set& Source) {
    Set<T> Result;
    for (auto iter = Group<T>::Begin(); iter != Group<T>::End(); ++iter)
    {
        if (Find(*iter) != Group<T>::Size && Source.Find(*iter) == Source.Size)
        {
            Result.AddElement(*iter);
        }
    }
    return Result;
}