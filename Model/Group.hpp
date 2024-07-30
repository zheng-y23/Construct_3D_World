/*************************************************************************
Group.hpp
实现大小、类型可变的“组”类模版
zheng-y23 2024-7-27
*************************************************************************/

#pragma once

#include<vector>

/*************************************************************************
Group
“组”类模版
类型T
zheng-y23 2024-7-27
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
Group
默认构造函数
无参数
无返回值
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Group<T>::Group() {
    //空函数体
}

/*************************************************************************
Group
拷贝构造函数
Group常引用Source
无返回值
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Group<T>::Group(const Group& Source) {
    for (int i = 0; i < Size; i++)
    {
        m_Group.push_back(Source[i]);
    }
}

/*************************************************************************
~Group
析构函数
无参数
无返回值
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Group<T>::~Group() {
    //空函数体
}

/*************************************************************************
operator=
赋值运算符重载
Group常引用Source
赋值后对象
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
Group<T>& Group<T>::operator= (const Group& Source) {
    if (this != &Source)
    {   
        if (Size >= Source.Size)
        {
            int i = 0;
            for (i = 0; i < Source.Size; i++)
            {
                m_Group[i] = Source[i];
            }
            while (i < Source.Size)
            {
                m_Group.pop_back();
            }
        }

    }
    return *this;
}

/*************************************************************************
operator[]
下标运算符重载
下标Index
下标对应值
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
T Group<T>::operator[] (int Index) const {
    return m_Group[Index];
}

/*************************************************************************
AddElement
添加元素
要添加的元素
无返回值
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
void Group<T>::AddElement(T element) {
    m_Group.push_back(element);
    m_Size += 1;
}

/*************************************************************************
DeleteElement
删除元素
要删除的元素
无返回值
zheng-y23 2024-7-27
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
DeleteElement
删除元素
要删除元素的下标
无返回值
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
void Group<T>::DeleteElement(int Index) {
    m_Group.erase(m_Group.begin() + Index);
}

/*************************************************************************
SetElement
修改元素
无参数
无返回值
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
void Group<T>::SetElement(int Index, T element) {
    if (Index < Size)
    {
        m_Group[Index] = element;
    }
}

/*************************************************************************
Find
查找元素
要查找的元素
若存在，返回元素的下标；若不存在，返回Group的大小
zheng-y23 2024-7-27
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
Begin
获取begin()迭代器
无参数
begin()迭代器
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
typename std::vector<T>::iterator Group<T>::Begin() {
    return m_Group.begin();
}

/*************************************************************************
End
获取end()迭代器
无参数
end()迭代器
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
typename std::vector<T>::iterator Group<T>::End() {
    return m_Group.end();
}