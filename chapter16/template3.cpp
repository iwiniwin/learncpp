/*
 * @Author: iwiniwin
 * @Date: 2020-12-18 13:34:15
 * @Last Modified by: iwiniwin
 * @Last Modified time: 2020-12-19 18:49:51
 * @Description: 模板实参
 */
#include <string>
#include <iostream>
#include <type_traits>
#include <utility>
using namespace std;

template <typename T> T fobj(T, T) {}
template <typename T> T fref(const T&, const T&) {}

template <typename T> void f1(T, T) {}

template <typename T1, typename T2, typename T3> T1 f2(T2, T3) {}

template <typename T1, typename T2, typename T3> T3 f3(T1, T2) {}

void test1(){
    int a[10], b[42];
    fobj(a, b);  // 正确，如果函数形参不是引用类型，数组类型会自动转换为指针类型，int*
    // fref(a, b);  // error : 类型不匹配，a，b的大小不同，数组类型不匹配

    int i = 0, *p1 = &i;
    const int *cp1 = &i;
    // f1(p1, cp1);  // error : 类型不匹配，一个是int*，一个是const int*

    f2<int>(3, 4);  // 正确，显式指定T1的类型，T2,T3的类型由编译器推断

    // f3<int>(3, 4);  // error : 第一个模板实参与第一个模板参数匹配，所以int指定的是T1，T3还是无法推断
    f3<int, int, int>(3, 4);  // 正确

    long l;
    // fobj(l, 1024);  // error : 类型不匹配
    fobj<int>(l, 1024);  // 正确，对于已经显式指定了的模板实参，可以进行正常的类型转换
}

// template <typename It>
// decltype(*beg) fcn0(It beg, It end) {  // error : beg不知道是什么
//     return *beg;
// }

template <typename It>
auto fcn(It beg, It end) -> decltype(*beg) {  // 尾置返回类型允许在参数列表之后声明返回类型，注意这里返回的是元素类型的引用类型
    return *beg;
}

template <typename It>
auto fcn(It beg, It end) -> typename remove_reference<decltype(*beg)>::type {  // 返回的是值，beg到end序列中元素的一个拷贝
    return *beg;
}

void test2() {
    
}

template <typename T> int compare(const T&, const T&) {}
int (*pf1)(const int&, const int&) = compare;  // 当使用一个函数模板初始化一个函数指针或为一个函数指针赋值时，编译器使用指针的类型来推断模板实参

template <typename T> void f1(T&){}  // 实参必须是一个左值
template <typename T> void f2(const T&){}  // 实参可以是任意类型
template <typename T> void f3(T&&){}  // 实参其实可以是任何类型
void f4(int &&) {}

template <typename T> void f(T&&);  // 非常量右值
template <typename T> void f(const T&);  // 左值和常量右值

void test3() {
    int i = 0;
    const int ci = 1;
    f1(i);  // 正确，T是int
    f1(ci);  // 正确，T是const int
    // f1(5);  // error : 传递给&参数的实参必须是一个左值

    f2(i);  // T是int
    f2(ci);  // T是int
    f2(5);  // const &参数可以绑定到一个右值，T是int

    f3(5);  // 实参一个int类型的右值，T是int
    f3(i);  // 正确，当将一个左值传递给函数的右值引用参数，“且此右值引用指向模板类型的参数时”，编译器推断模板类型参数即T为实参的左值引用类型。这里T被推断为int&
            // 此时出现引用折叠，模板实参是int& &&，此时引用会折叠成一个普通的左值引用类型，最终实参是int &
    // f4(i);  // error : 无法绑定一个左值到右值引用
    
    f3(ci);  // 正确，实参是一个左值，T是const int &
}

template <typename T>
typename remove_reference<T>::type &&move(T &&t){
    return static_cast<typename remove_reference<T>::type &&>(t);  // static_cast可以用于将一个左值显式地转换为一个右值引用
}

// std::move的实现
void test4() {

}

template <typename F, typename T1, typename T2>
void flip(F fun, T1 t1, T2 t2) {
    fun(t1, t2);
}

template <typename F, typename T1, typename T2>
void flip2(F fun, T1 &&t1, T2 &&t2) {
    fun(t1, t2);
}

template <typename F, typename T1, typename T2>
void flip3(F fun, T1 &&t1, T2 &&t2) {
    fun(std::forward<T1>(t1), std::forward<T2>(t2));  // forward会保持实参类型的所有细节，保持给定实参的右值/左值属性
}

void ff(int v1, int &v2) {
    // 修改v2的值，希望就是修改t2的
}

void gg(int &&i, int &j) {
    
}

void test5() {
    int i = 0;
    flip(ff, 42, i);
    flip2(ff, 42, i);
    // flip2(gg, 42, i);  // error : 不能将一个左值绑定到右值引用
    flip3(gg, 42, i);  // 正确
}

int main(){

    test1();
    test2();
    test3();
    test4();
    test5();

    system("pause");
    return 0;
}