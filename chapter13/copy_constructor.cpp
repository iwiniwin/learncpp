#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Foo {
public:
    int val = 0;
    Foo() = default;  // 默认构造函数
    // Foo();  // 默认构造函数，注意不能和上面同时定义
    Foo(const Foo&);  // 拷贝构造函数，参数几乎总是一个cosnt的引用

    Foo& operator=(const Foo&);  // 拷贝赋值运算符

    ~Foo();  // 析构函数
};

// Foo& Foo::operator=(const Foo&) = default;  // 默认的拷贝赋值运算符，只对成员的类外定义使用default，则成员不会是内联的（在类内使用default时，合成的函数将隐式声明为内联的）

Foo& Foo::operator=(const Foo&) {
    // 并没有进行真的拷贝
    cout << "call =" << endl;
    return *this;
}

Foo::Foo(const Foo& foo){
    cout << "copy construct" << endl;
}

Foo::~Foo(){
    cout << "destruct" << endl;
}

void test1_a(){
    Foo a;
}

void test1(){
    cout << "before test1_a" << endl;
    test1_a();
    cout << "after test1_a" << endl;

    Foo a, b = a, c;  // 拷贝初始化，会触发拷贝构造函数

    a.val = 1;
    c.val = 2;

    a = c;  // 由于重载了拷贝赋值运算符，什么也没有做，所以两个val都还是原来的值
    cout << a.val << " " << c.val << endl;  // 1 2
}

class NoCopy {
public:
    NoCopy() = default;
    NoCopy(const NoCopy&) = delete;  // 阻止拷贝
    ~NoCopy() = default;
    NoCopy& operator=(const NoCopy&) = delete;  // 阻止赋值
private:
    // NoCopy& operator=(const NoCopy&) = default;  // 通过将默认的拷贝赋值运算符定义为私有的，也可以阻止对象赋值，但是友元和成员函数仍可以拷贝对象
                                                    // 因此可以声明为private但不定义，这样的话成员函数或友元的拷贝操作将会导致在链接时出错
};

void test2(){
    // NoCopy n, f = n;  // errror : NoCopy::NoCopy(const NoCopy&)拷贝构造函数已被删除
    NoCopy n, m;
    // n = m;  // error : NoCopy& NoCopy::operator=(const NoCopy&) 拷贝赋值运算符已被删除
}

class NoDtor{
public:
    NoDtor() = default;
    ~NoDtor() = delete;  // 将析构函数删除，则不能销毁NoDtor类型的对象
};

void test3(){
    // NoDtor nd;  // error : NoDtor::~NoDtor()被删除了，所以也不允许定义该类型的变量或临时对象
    NoDtor *p = new NoDtor();  // 正确
    // delete p;  // error : NoDtor::~NoDtor()被删除了,所以不能销毁
}

int main(){

    test1();
    test2();
    test3();

    system("pause");
    return 0;
}