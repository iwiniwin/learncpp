#include <string>
#include <iostream>
using namespace std;

void test1(){
    try{

    }catch(...){  // ...可以用来捕获所有异常
        throw;  // 空的throw语句，可以重新抛出异常，只能出现在catch语句或catch语句调用的函数中
    }

    // throw;  // exception : 不是在catch语句中调用，程序将直接调用terminate终止
}

class Base {
public:
    Base(int a) {}
};

class Test : public Base {
public:
    Test(int a);
};

// 函数try语句块使得一组catch语句既能处理构造函数体（或析构函数体），也能处理构造函数的初始化过程（或析构过程），必须处理构造函数的初始值列表
Test::Test(int a) try : Base(a) {

} catch(...) {

}

// 函数try语句块
void test2() {

}

void recoup(int) noexcept;  // 表示该函数不会抛出异常
void recoup(int) throw();  // 等价的声明，不会抛出异常

// void recoup(int) {  // error : 所有的声明与定义都应该带上noexcept

// }

void recoup(int) noexcept {
    cout << "vvv" << endl;
}

void aaa(int) noexcept(true){}  // aaa不会抛出异常
void bbb(int) noexcept(false){}  // bbb可能会抛出异常

class Base2 {
public:
    virtual double f1(double) noexcept;
    virtual int f2() noexcept(false);
    virtual void f3();
};

class Derived : public Base2 {
public:
    // double f1(double) override;  // error : f1声明不会抛出异常
    double f1(double) noexcept override;

    int f2() noexcept(false) override;

    void f3() noexcept override;  // 正确，虽然基类的f3是可以抛出异常的，但是派生类可以做更严格的限定
};

// noexcept
void test3() {
    cout << noexcept(recoup(3)) << endl;  // 1, recoup不会抛出异常，所以noexcept运算符会返回true。与sizeof一样，并不会真的计算运算对象的值

    void (*pf1)(int) noexcept = recoup;  // 正确，pf1和recoup都承诺不会抛出异常
    void (*pf2)(int) = recoup;  // 正确，即使pf2可能抛出异常，仍然可以指向不会抛出异常的recoup

    pf1 = aaa;
    // pf1 = bbb;  // error : pf1说明它不会抛出异常，但bbb可能会抛出异常
}

int main(){

    test1();
    test2();
    test3();

    system("pause");
    return 0;
}