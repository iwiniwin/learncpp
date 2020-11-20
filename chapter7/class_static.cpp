#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Account {
    
public:
    void calculate(){
        amount += amount * interestRate; 
    }
    static double rate(){
        return interestRate;
    }
    static void rate(double);  // static关键字只出现在类内部的声明语句中，外部定义的时候不要有
    static constexpr int aa = 30;
    void tss(double c = interestRate){  // 区别2，静态成员可以作为默认实参

    }
    // void tss1(double c = amount){  // error : 非静态成员不行

    // }
private:
    string owner;
    double amount;
    static double interestRate;  // 类的静态成员存在于任何对象之外，一般来说不能在类的内部初始化静态成员
    static double initRate();  // 静态成员函数，不包含this指针，所以无法调用非静态成员函数
    // static double tt() const;  // 静态成员函数不能声明成const
    // static double ab = 0.0;  // error : 普通的静态成员不能在类内初始化
    static constexpr int period = 30;  // 允许字面值静态常量类内初始化
    // static const double pp1 = 0.0;  // error : 类内只能初始化整型的静态常量
    static constexpr double pp2 = 0.0;

    static Account acc;  // 区别1，静态成员可以是它所属的类类型，静态成员可以是不完全类型
    // Account acc1; // error : 非静态成员不行
};

// 静态数据成员的定义，一旦被定义，将一直存在于程序的整个生命周期中。
double Account::interestRate = initRate();  // 从类名开始，这条语句的剩余部分就都位于类的作用域之内了

// 即使一个静态数据成员在类内部被初始化了，通常情况下也应该在类的外部定义一下
constexpr int Account::aa;  // 因为下面的代码会使用引用Account::aa，所以必须在类外定义，否则会提示aa未定义

void Account::rate(double newRate){
    interestRate = newRate;
}

double Account::initRate(){
    return 3.14;
}

void test(const int &a){ 
    cout << a << endl;
}

int main(){

    double r = Account::rate();
    cout << r << endl;

    Account::rate(3.15);

    Account ac1;
    cout << ac1.rate() << endl;
    
    test(Account::aa);

    system("pause");
    return 0;
}