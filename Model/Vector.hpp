/*************************************************************************
Vector.hpp
实现不同维数、类型的向量类模版
zheng-y23 2024-7-26
*************************************************************************/

#pragma once

#include <iostream>
#include <cmath>

/*************************************************************************
Vector<T, N>
N维T类型的向量类模版
维数N和类型T
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
class Vector {
public:
    //构造函数
    Vector();
    Vector(const Vector& Source);
    //析构函数
    virtual ~Vector();
    //设置坐标
    void SetComponent(const T* Components);
    //赋值运算符重载
    Vector& operator= (const Vector& Source);
    //加法、减法运算符重载
    Vector& operator+ (const Vector& Source) const;
    Vector& operator+= (const Vector& Source) const;
    Vector& operator- (const Vector& Source) const;
    Vector& operator-= (const Vector& Source) const;
    //下标运算符重载 
    T operator[] (size_t Index) const;
    //外积运算
    Vector& operator* (const Vector& Source) const;
    Vector& operator*= (const Vector& Source) const;
    //向量的数乘
    Vector& operator* (T Source) const;
    //向量的范数
    T L0() const;
    T L1() const;
    T L2() const;
    T Lp(unsigned int p) const;
    T Lmax() const;
    //给出p范数实现（纯虚函数）
    virtual T InnerL(unsigned int p) const;
    //求叉乘结果
    Vector& CrossProduct(const Vector& Source);
    virtual Vector InnerCrossProduct(const Vector& Source); 
    //等于和不等于运算符重载
    bool operator== (const Vector& Source) const;
    bool operator!= (const Vector& Source) const;
    //求向量的模（也即2-范数）
    T Module() const;
private:
    T m_Component [N];
public:
    static constexpr size_t Dimension {N};
    const T* Component {m_Component};
};

/*************************************************************************
Vector
默认构造函数
无参数
无返回值
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
Vector<T, N>::Vector() {
    //空函数体
}

/*************************************************************************
Vector
拷贝构造函数
Vector常引用Source
无返回值
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
Vector<T, N>::Vector(const Vector& Source) {
    for (int i = 0; i < N; i++) 
    {
        m_Component[i] = Source.Component[i];
    }
}

/*************************************************************************
~Vector
析构函数
无参数
无返回值
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
Vector<T, N>::~Vector() {
    //空函数体
}

/*************************************************************************
SetComponent
设置坐标
坐标数组
无返回值
zheng-y23 2024-7-27
*************************************************************************/
template<class T, size_t N>
void Vector<T, N>::SetComponent(const T* Components) {
    for (int i = 0; i < N; i++)
    {
        m_Component[i] = Components[i];
    }
}

