/*
 * @Author: iwiniwin
 * @Date: 2020-12-19 19:06:40
 * @Last Modified by: iwiniwin
 * @Last Modified time: 2020-12-19 21:28:19
 * @Description: 模板与重载
 */
#include <string>
#include <iostream>
#include <memory>
using namespace std;

int f(int t) {
    cout << "call int t" << endl;
    return 0;
}

template <typename T> int f(T t){
    cout << "call T t" << endl;
    return 0;
}

template <typename T> string debug(const T &t) {
    cout << "debug const T &t" << endl;
    return "d1";   
}

template <typename T> string debug(T *p) {
    cout << "debug T *p" << endl;
    return "d2";
}

void test1(){

    f(3);  // 函数匹配同样好的情况下，会优先调用非模板函数的函数

    string s("hi");
    debug(s);  // 将调用const T &t版本，因为对于第二个debug而言，无法将string转换为指针

    debug(&s);  // 将调用T *p版本
                // 两个debug其实都是可行的，一个是debug(const string* &)，第二个是debug(string *)，但是第二个是精确匹配，因为第一个还有const的转换
    const string *sp = &s;
    debug(sp);  // 将调用T *p版本
                // 两个debug其实都是可行的，一个是debug(const string* &)，第二个是debug(const string *)，匹配的程度都是相同的，但第二个版本更加特例化，所以选择第二个，不会产生二义性
}

// foo是一个可变参数函数模板
template <typename T, typename... Args>  // Args是一个模板参数包
void foo(const T &t, const Args& ...rest){ // rest是一个函数参数包
    cout << sizeof...(Args) << endl;  // 类型参数的数目
    cout << sizeof...(rest) << endl;  // 函数参数的数目
}  

// 可变参数模板
void test2() {
    int i = 0; 
    double d = 3.14;
    string s = "vv";
    foo(i, s, 42, d);  // 包中有3个参数，T的类型由第一个实参的类型推断出来，剩下的提供函数额外实参的数目和类型
    foo(d, s);  // 包中有1个参数，编译器实例化的版本为 void foo(const double &, cosnt string &)
    foo("hi");  // 空包

    foo<int, int, int>(i, i, i, i, i);  // 4, 4
}

// 用来终止递归的，因为它比可变参数模板函数更特例化。必须声明在可变参数模板函数前面
template<typename T>
ostream &print(ostream &os, const T &t) {
    return os << t;
}

template <typename T, typename... Args>
ostream &print(ostream &os, const T &t, const Args&... rest) {  // 每个参数类型都是const Type &
    os << t << ",";
    return print(os, rest...);  // 等价于 print(os, a, b, c, d)
}

template <typename T, typename... Args>
ostream &print2(ostream &os, const T &t, const Args&... rest) {  // 每个参数类型都是const Type &
    os << t << ".";
    return print(os, debug(rest)...);  // 等价于 print(os, debug(a), debug(b), debug(c), debug(d))
}

void test3() {
    print2(cout, "aa", "bb", "cc");
}

template <typename... Args>
void emplace_back(Args&&... args) {
    allocator<string> alloc();  // 可以分配string的allocatior
    auto const p = alloc.allocate(3);   // 分配3个未初始化的string的内存
    alloc.construct(p, std::forward<Args>(args)...);  // 类似于alloc.construct(p, std::forward<aType>(a), std::forward<bType>(b));
}

template <typename T, typename... Args>
auto make_shared(Args&&... args) -> std::shared_ptr<T> {
    return std::shared_ptr<T>(new T(std::forward<Args>(args)...));
}

// 参数包转发
void test4() {

}

int main(){

    test1();
    test2();
    test3();
    test4();

    system("pause");
    return 0;
}