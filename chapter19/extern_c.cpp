/*
 * @Author: iwiniwin
 * @Date: 2020-12-24 22:10:44
 * @Last Modified by: iwiniwin
 * @Last Modified time: 2020-12-24 22:28:37
 * @Description: 链接指示
 */
#include <string>
#include <iostream>
using namespace std;

// C函数声明
extern "C" size_t strlen(const char*);

// 复合语句链接提示。花括号的作用是将适用于该链接提示的多个声明聚合在一起，花括号中声明的函数名字是可见的，就好像在花括号之外声明一样
extern "C" {
    int strcmp(const char*, const char*);
    char *strcat(char *, const char*);
}

extern "C" {
    #include <string.h>  // 头文件中的所有普通函数声明都被认为是由链接指示的语言编写的
}

extern "C" void (*pf)(int);  // pf指向一个C函数，该函数接受一个int返回void

// f1是一个c函数，它的形参是一个指向C函数的指针。链接指示对整条声明都有效
extern "C" void f1(void(*)(int));

extern "C" typedef void FC(int);  // FCC函数类型
// f2是一个C++函数，该函数的形参是指向C函数的指针
void f2(FC *);

// calc函数就可以被c程序调用。编译器会为该函数生成适合于指定语言的代码
extern "C" double calc(double dp) {
    
}

// __cplusplus变量，只有在编译C++版本的程序时预处理器才会定义
#ifdef __cplusplus
extern "C"
#endif
int strcmp2(const char*, const char*);

extern "C" int compare(int *, int);
// extern "C" double compare(double*, double);  // error : C语言不支持函数重载
int compare(int*, int);  // 正确，这是一个C++函数

// extern "ABC" int ddd(int *, int);  // error : ABC是不认识的语言

void test1(){
    void (*pf2)(int);  // pf2指向一个C++函数
    // pf2 = pf;  // error : 类型不匹配
}

int main(){

    test1();

    system("pause");
    return 0;
}