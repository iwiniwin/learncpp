#include <string>
using std::string;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int carray[10];  // 函数外部的数组默认初始化，所有的元素值都默认值

int main(){

    unsigned cnt = 42;
    constexpr unsigned sz = 42;  // 常量表达式
    int array[10];  // 函数内部的数组默认初始化，所有的元素值都是未定义的
    int *parr[sz];  // 含有42个整型指针的数组
    // string bad[cnt];  // error : 数组的维度必须是一个常量表达式，不同的编译器可能要求不同

    cout << carray[5] << endl;  // 值是默认值0
    cout << array[5] << endl;  // 值是未定义的

    const int cz = 3;
    int ia1[cz] = {0, 1, 2};  // 列表初始化
    int a2[] = {0, 1, 2};  // 列表初始化，可以省略维度
    string a3[3] = {"hi", "bye"};  // 等价于 {"hi", "bye", ""}
    // int a4[2] = {0, 1, 2};  // error : 初始值过多，超过了数组维度

    // 字符数组
    char c1[] = {'C', '+', '+'};  // 列表初始化，没有空字符
    char c2[] = {'C', '+', '+', '\0'}; // 列表初始化，含有显示的空字符
    char c3[] = "C++";  // 自动添加表示字符串结束的空字符
    // const char a4[3] = "C++";  // error : 没有空间再存放额外的空字符了

    // char c4[] = c1;  // error : 不允许使用一个数组初始化另一个数组
    char c5[] = {'C', '+', '+'}; 
    // c5 = c1;  // error : 不能把一个数组直接赋值给另一个数组

    int *ptrs[10];  // 包含10个整型指针的数组
    // int &refs[10];  // error : 不存在引用的数组

    int (*parray)[3] = &a2;  // parray是指向含有3个整数的数组的指针
    int (&arrRef)[3] = a2;  // arrRef是含有3个整数的数组的引用
    int *(&prarray)[10] = ptrs;  // prarray是含有10个整型指针数组的引用

    system("pause");
    return 0;
}