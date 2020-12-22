#include <string>
#include <iostream>
using namespace std;

class Base1 {
public:
    Base1(int) {}
    virtual void print() {
        cout << "base1 print" << endl;
    }
};

class Base2 {
public:
    Base2(int){}
    virtual void print() {
        cout << "base2 print" << endl;
    }
};

class D1 : public Base1, public Base2 {
public:
    D1(int a) : Base1(a), Base2(a) {

    }
};

class D2 : public Base1, public Base2 {
public:
    D2(int a) : Base1(a), Base2(a) {

    }
    void print() override {
        cout << "d2 print" << endl;
    }
};

void test1(){
    D1 d(1);
    // d.print();  // error : print有二义性，两个父类都有
    d.Base1::print();  // base1 print显式调用Base1的print

    D2 d2(2);
    d2.print();  // d2 print

    Base1 *pb1 = &d2;
    pb1->print();  // d2 print

    Base2 b(2);
    Base2 *pb2 = &b;
    pb2->print();  // base2 print
}

int main(){

    test1();

    system("pause");
    return 0;
}