/*************************************************************************
【文件名】            CountFixedSet.hpp
【功能模块和目的】     实现类型可变但元素只能修改的集合类模版
【开发者及日期】       zheng-y23 2024-7-27
*************************************************************************/

#pragma once

#include "Set.hpp"

/*************************************************************************
【类名】              CountFixedSet
【功能】              元素只能修改的集合类模版
【接口说明】           继承Set类，实现对元素的修改，隐藏了增加或减少元素的接口
【开发者及日期】       zheng-y23 2024-7-27
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
    T operator[] (unsigned int Index) const;
private:
    unsigned int m_Size;
    //隐藏增加、减少元素的接口
    using Set<T>::AddElement;
    using Set<T>::DeleteElement;
public:
    const unsigned int& Size {m_Size};
};

/*************************************************************************
【函数名称】                  CountFixedSet
【函数功能】                  默认构造函数
【参数】                      无参数
【返回值】                    无返回值
【开发者及日期】               zheng-y23 2024-7-27
*************************************************************************/
template <class T>
CountFixedSet<T>::CountFixedSet() {
    //空函数体
}

/*************************************************************************
【函数名称】                  CountFixedSet
【函数功能】                  构造函数
【参数】                      元素的数组和数组大小
【返回值】                    无返回值
【开发者及日期】               zheng-y23 2024-7-27
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
【函数名称】                  CountFixedSet
【函数功能】                  拷贝构造函数
【参数】                      CountFixedSet常引用Source
【返回值】                    无返回值
【开发者及日期】               zheng-y23 2024-7-29
*************************************************************************/
template <class T>
CountFixedSet<T>::CountFixedSet(const CountFixedSet& Source) : Set<T>(Source) {
    m_Size = Source.Size;
}

/*************************************************************************
【函数名称】                  ~CountFixedSet
【函数功能】                  析构函数
【参数】                      无参数
【返回值】                    无返回值
【开发者及日期】               zheng-y23 2024-7-27
*************************************************************************/
template <class T>
CountFixedSet<T>::~CountFixedSet() {
    //空函数体
}

/*************************************************************************
【函数名称】                  operator=
【函数功能】                  赋值运算符重载
【参数】                      CountFixedSet类型常引用Source
【返回值】                    返回赋值后对象
【开发者及日期】               zheng-y23 2024-7-27
*************************************************************************/
template <class T>
CountFixedSet<T>& CountFixedSet<T>::operator= (const CountFixedSet& Source) {
    if (this != &Source)
    {
        m_Size = Source.Size;
        Set<T>::operator=(Source);
    }
    return *this;
}

/*************************************************************************
【函数名称】                  operator[]
【函数功能】                  下标运算符重载
【参数】                      下标
【返回值】                    下标对应的元素
【开发者及日期】               zheng-y23 2024-7-27
*************************************************************************/
template <class T>
T CountFixedSet<T>::operator[] (unsigned int Index) const {
    if (Index >= m_Size)
    {
        throw std::out_of_range("Index out of range");
    }
    return Set<T>::operator[](Index);
}
