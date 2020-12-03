#include <string>
#include <iostream>
#include <memory>
using namespace std;

void test1(){
    // 让new分配一个数组，返回指向第一个对象指针
    int size = 10;
    int *pia = new int[size];  // pia指向第一个int。动态数组并不是数组类型。默认初始化
    int *pia2 = new int[10]();  // 值初始化为0的int
    int *pia3 = new int[10]{1, 2, 3};  // 列表初始化，前三个赋值，后面的执行值初始化
    cout << *pia << " " << *pia2 << " " << *pia3 << endl;  // -1163005939（未定义的） 0 1

    // int *pia4 = new int[3]{1, 2, 3, 4};  // error : 初始化器数目要小于元素数目
    // int *pia5 = new int[3](0);  // error : 不能在括号中给出初始化器

    typedef int arrT[20];  // 使用数组别名
    int *pa = new arrT;

    // char arr[0];  // error : 数组的大小必须大于0
    char *cp = new char[0];  // 正确，new会返回一个合法的非空指针，此指针保证与new返回的其他指针都不相同。对于零长度的数组来说，就像尾后指针,它不指向任何元素

    // 释放动态数组，销毁pia指向的数组中的元素，并释放对应的内存。数组中的元素按逆序销毁
    delete [] pia;
    // delete pia;  // undefined ： 行为将是未定义的
}

// 使用unique_ptr管理动态数组
void test2(){
    // up指向一个包含10个未初始化int的数组
    unique_ptr<int[]> up(new int[10]);
    
    // 当unique_ptr指向的是数组时，可以使用下标运算符来访问数组中的元素
    cout << up[0] << endl;  // -1163005939 ,值是未定义的

    up.release();  // 自动使用delete[]销毁其指针
    cout << (up == nullptr) << endl;  // 1
}

// 使用shared_ptr管理动态数组
void test3(){
    shared_ptr<int> sp1(new int[10]());  // 未定义的，shared_ptr未提供删除器，将仍然使用delete销毁对象，而不是使用delete []

    // shared_ptr管理动态数组，需要自己提供删除器
    shared_ptr<int> sp2(new int[10](), [](int *p) {
        cout << "delete [] p" << endl;
        delete [] p;
    });

    // cout << sp2[0] << endl;  // error : 即使shared_ptr指向动态数组，也仍然不支持下标访问
    cout << *sp2 << endl;  // 0
    // cout << *(sp2 + 1) << endl;  // error : 智能指针不支持指针的算术运算
    // 要访问下一个元素，只能使用get
    cout << *(sp2.get() + 1) << endl;  // 0

    sp2.reset();  // delete [] p将在test之前打印
    cout << "test" << endl;
}

int main(){

    test1();
    test2();
    test3();

    system("pause");
    return 0;
}