/*************************************************************************
operator=
赋值运算符重载
Vector常引用Source
赋值后对象
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
Vector<T, N>& Vector<T, N>::operator= (const Vector& Source) {
    if (this != &Source) {
        for (int i = 0; i < N; i++)
        {
            m_Component[i] = Source.Component[i];
        }
    }
    return *this;
}

/*************************************************************************
operator+
加法运算符重载
Vector常引用Source
相加后对象
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
Vector<T, N>& Vector<T, N>::operator+ (const Vector& Source) const {
    for (int i = 0; i < N; i++)
    {
        m_Component[i] += Source.Component[i];
    }
    return *this;
}

/*************************************************************************
operator+=
加等于运算符重载
Vector常引用Source
相加后对象
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
Vector<T, N>& Vector<T, N>::operator+= (const Vector& Source) const {
    for (int i = 0; i < N; i++)
    {
        m_Component[i] += Source.Component[i];
    }
    return *this;
}

/*************************************************************************
operator-
减法运算符重载
Vector常引用Source
相减后对象
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
Vector<T, N>& Vector<T, N>::operator- (const Vector& Source) const {
    for (int i = 0; i < N; i++)
    {
        m_Component[i] -= Source.Component[i];
    }
    return *this;
}

/*************************************************************************
operator-=
减等于运算符重载
Vector常引用Source
相减后对象
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
Vector<T, N>& Vector<T, N>::operator-= (const Vector& Source) const {
    for (int i = 0; i < N; i++)
    {
        m_Component[i] -= Source.Component[i];
    }
    return *this;
}

/*************************************************************************
operator[]
下标运算符重载
下标
数组中下标对应的数据
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
T Vector<T, N>::operator[] (size_t Index) const {
    return m_Component[Index];
}

/*************************************************************************
operator*
计算向量外积
Vector常引用Source
向量外积
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
Vector<T, N>& Vector<T, N>::operator* (const Vector& Source) const {
    return CrossProduct(Source);
}

/*************************************************************************
operator*=
计算向量外积
Vector常引用Source
向量外积
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
Vector<T, N>& Vector<T, N>::operator*= (const Vector& Source) const {
    return CrossProduct(Source);
}

/*************************************************************************
operator*
计算向量数乘
T类型Source
数乘后的向量
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
Vector<T, N>& Vector<T, N>::operator* (T Source) const {
    for (int i = 0; i < N; i++)
    {
        m_Component[i] *= Source;
    }
    return *this;
}

/*************************************************************************
L0
计算向量的0-范数
无参数
向量的0-范数
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
T Vector<T, N>::L0() const {
    T Result0 = 0;
    if (m_Component[0] != 0)
    {
        Result0 += 1;
    }
    for (int i = 1; i < N; i++) 
    {
        int flag = 0;
        for (int j = 0; j < i; j++)
        {
            if (m_Component[j] == m_Component[i])
            {
                flag = 0;
            }
        }
        if (flag == 1 && m_Component[i] != 0)
        {
            Result0 += 1;
        }
    }
    return Result0;
}

/*************************************************************************
L1
计算向量的1-范数
无参数
向量的1-范数
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
T Vector<T, N>::L1() const {
    T Result1 = 0;
    for (int i = 0; i < N; i++)
    {
        Result1 += std::abs(m_Component[i]);
    }
    return Result1;
}

/*************************************************************************
L2
计算向量的2-范数
无参数
向量的2-范数
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
T Vector<T, N>::L2() const {
    T Result2 = 0;
    for (int i = 0; i < N; i++)
    {
        Result2 += pow(m_Component[i], 2);
    }
    return sqrt(Result2);
}

/*************************************************************************
Lp
计算向量的p-范数
无参数
向量的p-范数
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
T Vector<T, N>::Lp(unsigned int p) const {
    return InnerL(p);
}

/*************************************************************************
Lmax
计算向量的无穷范数
无参数
向量的无穷范数
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
T Vector<T, N>::Lmax() const {
    T ResultMax = 0;
    for (int i = 0; i < N; i++)
    {
        if (ResultMax < std::abs(m_Component[i]))
        {
            ResultMax = m_Component[i];
        }
    }
    return ResultMax;
}

/*************************************************************************
InnerL
计算向量的p-范数
整型p
向量的p-范数
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
T Vector<T, N>::InnerL(unsigned int p) const {
    T Result = 0;
    for (int i = 0; i < N; i++)
    {
        Result += pow(std::abs(m_Component[i]), p);
    }
    return pow(Result, 1 / p);
}

/*************************************************************************
CrossProduct
计算向量的外积
Vector常引用Source
向量的外积
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
Vector<T, N>& Vector<T, N>::CrossProduct(const Vector& Source) {
    if (N == 1 || N == 2)
    {
        //抛出错误
    }
    else 
    {
        return InnerCrossProduct(Source);
    }
}

/*************************************************************************
InnerCrossProduct
计算向量的外积（虚函数，需要重载）
Vector常引用Source
向量的外积
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
Vector<T, N> Vector<T, N>::InnerCrossProduct(const Vector& Source) {
    //空函数体，在派生类中重载
    return *this;
}

/*************************************************************************
operator==
判断向量是否相等
Vector常引用Source
向量是否相等
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
bool Vector<T, N>::operator== (const Vector& Source) const {
    bool Result = 1;
    for (int i = 0; i < N; i++)
    {
        if (m_Component[i] != Source.Component[i])
        {
            Result *= 0;
            break;
        }
    }
    return Result;
}

/*************************************************************************
operator!=
判断向量是否不等
Vector常引用Source
向量是否不等
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
bool Vector<T, N>::operator!= (const Vector& Source) const {
    bool Result = 1;
    for (int i = 0; i < N; i++)
    {
        if (m_Component[i] == Source.Component[i])
        {
            Result *= 0;
            break;
        }
    }
    return Result;
}

/*************************************************************************
Module
求向量的模（也即2-范数）
无参数
向量的模
zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
T Vector<T, N>::Module() const {
    return L2();
}