#include <string>
#include <iostream>
#include <cstring>
using namespace std;

// 函数模板
template<typename T>
int compare(const T &v1, const T &v2) {
    if(v1 < v2) return -1;
    if(v2 < v1) return 1;
    return 0;
}

template<typename T> T foo(T *p) {
    T tmp = *p;
    return tmp;
}

// typename与class用在模板参数上时没有任何区别，但推荐使用typename
template<typename T, class U> T foo(U *p) {
    T tmp = *p;
    return tmp;
}

// N和M是非类型参数，必须是常量表达式
template<unsigned N, unsigned M>
int compare2(const char (&p1)[N], const char (&p2)[M]) {
    return strcmp(p1, p2);
}

// inline或constexpr说明符放在模板参数列表之后
template<typename T> inline T min();
// inline template<typename T> T min();  // error : inline应该放在模板参数之后

class TT {
public:
    int t = 0;
};

void test1(){
    compare(1, 2);  // 编译器会使用实参的类型来确定保定道模板参数T的类型

    TT t1, t2;
    // compare(t1, t2); // error : TT类型的对象没有定义<操作。这条错误只有在编译器实例化模板的时候才会触发

    compare2("aa", "bb");   // 编译器会根据字面值常量的大小来代替N和M

    compare2<3, 3>("aa", "bb");

    int a = 3;
    // compare2<a, a>("aa", "bb");  // error : 非类型参数必须是常量
}

// 前置声明，在将一个模板类声明为友元时要用到
template <typename T> class Pal;
class C {  // C是一个普通的非模板类
    friend class Pal<C>;  // 用类C实例化的Pal是C的友元
    template <typename T> friend class Pal;  // Pal的所有实例都是C的友元
};
template <typename T> class CT {  // CT本身是一个模板类
    friend class Pal<T>;  // CT的每个实例将与T相同的Pal的实例声明为友元
    template <typename X> friend class Pal;  // Pal的每个实例都是CT每个实例的友元，注意要使用不同的模板参数
    friend T;  // 将模板的类型参数声明为友元
public:
    static int a;
};

template <typename T> int CT<T>::a = 0;  // 静态成员定义

// 模板与友元
void test2() {
    
}

typedef CT<int> IntCT;  // IntCT是CT<int>的别名
// typedef CT<T> TCT;  // error : 模板不是一个类型，所以不能定义一个typedef引用模板
template <typename T> using NA = CT<T>;  // 正确，C++11允许通过using为模板定义一个别名

template <typename TX, typename TY> class PP;  // 模板类声明，正确，模板参数名可以任意起，不一定非要T
// template <typename TX, typename TX> class PP2;  // error : 模板参数名不能重用
template <typename T> int compare();  // 正确，模板函数声明

template <typename V> int compare() {  // 模板函数定义，正确，定义中的模板参数名不必与声明中的相同
    auto a = V::size_type;  // 默认情况下，编译器认为size_type不是类型，是个数据成员
    // V::size_type2 b;  // error : 默认情况下，编译器认为size_type2不是类型，是个数据成员
    typename V::size_type3 c;  // 正确，使用typename显式告诉编译器该名字一个类型 
}

// 模板别名
void test3() {
    NA<int> a;

    CT<string> c;
    cout << CT<string>::a << endl;  // 0， 访问静态成员
    cout << c.a << endl;  // 0
}

template <typename T = int> T compare(string a) {
    return a;
}

template <typename T, typename F = less<T>>
int compare(const T &v1, const T &v2, int nothing, F f = F()){  // nothing仅为了避免和上面的compare定义冲突
    if(f(v1, v2)) return -1;
    if(f(v2, v1)) return 1;
    return 0;
}

template <class T = int> class Number {

};

// 默认实参
void test4() {
    // compare("33");  // error : 默认实参是int，但返回了一个string
    compare<string>("33");  // 正确

    compare(3, 4, 0);  // 默认使用less比较

    // Number n;  // error : 即使模板定义了默认实参，也必须要带尖括号
    Number<> n;  // 正确，使用默认实参
}

int main(){

    test1();
    test2();
    test3();
    test4();

    system("pause");
    return 0;
}