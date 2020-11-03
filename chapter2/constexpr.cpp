#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int a1 = 0;
int main(){

    constexpr int mf = 20;
    constexpr int limit = mf + 1;

    int x = 0;
    const int y = 0;
    // constexpr int z = x; // error : x不是常量表达式
    constexpr int z = y;

    const int *p = nullptr;  // p是指向常量的指针
    constexpr int *q = nullptr;  // q是常量指针，constexpr仅对指针有效，与指针所指的对象无关

    int a2 = 0;

    constexpr int *q2 = &a1;  // 函数体外定义的对象其地址固定不变
    // constexpr int *q3 = &a2;  // error : 函数体内定义的对象并非存放在固定地址中

    system("pause");
    return 0;
}