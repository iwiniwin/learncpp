#include <string>
using std::string;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void test(){
    int i = 0;
    const int v2 = 0; 
    int v1 = v2;
    int *p1 = &v1, &r1 = v1;
    const int *p2 = &v2, *const p3 = &i, &r2 = v2;

    r1 = v2;
    // p1 = p2;  // error
    p2 = p1;  
    // p1 = p3;  // error
    p2 = p3;
}

int main()
{
    test();
    // int &a = 3; // error：普通引用不能绑定到字面值
    const int &b = 3; // 常量引用可以绑定到非常量的对象，字面值，或者表达式

    const int i = 3;
    // int &r1 = i; // error：普通引用不能绑定常量

    // 常量引用绑定普通变量
    int j = 42;
    const int &r2 = j;  // 常量引用对于引用对象本身是不是一个常量不做限定
    j = 30;  
    cout << r2 << endl; // 30

    double k = 3.21;
    const int &r3 = k;  // 这种情况下，r3其实是绑定到了一个临时量上
    cout << r3 << endl; // 3
    k = 4.56;
    cout << r3 << endl; // 3，修改k的值，不会影响到r3

    const int x = -1, &r4 = 0; // r4是常量引用

    const int *p1; // 指向常量的指针
    // int *const p2; // error：常量指针必须初始化
    // int *const p2 = &i;  // error：p2是指向int，而 i是const int，不允许，如果指向了就可以通过p2修改i了，不正确
    // const int *const p2 = &j; // 合法，int *可以转换为const int *
    int *const p2 = &j;

    const int *const p3 = &i;
    int * p4;
    p1 = p3;
    // p4 = p3; // error：p3指向的是const int而 p4指向的是int，类型不匹配
    // p2 = p1; // error：p2是常量不能修改

    system("pause");
    return 0;
}