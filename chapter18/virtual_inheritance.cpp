#include <string>
#include <iostream>
using namespace std;

class Base {
public: 
    Base(int){
        cout << "base construct" << endl;
    }
    int a = 3;
};

// 虚继承，virtual说明符表明在后续的派生类当中共享虚基类的同一份实例
class Derived : public virtual Base {
public:
    Derived(int a) : Base(a) {
        cout << "Derived construct" << endl;
    }
    int a = 4;
};

class Derived2 : virtual public Base {
public:
    Derived2(int a) : Base(a) {
        cout << "Derived2 construct" << endl;
    }
};

// Derived_Derived对象中将只有一个Base基类对象
class Derived_Derived : public Derived, public Derived2 {
public:
    Derived_Derived(int a) : Base(a), Derived(a), Derived2(a) {  // 因为虚基类对象只有一份，所以由最底层派生类来直接初始化
        cout << "Derived_Derived construct" << endl;
    }
};

void test1(){
    Derived_Derived d(3);  // 会先调用Base构造函数，然后Derived， 然后Derived2，最后Derived_Derived。整个过程Base构造函数只会调用一次
    Base *p = &d;

    cout << d.a << endl;  // 4， 使用的是Derived::a,因为派生类的a比共享需基类的a优先级高。同时，如果Derived没有定义a，则会打印3，不存在二义性，因为内部只有一个Base对象
}

int main(){

    test1();

    system("pause");
    return 0;
}