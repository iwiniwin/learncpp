#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main(){

    auto i = 0, *p = &i;  // i是整数，p是整型指针
    // auto j = 3, k = 3.14;  // error : j和k的类型不一样

    // auto一般会忽略掉顶层const，同时底层const会保留下来
    const int ci = i, &cr = ci;
    auto b = ci;  // b是一个整数，ci的顶层const被忽略了
    auto c = cr;  // c是一个整数
    auto d = &i;  // d是一个整型指针
    auto e = &ci;  // e是一个指向整数常量的指针，对常量对象取地址是一种底层const

    const auto f = ci;  // ci的推演类型是int, f是const int

    auto &g = ci;  // g是一个整型常量引用
    // auto &h = 42;  // error : 不能为非常量引用绑定字面值
    const auto &h = 42;

    auto &m = ci, *p1 = &ci;  // m是对整型常量的引用，p是指向整型常量的指针

    // auto &n = i, *p2 = &ci;  // error : i的类型是int，而&ci的类型是const int
    
    system("pause");
    return 0;
}