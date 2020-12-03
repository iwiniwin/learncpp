#include <string>
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

void test1(){
    int *pi = new int;  // 此new表达式在自由空间构造一个int型对象，并返回指向该对象的指针
    cout << *pi << endl;  // -1163005939，默认初始化，pi指向的对象是未初始化的

    string *ps = new string;

    int *pi2 = new int(1024);  // 直接初始化，pi指向的对象值是1024

    int *pi3 = new int();  // 值初始化，pi3指向的对象值为0
    cout << *pi3 << endl;  // 0

    string *ps2 = new string(10, '9');  // 直接初始化
    cout << *ps2 << endl;  // 9999999999

    vector<int> *pv = new vector<int>{1, 2, 3};  // 列表初始化

    const int *pci = new const int(1024);  // 分配并初始化一个const int 
    // const int *pci2 = new const int;  // error : 一个动态分配的const对象必须进行初始化
    const string *pcs = new const string;  // 对于一个定义了默认构造函数的类类型，其const对象可以隐式初始化

    int * pi4 = new (nothrow) int;  // 定位new，默认情况下，如果new不能分配需要的内存空间，会抛出bad_alloc异常，使用定位new，可以在分配失败时返回一个空指针，而不抛出异常
}

// auto
void test2(){
    int a = 2, b = 0;
    // 可以利用auto从初始化器来推断想要分配的对象的类型
    auto pl = new auto(a);  // pl指向一个与a类型相同的对象，新分配的对象使用a的值进行初始化
    cout << *pl << endl;  // 2
    *pl = 3;
    cout << a << endl;  // 2
    // auto pl2 = new auto{a, b};  // error : 括号中只能有单个初始化器
}

// delete
void test3(){
    auto p = new int(4);
    cout << *p << endl;  // 4
    cout << (p == nullptr) << endl;  // 0
    delete p;
    cout << *p << endl;  // 16586560 ，未定义的
    cout << (p == nullptr) << endl;  // 0

    p = nullptr;  // 在释放内存后，将指针置为空，是个很好的做法，避免再使用已经释放掉的对象

    int i = 2, *pi1 = &i;
    // delete pi1;  // undifined : delete一块并非new分配的内存，其行为是未定义的
    // delete i;  // error : i不是指针

    int *pi2 = nullptr;
    delete pi2;  // 正确，delete一个空指针总是没有错误的

    const int *pci = new const int(1024);
    delete pci;  // 虽然一个const对象的值不能被改变，但它本身是可以被销毁的
}

class Test {

};

Test *factory(){
    return new Test();  // 调用者应该释放这块内存
}

void use_factory(){
    Test *t = factory();  // 使用t

    // 正确做法
    delete t;

}  // 如果没有上面的正确做法，t离开了它的作用域后，它所指向的内存仍不会被释放

void test4(){
    use_factory();
}

void process(shared_ptr<int> ptr){

}

// shared_ptr和new结合使用
void test5(){
    // shared_ptr<int> p1 = new int(42);  // error : 不能将一个内置指针隐式转换为智能指针

    shared_ptr<int> p2(new int(42));  // p1指向一个值为42的int，利用直接初始化

    int *x(new int(1024));  // x是一个普通指针
    // process(x);  // error : 不能将一个内置指针隐式转换为智能指针

    process(shared_ptr<int>(x));  // 危险操作，将一个临时shared_ptr传递给process,当这个调用表达式结束时，临时对象会被销毁，同时由于计数为0，它指向的内存也会被销毁

    cout << *x << endl;  // 8026408, 未定义的，此时x已经是一个空悬指针了


    shared_ptr<int> p(new int(42));
    int *q = p.get();  // 正确，但是get函数应该仅用于向不能使用智能指针的代码传递一个内置指针，且该代码不能delete此指针
    {  // 新程序块
        shared_ptr<int>(q);
    }  // 程序块结束时，q指向的内存被释放
    cout << *p << endl;  // 42 ？ ， 为什么仍然值是42，此时p指向的内存已被释放，它指向的值应该是未定义的
    // 当test5这个函数代码块结束时，p被销毁，会导致内存被第二次delete
}

int main(){

    test1();
    test2();
    test3();
    test4();
    test5();

    system("pause");
    return 0;
}