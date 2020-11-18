#include <string>
#include <iostream>
using namespace std;

struct Sales_data {
    // 友元声明，使下面的函数可以访问类的非公有成员
    friend Sales_data add(const Sales_data&, const Sales_data&);
    friend ostream &print(ostream &, const Sales_data&);
    friend istream &read(istream &, Sales_data &);
public:
    // 构造函数
    Sales_data() = default;  // 要求编译器生成默认构造函数
    Sales_data(const string &s) : bookNo(s) {}
    Sales_data(const string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p * n){}  // 构造函数初始值列表
    Sales_data(istream &);  // 构造函数的声明

    string isbn() const {  // 直接定义在类内，这里const的作用是修改隐式this指针的类型，使其可以指向常量
        // bookNo = "123";  // error : 无法通过指向常量的指针，修改值
        // avg_price2();  // error : 常量对象，以及常量对象的引用或指针都只能调用常量成员函数
        return bookNo;
    }  
    string isbn2() {
        bookNo = "123";
        return bookNo;
    }
    Sales_data& combine(const Sales_data&);  // 将被定义在类外
    double avg_price() const;
    double avg_price2();

private:
    // 数据成员
    string bookNo;  // isbn编号
    unsigned units_sold = 0;   // 某本书的销量
    double revenue = 0.0;  // 收入
};

double Sales_data::avg_price() const {  // 注意这里的const不能少
    if(units_sold)
        return revenue / units_sold;
    else
        return 0;
}

Sales_data &Sales_data::combine(const Sales_data &rhs){
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

// Sales_data的非成员接口函数
Sales_data add(const Sales_data&, const Sales_data&);
ostream &print(ostream &, const Sales_data&);
istream &read(istream &, Sales_data &);

// 类外定义的构造函数
Sales_data::Sales_data(istream &is){
    // 一些编译器允许在尚无友元函数的初始声明的情况下就调用它，不过最好还是提供一个独立的函数声明，以符合更多的编译器
    read(is, *this);
}

istream &read(istream &is, Sales_data &item){
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

ostream &print(ostream &os, const Sales_data &item){
    os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
    return os;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs){
    Sales_data sum = lhs;  // 默认情况下，拷贝类的对象其实拷贝的是对象的数据成员
    sum.combine(rhs);
    return sum;
}

void test1(){
    Sales_data data1;
    data1.isbn2();  // 默认情况下，this的类型是指向类类型非常量版本的常量指针
    const Sales_data data2;
    // data2.isbn2();  // error : 不能把this绑定到一个常量上
    data2.isbn();  // isbn函数定义将this声明成了指向常量的常量指针

    data1.combine(data2);

    
}

class Test{
public:
    int an;
    int bn;
    int cn;
    Test() = default;
};

void test2(){
    Test t;
    cout << t.an << endl;  // an是未定义的

    Test t1{2, 3};
    cout << t1.an << endl;  // an是2
    cout << t1.cn << endl;  // cn是0，值初始化

    t = t1;  // 默认的赋值操作，就是数据成员的值拷贝
    cout << t.an << endl;  // an是2
    t.an = 12;
    cout << t1.an << endl;  // an是2

    // Test t2(3);
    // cout << t2.an << endl;  
}

struct S {
    int a;  // 默认访问权限是public
};
class C {
    int a;  // 默认访问权限是private
};

void test3(){
    S s;
    C c;
    cout << s.a << endl;
    // cout << c.a << endl;  // error : 不可访问，私有的
}

int main(){
    
    test1();
    test2();
    test3();
    

    system("pause");
    return 0;
}