#include <string>
#include <iostream>
using namespace std;

#include <vector>
#include "function.h"
#include <initializer_list>
#include <cstdarg>

void xfunc(int, float);  // 函数声明
void xfunc(int, float);  // 函数声明
void xfunc(int, float);  // 函数声明
void yfunc(int a, float b);  // 函数声明

void zfunc(int b){  // 函数定义

}

class A {
    public:
    int a = 8;
};

int test11(){
    static int ctr = 0;  // 局部变量被定义成static后，在程序的执行路径第一次经过对象语句初始化，知道程序结束才会被销毁
    ctr ++;
    return ctr;
}

// 测试函数内静态变量
void test1(){
    cout << test11() << endl;  // 1
    cout << test11() << endl;  // 2
    // cout << ctr << endl;  // error : ctr是未定义的
}

void test20(vector<int> vec){  // 值传递，仅仅是将实参的值拷贝给形参
    vec.push_back(4);
}

void test21(int &a){  // 引用传递
    a = 4;
}

void test22(int *p){  // 值传递，但是可以通过指针修改其所指向的对象
    *p = 1;
}

void test23(A a){  // 值传递
    a.a = 9;
}

void test24(string &s) {}

void test25(const string &s) {}  // 如果函数不会改变形参的值，则最好使用常量引用，一来可以告诉调用者不会改变它传递的值，二来可以接收的实参范围不会被限制

// 测试函数参数传递
void test2(){
    vector<int> vec = {1, 2, 3};
    test20(vec);
    for(int v : vec){
        cout << v << " ";
    }  // 将输出 1 2 3
    cout << endl;  

    int b = 3;
    // test21(4);  // error 
    test21(b);
    cout << b << endl;  // 输出 4

    int c = 0;
    test22(&c);  
    cout << c << endl;  // 输出 1

    A a;
    test23(a);
    cout << a.a << endl;

    // test24("vvv");  // error : 不能将字面值赋给普通引用
    test25("vvv");
}

void test_const(int a){}
// void test_const(const int a){}    // error : 重复定义，顶层const会被忽略

// 下面这3个函数的声明是等价的
void print(const int*);
void print(const int[]);
void print(const int[10]);  // 这里的维度表示我们期望数组含有多少元素，实际不一定
void print(int (*matrix)[10], int size);  // 多维数组，实际上是指针数组首元素的指针

// 被调用函数如何确定数组的尺寸？
void print(const char *cp);  // 1. 利用标记指定数组长度，比如C风格字符串，遇到空字符说明找到数组末尾
void print(const int *beg, const int *end);  // 2. 使用标准库规范，定义首元素指针和尾后指针
void print(const int ia[], size_t size);  // 3. 显式传递一个表示数组大小的形参

void test30(int (&array)[5]){
    array[0] = 0;
}

void test31(int array[10]){  // 这里的 10 是不起作用的，实际上就是int *
    array[0] = 11;
}

// 测试数组形参
void test3(){
    int arr[] = {1, 2, 3};
    // test30(arr);  // error : 实参数组维度与形参不同
    int arr2[] = {1, 2, 3, 4, 5};
    test30(arr2);
    cout << arr2[0] << endl;  // 输出 0

    test31(arr);  // 合法
    cout << arr[0] << endl;  // 输出 11

    // int &arr4[3] = arr;  // error : 不允许使用引用的数组
    int (&arr4)[3] = arr;

    int i = 0;
    // test30(&i);  // error : 不能从int * 转化为数组类型
    test31(&i);
    cout << i << endl;  // 11
}

void error_msg(initializer_list<string> il){
    for(auto beg = il.begin(), end = il.end(); beg != end; ++beg){
        cout << *beg << " ";
    }
    cout << endl;
}

void error_msg2(vector<string> il){
    for(auto beg = il.begin(), end = il.end(); beg != end; ++beg){
        cout << *beg << " ";
    }
    cout << endl;
}

// 省略符形参
void test41(int count, ...){
    va_list args;
    va_start(args, count);
    for(int i = 0; i < count; ++i){
        cout << va_arg(args, int) << endl;;
    }
}

// 测试可变形参
void test4(){
    initializer_list<int> lst{1, 2, 3};
    cout << *lst.begin() << endl;
    // *lst.begin() = 2; error : initializer_list中的元素永远是常量值
    error_msg({"lll", "jjj", "666"});
    error_msg({"lll", "666"});

    error_msg2({"222", "666"});

    test41(2, 55, 44);
}

int main(int argc, char *argv[]){
    cout << "argc = " << argc << endl;
    cout << "argv[0] = " << argv[0] << endl;
    for(size_t i = 1; i != argc; ++i){
        cout << "argv[" << i << "] param = " << argv[i] << endl;
    }

    test1();
    test2();
    test3();
    test4();

    system("pause");
    return 0;
}