/*************************************************************************
CountFixedSet.hpp
实现类型可变但元素只能修改的集合类模版
zheng-y23 2024-7-27
*************************************************************************/

#pragma once

#include "Set.hpp"

/*************************************************************************
CountFixedSet
元素只能修改的集合类模版
类型T
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
class CountFixedSet : public Set<T> {
public:
    //构造函数
    CountFixedSet();
    CountFixedSet(T* elements, unsigned int Size);
    CountFixedSet(const CountFixedSet& Source);
    //析构函数
    ~CountFixedSet();
    //赋值运算符重载
    CountFixedSet& operator= (const CountFixedSet& Source);
    //下标运算符重载
    T operator[] (int Index) const;
private:
    unsigned int m_Size;
    //隐藏增加、减少元素的接口
    using Set<T>::AddElement;
    using Set<T>::DeleteElement;
public:
    const unsigned int& Size {m_Size};
};

/*************************************************************************
CountFixedSet
默认构造函数
无参数
无返回值
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
CountFixedSet<T>::CountFixedSet() {
    //空函数体
}

/*************************************************************************
CountFixedSet
构造函数
元素的数组和数组大小
无返回值
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
CountFixedSet<T>::CountFixedSet(T* elements, unsigned int Size) {
    for (int i = 0; i < Size; i++)
    {
        Set<T>::AddElement(elements[i]);
    }
    m_Size = Size;
}

/*************************************************************************
CountFixedSet
拷贝构造函数
CountFixedSet常引用Source
无返回值
zheng-y23 2024-7-29
*************************************************************************/
template <class T>
CountFixedSet<T>::CountFixedSet(const CountFixedSet& Source) : Set<T>(Source) {
    m_Size = Source.Size;
}

/*************************************************************************
~CountFixedSet
析构函数
无参数
无返回值
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
CountFixedSet<T>::~CountFixedSet() {
    //空函数体
}

/*************************************************************************
operator=
赋值运算符重载
CountFixedSet类型常引用Source
返回赋值后对象
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
CountFixedSet<T>& CountFixedSet<T>::operator= (const CountFixedSet& Source) {
    if (this != &Source)
    {
        m_Size = Source.Size;
        Set<T>::operator=(Source);
    }
    std::cout << "CountFixedSet using" << std::endl;
    //std::cout << "In CountFixedSet: " << Set<T>::operator[](0).X << std::endl;
    std::cout << "CountFixedSet operator= used" << std::endl;
    return *this;
}

/*************************************************************************
operator[]
下标运算符重载
下标
下标对应的元素
zheng-y23 2024-7-27
*************************************************************************/
template <class T>
T CountFixedSet<T>::operator[] (int Index) const {
    return Set<T>::operator[](Index);
}