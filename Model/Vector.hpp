/*************************************************************************
【文件名】             Vector.hpp
【功能模块和目的】      实现不同维数、类型的向量类模版
【开发者及日期】        zheng-y23 2024-7-26
*************************************************************************/

#pragma once

#include <iostream>
#include <cmath>

/*************************************************************************
【类名】               Vector<T, N>
【功能】               N维T类型的向量类模版
【接口说明】           实现向量的加、减、乘、除、求外积、求范数
                      Vector& operator+ (const Vector& Source) const;
                      Vector& operator+= (const Vector& Source) const;
                      Vector& operator- (const Vector& Source) const;
                      Vector& operator-= (const Vector& Source) const;
                      Vector& operator* (const Vector& Source) const;
                      Vector& operator*= (const Vector& Source) const;
                      T L0() const;
                      T L1() const;
                      T L2() const;
                      T Lp(unsigned int p) const;
                      T Lmax() const;
【开发者及日期】        zheng-y23 2024-7-26
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
【函数接口】              Vector
【函数功能】              默认构造函数
【参数】                  无参数
【返回值】                无返回值
【开发者及日期】           zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
Vector<T, N>::Vector() {
    //空函数体
}

/*************************************************************************
【函数接口】             Vector
【函数功能】             拷贝构造函数
【参数】                 Vector常引用Source
【返回值】               无返回值
【开发者及日期】          zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
Vector<T, N>::Vector(const Vector& Source) {
    for (int i = 0; i < N; i++) 
    {
        m_Component[i] = Source.Component[i];
    }
}

/*************************************************************************
【函数名称】             ~Vector
【函数功能】             析构函数
【参数】                 无参数
【返回值】               无返回值
【开发者及日期】          zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
Vector<T, N>::~Vector() {
    //空函数体
}

/*************************************************************************
【函数名称】             SetComponent
【函数功能】             设置坐标
【参数】                 坐标数组
【返回值】               无返回值
【开发者及日期】          zheng-y23 2024-7-27
*************************************************************************/
template<class T, size_t N>
void Vector<T, N>::SetComponent(const T* Components) {
    for (int i = 0; i < N; i++)
    {
        m_Component[i] = Components[i];
    }
}

