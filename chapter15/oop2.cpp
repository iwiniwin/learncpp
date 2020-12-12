#include <string>
#include <iostream>
using namespace std;

class Base {
    friend class Pal;
public:
    int h = 0;
    void f(){cout << "base f" << endl;}
    virtual void f2(){cout << "base f2" << endl;}
    void f3(){cout << "base f3" << endl;}
protected:
    int i = 1;
private: 
    int j;
};

class Sneaky : public Base {
    friend void clobber(Sneaky &s) {
        cout << s.i << endl;  // 正确，可以通过派生类对象，访问其的基类部分的受保护成员
        // cout << s.j << endl;  // error : 不能访问j，因为j是私有的，Sneaky也不能访问
    }
    friend void clobber(Base &s) {
        // cout << s.i << endl;  // error : 不能通过基类对象访问其受保护的成员
        // cout << s.j << endl;  // error : j是私有的
    }
};

// 访问控制权限
void test1(){

}

class PubDerv : public Base {
public:
    void f() {
        cout << h << endl;
        cout << i << endl;
        // cout << j << endl;  // error : j是私有的
        Base *p = this;
    }
private:
    int m;
};

class PriDerv : private Base {  
public:
    void f() {
        cout << h << endl;  // 正确，派生列表中的访问说明符对于能否访问基类的成员没有影响
        cout << i << endl;  // 正确
        // cout << j << endl;  // error : j是私有的
        Base *p = this;  // PriDerv的成员函数和友元都能使用派生类向基类的转换，不受生列表中的访问说明符影响
    }
};

class PubDerv2 : public PubDerv {
public: 
    void f2() {
        cout << h << endl;
    }
};

class PriDerv2 : public PriDerv {
public: 
    void f2() {
        // cout << h << endl;  // error : 派生列表的private说明符限制了h在PriDerv中是私有的
        // Base *p;  // error : PriDerv2无法访问PriDerv的私有成员，因为PriDerv是私有继承Base
    }
};

// 派生列表中的访问说明符
void test2() {
    PubDerv d1;
    PriDerv d2;
    cout << d1.h << endl;  // 0
    // cout << d2.h << endl;  // error : 派生列表的private说明符限制了h在PriDerv中是私有的

    Base *p = &d1;
    // p = &d2;  // error : 派生列表的private说明符限制了派生类向基类的访问
}

class Pal {
    void f(PubDerv & d){
        cout << d.j << endl;  // 正确，可以访问Base的私有成员，对于基类的访问权限由基类本身控制，即使对于派生类的基类部分也是如此
        // cout << d.m << endl;  // error : Pal仅仅是Base的友元，不能访问PubDerv的私有成员
    }
};

// 友元，友元不具有传递性和继承性 
void test3() {

}

class MyDerived : private Base {
public:
    using Base::h;  // 即使是使用私有继承，但是仍能提高h的访问权限为public
    using Base::i;  // 即使是使用私有继承，也能将protecte成员也提高为public
};

// 改变个别成员的可访问性
void test4() {
    MyDerived d;
    cout << d.h << endl;  // 0
    cout << d.i << endl;  // 1
}

class MyDerived2 : public Base {
public:
    int j = 3;  // 将隐藏基类的k
    void f(int a) {  // 将隐藏基类的f，即使形参不同
    }
    void f2(){  // 覆写了base的虚函数，虽然没有加override
        cout << "derived f2" << endl;
    }
    void f3(int a) {  // f3的重载版本，将隐藏基类的f3
        cout << "derived f3" << endl;
    }
    using Base::f3;  // 使用using声明，可以把被隐藏的函数，重新添加到派生类作用域中
};

void test5(){
    MyDerived2 d;
    cout << d.j << endl;  // 3
    d.f(2);
    // d.f();  // error : 没有匹配的函数。可以这样理解，首先查找名字，发现MyDerived2.f(int)，则查找过程终止，编译器将不再继续查找，然后执行函数匹配，发现不匹配
    d.Base::f();  // 正确，显示调用Base.f

    Base *p = &d;
    p->f();  // 调用的仍将是 Base f
    // p->f(2);  // error : Base中没有f(int)

    p->f2();  // 调用的是 derived f2

    d.f3();  // 正确，因为派生类使用了using声明，所以Base::f3又可见了
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