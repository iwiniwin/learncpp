/*
 * @Author: iwiniwin
 * @Date: 2020-12-15 17:37:02
 * @Last Modified by: iwiniwin
 * @Last Modified time: 2020-12-16 15:53:51
 * @Description: 拷贝控制相关
 */
#include <string>
#include <iostream>
using namespace std;

class Base {
public:
    // virtual ~Base() = default;  // 虚析构函数
    Base() = default;
    virtual ~Base() {  // 虚析构函数
        cout << "base deconstruct" << endl;
    }  

    Base(const Base&) = delete;  // 拷贝构造函数是删除的，则子类的也是删除的
};

class Derived : public Base {
public:
    ~Derived() {
        cout << "derived deconstruct" << endl;   
    }
};

void test1(){
    Base *p = new Base;
    delete(p);   // base deconstruct
    p = new Derived;
    delete(p);   // derived deconstruct  base deconstruct

    Derived d;
    // Derived d2(d);  // error : 子类的拷贝构造函数也是被删除的
    // Derived d3(std::move(d));  // error :  由于没有定义移动构造函数，所以还是隐式的调用了拷贝构造函数，而构造函数是被删除的
}

class B1 {
public:
    B1() = default;
    B1(int a) {
        cout << "base a" << endl;
    }
    B1(int a, int b) {
        cout << "base a b" << endl;
    }
    virtual ~B1() = default;
};

class D1 : public B1 {
public:
    using B1::B1;  // 声明继承父类的构造函数

    D1(int a, int b) : B1(a) {  // 虽然上面声明继承了父类的构造函数，但是当派生类定义的构造函数与基类的构造函数具有相同的参数列表时，则该构造函数替换掉从父类继承而来的
        cout << "derived a b" << endl;
    }

    D1(const D1 &d) : B1(d){  // 拷贝构造函数，B1的拷贝构造函数负责将d的基类部分拷贝给要创建的对象。如果不显式调用的话，默认情况下，会使用基类的默认构造函数初始化对象的基类部分
        
    }

    D1(D1&& d) : B1(std::move(d)) {  // 移动构造函数
        
    }

    D1 &operator=(const D1 &rhs){  // 赋值运算符
        B1::operator=(rhs);  // 为基类部分赋值，必须显式调用，否则不会自动调用的
        return *this;
    }
};

class D2 : public B1 {
private:
    using B1::B1;  // 构造函数的using声明语句不会受子类的控制符比如这里的private影响
};

void test2() {
    B1 b(3);
    D1 d(3);  // 正确，声明继承了父类接收int的构造函数

    D1 d1(3, 4);  // derived a b  base a

    D2 d2(3);  // 正确，即使using B1::B1定义在了private下面
    D2 d22;  // 正确，虽然基类合成的默认构造函数不会被继承，但通过using继承的构造函数不会被作为用户定义的构造函数来使用，所以如果一个类只有继承的构造函数，则它也将拥有一个合成的默认构造函数
}

class B2;
class F {
public:
    void f(B2 *p);
};

class B2 {
    friend class F;
private:
    virtual void f() {
        cout << "base f" << endl;
    }
};

void F::f(B2 *p) {
    p->f();
}

class D3 : public B2 {
    friend class F;
public:
    void f() override {  // 即使基类定义的虚函数是private的，也仍然可以覆写，并且可以改变控制级别
        cout << "derived f" << endl;
    }
};

void test3() {
    F f;
    B2 b;
    D3 d;
    B2 *p = &b;
    f.f(p);  // base f
    p = &d;
    f.f(p);  // derived f

    d.f();  // derived f
}

int main(){

    test1();
    test2();
    test3();

    system("pause");
    return 0;
}