/*************************************************************************
【函数名称】            operator=
【函数功能】            赋值运算符重载
【参数】                Vector常引用Source
【返回值】              赋值后对象
【开发者及日期】         zheng-y23 2024-7-26
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
【函数名称】           operator+
【函数功能】           加法运算符重载
【参数】              Vector常引用Source
【返回值】             相加后对象
【开发者及日期】        zheng-y23 2024-7-26
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
【函数名称】           operator+=
【函数功能】           加等于运算符重载
【参数】               Vector常引用Source
【返回值】             相加后对象
【开发者及日期】        zheng-y23 2024-7-26
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
【函数名称】            operator-
【函数功能】            减法运算符重载
【参数】                Vector常引用Source
【返回值】              相减后对象
【开发者及日期】         zheng-y23 2024-7-26
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
【函数名称】           operator-=
【函数功能】           减等于运算符重载
【参数】               Vector常引用Source
【返回值】             相减后对象
【开发者及日期】        zheng-y23 2024-7-26
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
【函数名称】          operator[]
【函数功能】          下标运算符重载
【参数】              下标
【返回值】            数组中下标对应的数据
【开发者及日期】       zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
T Vector<T, N>::operator[] (size_t Index) const {
    return m_Component[Index];
}

/*************************************************************************
【函数名称】           operator*
【函数功能】           计算向量外积
【参数】               Vector常引用Source
【返回值】             向量外积
【开发者及日期】        zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
Vector<T, N>& Vector<T, N>::operator* (const Vector& Source) const {
    return CrossProduct(Source);
}

/*************************************************************************
【函数名称】            operator*=
【函数功能】            计算向量外积
【参数】                Vector常引用Source
【返回值】              向量外积
【开发者及日期】         zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
Vector<T, N>& Vector<T, N>::operator*= (const Vector& Source) const {
    return CrossProduct(Source);
}

/*************************************************************************
【函数名称】             operator*
【函数功能】             计算向量数乘
【参数】                 T类型Source
【返回值】               数乘后的向量
【开发者及名称】         zheng-y23 2024-7-26
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
【函数名称】              L0
【函数功能】              计算向量的0-范数
【参数】                  无参数
【返回值】                向量的0-范数
【开发者及日期】           zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
T Vector<T, N>::L0() const {
    T t_Result0 = 0;
    if (m_Component[0] != 0)
    {
        t_Result0 += 1;
    }
    for (int i = 1; i < N; i++) 
    {
        int i_flag = 0;
        for (int j = 0; j < i; j++)
        {
            if (m_Component[j] == m_Component[i])
            {
                i_flag = 0;
            }
        }
        if (i_flag == 1 && m_Component[i] != 0)
        {
            t_Result0 += 1;
        }
    }
    return t_Result0;
}

/*************************************************************************
【函数名称】                L1
【函数功能】                计算向量的1-范数
【参数】                    无参数
【返回值】                  向量的1-范数
【开发者及日期】             zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
T Vector<T, N>::L1() const {
    T t_Result1 = 0;
    for (int i = 0; i < N; i++)
    {
        t_Result1 += std::abs(m_Component[i]);
    }
    return t_Result1;
}

/*************************************************************************
【函数名称】                 L2
【函数功能】                 计算向量的2-范数
【参数】                     无参数
【返回值】                   向量的2-范数
【开发者及日期】              zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
T Vector<T, N>::L2() const {
    T t_Result2 = 0;
    for (int i = 0; i < N; i++)
    {
        t_Result2 += pow(m_Component[i], 2);
    }
    return sqrt(t_Result2);
}

/*************************************************************************
【函数名称】                  Lp
【函数功能】                  计算向量的p-范数
【参数】                     无参数
【返回值】                    向量的p-范数
【开发者及日期】              zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
T Vector<T, N>::Lp(unsigned int p) const {
    return InnerL(p);
}

/*************************************************************************
【函数名称】                  Lmax
【函数功能】                  计算向量的无穷范数
【参数】                      无参数
【返回值】                    向量的无穷范数
【开发者及日期】              zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
T Vector<T, N>::Lmax() const {
    T t_ResultMax = 0;
    for (int i = 0; i < N; i++)
    {
        if (t_ResultMax < std::abs(m_Component[i]))
        {
            t_ResultMax = m_Component[i];
        }
    }
    return t_ResultMax;
}

/*************************************************************************
【函数名称】                   InnerL
【函数功能】                   计算向量的p-范数
【参数】                       整型p
【返回值】                     向量的p-范数
【开发者及日期】                zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
T Vector<T, N>::InnerL(unsigned int p) const {
    T t_Result = 0;
    for (int i = 0; i < N; i++)
    {
        t_Result += pow(std::abs(m_Component[i]), p);
    }
    return t_pow(Result, 1 / p);
}

/*************************************************************************
【函数名称】                   CrossProduct
【函数功能】                   计算向量的外积
【参数】                       Vector常引用Source
【返回值】                     向量的外积
【开发者及日期】               zheng-y23 2024-7-26
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
【函数名称】                  InnerCrossProduct
【函数参数】                  计算向量的外积（虚函数，需要重载）
【参数】                      Vector常引用Source
【返回值】                    向量的外积
【开发者及日期】               zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
Vector<T, N> Vector<T, N>::InnerCrossProduct(const Vector& Source) {
    //空函数体，在派生类中重载
    return *this;
}

/*************************************************************************
【函数名称】                  operator==
【函数功能】                  判断向量是否相等
【参数】                      Vector常引用Source
【返回值】                    向量是否相等
【开发者及日期】              zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
bool Vector<T, N>::operator== (const Vector& Source) const {
    bool b_Result = 1;
    for (int i = 0; i < N; i++)
    {
        if (m_Component[i] != Source.Component[i])
        {
            b_Result *= 0;
            break;
        }
    }
    return b_Result;
}

/*************************************************************************
【函数名称】                 operator!=
【函数功能】                判断向量是否不等
【参数】                    Vector常引用Source
【返回值】                  向量是否不等
【开发者及日期】             zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
bool Vector<T, N>::operator!= (const Vector& Source) const {
    bool b_Result = 1;
    for (int i = 0; i < N; i++)
    {
        if (m_Component[i] == Source.Component[i])
        {
            b_Result *= 0;
            break;
        }
    }
    return b_Result;
}

/*************************************************************************
【函数名称】                 Module
【函数功能】                 求向量的模（也即2-范数）
【参数】                    无参数
【返回值】                   向量的模
【开发者及日期】             zheng-y23 2024-7-26
*************************************************************************/
template <class T, size_t N>
T Vector<T, N>::Module() const {
    return L2();
}