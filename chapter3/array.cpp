#include <string>
using std::string;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <iterator>

int carray[10];  // 函数外部的数组默认初始化，所有的元素值都默认值

// 多维数组
void test1(){
    int ia[3][4];
    cout << ia[2][1] << endl;  // 值是未定义的

    int ia1[3][4] = {3};
    cout << ia1[2][1] << endl;  // 值是0，有了默认值
    cout << ia1[0][0] << endl;  // 值是3

    int ia2[3][4] = {
        {1, 1, 1, 1},
        {2, 2, 2, 2},
        {3, 3, 3, 3},
    };
    int ia3[3][4] = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3,}; // 与上面的等价

    int ia4[3][4] = {
        {1},
        {2},
    };  // 部分初始化，只初始化第一行和第二行的首元素，其他位置都是默认初始化

    int (&ref)[4] = ia4[0];  // ref引用ia4的第一行

    // 范围for语句遍历多维数组
    for(auto &row : ia4){
        for(auto &col : row){
            cout << col << endl;
        }
    }

    int ia5[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
    };
    int (*p)[4] = ia5;
    int *p1 = ia5[1];
    cout << *((*(p + 1)) + 1) << endl;  // 6
    cout << *(p1 + 1) << endl;  // 6
}

// 常量数组
void test2(){
    const int array[] = {1, 2, 3};
    // array[0] = 1;  // error : 常量，不允许修改
    int array1[] = {4, 5, 6};
    // array = array1;  // error : 数组不能直接赋值
    // array1 = array;  // error : 数组不能直接赋值
}

int main(){

    test1();
    test2();

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

    // 当使用数组作为一个auto变量的初始值时，推断得到的类型是指针而非数组
    int ia[] = {1, 2, 3};
    auto ia2(ia);  // ia2是一个整型指针，指向ia的第一个元素，等价于 auto ia2(&ia[0]);
    auto ia3 = ia;  // ia3是一个整型指针，指向ia的第一个元素

    // 当使用decltype关键字推断数组的类型时，返回的类型仍然是数组
    decltype(ia) ia4 = {1, 2, 3};

    int *beg = std::begin(ia);  // 指向ia首元素的指针
    int *last = std::end(ia);  // 指向ia尾元素下一位置的指针，尾后指针
    int *ip = beg + 1;  // 指向ia第二个元素的指针
    int *ip2 = ia + 3;  // 尾后指针
    cout << (ip2 == last) << endl;  // 1

    ptrdiff_t d = last - beg;  // 两个指针差值的类型

    int *na = nullptr;
    int *na2 = nullptr;
    cout << (na - na2) << endl;  // 0

    int *iip = &ia[1];
    cout << iip[1] << endl;  // 值是尾元素3
    cout << iip[-1] << endl;  // 值是首元素1

    system("pause");
    return 0;
}