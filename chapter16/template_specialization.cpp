/*
 * @Author: iwiniwin
 * @Date: 2020-12-19 21:27:11
 * @Last Modified by: iwiniwin
 * @Last Modified time: 2020-12-19 21:47:45
 * @Description: 模板特例化
 */
#include <string>
#include <iostream>
using namespace std;

template <typename T> void compare(const T&, const T&) {
    cout << "compare(const T&, const T&)" << endl;
}

// compare的一个特例化模板
template<>
void compare(const char* const &p1, const char * const &p2) {
    cout << "compare(const char* const &p1, const char * const &p2)" << endl;
}

// 模板特例化
void test1() {
    compare("aa", "bb");  // 调用的是通用版本，特例化只是实例化了一个模板，而非重载，不影响函数匹配
    const char* p = "aa";
    compare(p, p);  // 调用的是特例化的版本
}

class Test {

};

// 定义std::hash类的一个特例化版本
namespace std {
    template<>
    struct hash<Test> {
        typedef size_t result_type;
        typedef Test argument_type;  
        size_t operator() (const Test &s) const;  
    };

    size_t hash<Test>::operator()(const Test& s) const {
        return hash<string>()("vv");  // 使用标准库的hash<string>生成hash，hash<string>是标准库为hash定义的一个特例化版本
    }
}

// 类模板特例化
void test2() {

}

// 原始的，最通用版本
template <typename T> struct remove_reference2 {
    typedef T type;  
};

// 部分特例化版本，本质还是一个模板
template <typename T> struct remove_reference2<T&> {  // 类名之后要为特例化模板参数指定实参
    typedef T type;
};

template <typename T> struct remove_reference2<T&&> {
    typedef T type;
};

// 类模板部分特例化，只能部分特例化类模板，而不能特例化函数模板
void test3() {
    int i = 0;
    remove_reference2<decltype(42)>::type a;  // decltype(42)是int，使用原始版本
    remove_reference2<decltype((i))>::type b;  // decltype((i))是int&, 使用左值版本
    remove_reference2<decltype(std::move(i))>::type c;  // 使用右值版本
}

template <typename T> struct Foo {
    void Bar() {cout << "common bar" << endl;}
    T mem;
};

// 特例化Foo<int>的成员Bar
template<>
void Foo<int>::Bar() {
    cout << "int bar" << endl;
}

// 特例化成员，而不是类
void test4() {
    Foo<string> fs;
    fs.Bar();  // common bar

    Foo<int> fi;
    fi.Bar();  // int bar
}

int main(){

    test1();
    test2();
    test3();
    test4();

    system("pause");
    return 0;
}