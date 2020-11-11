#include <string>
using std::string;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class T {
    private:
    int a;
    int b;
    public:
    int c;
};

void test1() {
    int k = 0;
    cout << (sizeof(T)) << endl;  // 12
    cout << (sizeof(k)) << endl;  // 4
    T *pt = nullptr;
    cout << (sizeof(pt)) << endl; // 4，得到的是指针本身所占空间的大小
    cout << (sizeof(*pt)) << endl;  // 12，sizeof并不需要真的解引用，不会计算表达式的值
    cout << (sizeof(T::c)) << endl;  // 4

    cout << (sizeof(char)) << endl;  // 1，char类型sizeof固定返回1
    int &kk = k;
    cout << (sizeof(kk)) << endl;  // 4

    int arr[] = {1, 2, 3, 4};
    cout << (sizeof(arr)) << endl;  // 16

    constexpr size_t sz = sizeof(arr) / sizeof(*arr);  // 4，数组元素数量
    int brr[sz];  // 利用常量sz声明数组
}

int main(){

    test1();
    system("pause");
    return 0;

    bool b = true;
    bool bb = -b;  // bb仍然是1

    double a = 3.14;
    // cout << (a % 3) << endl; // error : %只能作用于整数

    int k = 0;
    k = 3.1415926;
    cout << k << endl;  // k值是3
    k = {23};  // 对于内置类型，初始值列表最多只能包含一个值
    // k = {23.25};  // 错误，精度丢失
    k = {};  // 无论左侧运算对象的类型是什么，初始值列表都可以为空，编译器会创建一个值初始化的临时量赋给左侧对象。这里k是0

    int c = (k = 8);  // 赋值运算返回的是其左侧运算对象。c值是8

    k = k ++;  // warning : 这条语句的行为是未定义的，赋值运算符的两端都用到了k，并且左侧的运算对象还改变了k

    int *p = &k;
    cout << (p != 0) << endl;  // 1
    // cout << (p != 3) << endl;  // error : 不能将指针和整型进行比较

    system("pause");
    return 0;
}