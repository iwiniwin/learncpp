#include <string>
#include <iostream>
using namespace std;

// 基类
class Quote {
public:
    Quote() = default;
    Quote(const string &block, double sales_price) : bookNo(block), price(sales_price) {

    }

    string isbn() const {return bookNo;}

    // 返回给定数量的书籍的销售总额，派生类负责改写并使用不同的折扣计算算法
    virtual double net_price(size_t n) const {
        return n * price; 
    }
    virtual ~Quote() = default;  // 对析构函数进行动态绑定

private:
    string bookNo;  // 书籍ISBN编号

protected:
    double price = 0.0;  // 代表普通状态下不打折扣的价格
};

// 派生类，public用来控制派生类从基类继承而来的成员是否对派生类的用户可见
class Bulk_quote : public Quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const string&, double, size_t, double);
    // 派生类可以访问基类的公有成员和受保护成员
    double net_price(size_t cnt) const override {
        if(cnt >= min_qty)
            return cnt * (1 - discount) * price + 3;
        else
            return cnt * price + 3;
    }
private:
    size_t min_qty = 0;  // 适用折扣政策的最低购买量
    double discount = 0.0;   // 以小数表示折扣额
};

Bulk_quote::Bulk_quote(const string &book, double p, size_t qty, double disc) : Quote(book, p), min_qty(qty), discount(disc) {

}

void test1(){
    Quote item;  // 基类对象
    Bulk_quote bulk;  // 派生类对象

    Quote *p = &item;  // p指向Quote对象
    cout << p->net_price(1) << endl;  // 0，调用的父类的方法
    p = &bulk;  // p指向bulk的Quote部分
    cout << p->net_price(1) << endl;  // 3，调用的子类的方法

    Quote &r = bulk;  // r绑定到bulk的Quote部分
    cout << r.net_price(1) << endl;  // 3
    r = item;  // // 调用的是基类默认的拷贝赋值运算符，将会逐成员的进行赋值
    cout << r.net_price(1) << endl;  // 3
    Quote &r1 = item;
    cout << r1.net_price(1) << endl;  // 0

    Quote q;
    Bulk_quote b;
    q = b;  // 调用的是基类默认的拷贝赋值运算符 Quote::operator=(const Quote&)，将会逐成员的进行赋值
    cout << q.net_price(1) << endl;  // 0，调用的仍然是父类的方法
}

class Derived;  // 派生类的声明
// class Derived : public Base;  // error : 派生类的声明不要出现派生列表

class Base {
public:
    static void statmem() {}
};

class Derived : public Base {
    void f(const Derived&);
};

void Derived::f(const Derived &derived_obj) {
    Base::statmem();
    Derived::statmem();
    derived_obj.statmem();  // 通过Derived对象访问
    statmem();  // 通过this指针访问
}

void test2() {

}

class TT;
// class UU : public TT {  // error : 如果想将某个类用作基类，则该类必须已经定义而非声明

// };

class NoDerived final {

};

// class VV : NoDerived {  // error ： NoDerived是final的，不允许被派生

// };

void test3() {

}

class MyBase {
public:
    virtual MyBase *f();
    virtual void ft();
};

class MyDerived : MyBase{
public:
    // virtual int f();  // error : 返回值不同
    
    MyDerived *f() override;  // 正确，如果基类的虚函数返回的是基类的指针或引用时，子类覆写虚函数时，可以放回子类的指针或引用
    // void f2() override;  // error : f2不是虚函数
    // MyBase *f(int) override;  // error : 形参列表不同
    MyDerived *f(int);  // 正确，定义了一个f函数数，与基类的f虚函数其实是没有关系的，实际上将基类的虚函数隐藏了
                        // 这种情况下，我们不能确定到底是因为写错了而没能成功覆写f，还是真的想定义一个不同的f函数。
                        // 所以实战中每个覆写虚函数都加上override是十分重要的，编译器将为我们检查是否覆写成功
    void ft() final;  // 正确，后面再派生的类，将不能再覆写ft虚函数

    // void ft2() final;  // error : ft2不是一个虚函数
};

class MyDerived2 : MyDerived {
public:
    // void ft() override;  // error : ft已经是final，不能再被覆写
};

void test4() {

}

class MyBase2 {
public:
    virtual int f(int a = 2) {
        cout << "base f " << a << endl;
        return a;
    }
};

class MyDerived3 : public MyBase2 {
public:
    int f(int a = 3) override {
        cout << "derived f " << a << endl;
        return a;
    }
};

// 虚函数与默认实参
void test5() {
    MyBase2 b;
    MyDerived3 d;

    MyBase2 *p = &b;
    cout << p->f() << endl;  // 2，调用的是基类版本f，默认实参是基类的2
    p = &d;
    cout << p->f() << endl;  // 2，调用的是子类版本f，但默认实参仍然是基类的2

    cout << p->MyBase2::f() << endl;  // 2，强制执行基类中的虚函数

    MyDerived3 *p2 = &d;
    cout << p2->f() << endl;  // 3，调用的是子类版本f，默认实参仍然是子类的3
}

class MyBase3 {
public:
    virtual void f() = 0;  // 纯虚函数
};

void MyBase3::f() {
    cout << "ff" << endl;
}

class MyDerived4 : public MyBase3 {
public:
    void f() override {

    }
};

// 纯虚函数
void test6() {
    // MyBase3 b;  // error : MyBase3含有纯虚函数，是抽象类，不能直接创建一个抽象类的对象
    MyDerived4 d;  // 正确
    d.MyBase3::f();  // ff，可以调用纯虚函数，纯虚函数也可以有定义
}

int main(){

    test1();
    test2();
    test3();
    test4();
    test5();
    test6();

    system("pause");
    return 0;
}