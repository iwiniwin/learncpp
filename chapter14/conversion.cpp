#include <string>
#include <iostream>
using namespace std;

class SmallInt {
public:
    // 转换构造函数，可以由int向类类型转换
    SmallInt(int i = 0) : val(i){

    }

    // 类型转换运算符，可以由类类型转化为int，隐式的
    operator int() const {return val;}

    // operator string() const {  // error : 返回值类型不对
    //     return val;
    // }

    // operator string(int a) const {  // error : 类型转化运算符参数列表必须为空
    //     return "";
    // }

    // 显式的类型转换运算符
    explicit operator string() const {return "vv";}

    // 显式的类型转换运算符，但是当该对象被用作条件时，编译器仍然会自动转换
    explicit operator bool() const {return false;}

private:
    size_t val;
};

void test1(){
    SmallInt si;
    si = 4;  // 首先int隐式转换为SmallInt，然后调用operator=运算符
    int j = si + 3;  // 类类型隐式转换为int


    SmallInt si2 = 3.14;  // 内置类型double转换成int，int通过构造函数隐式转换成类类型
}

void test2() {
    SmallInt i;
    // string s = i;  // error : 不能将SmallInt类型隐式转化为string
    string s = static_cast<string>(i);  // 正确，显式的请求类型转换
    cout << s << endl;  // vv

    if(i){  // 当表达式被用作条件时，编译器会将显式的类型转换自动应用于它
 
    }else {
        cout << "false" << endl;  // false
    }
}

struct B;
struct A {
    A() = default;
    A(const B& b) {  // 可以将B转换为A
        cout << "conversion construct" << endl;
    }
};

struct B {
    operator A() const {  // 可以将B转换成A
        cout << "operator A()" << endl;
        return A();
    }
};

A f(const A &a) {
    return a;
}

void test3() {
    B b;
    // error : 下面的代码应该错误的，有二义性，无法确定应该通过转换构造函数还是转换运算符完成转换
    // A a = f(b);  // error : 二义性，但实际代码执行，优先使用转换构造函数
    // A a = static_cast<A>(b);  // error : 二义性，但实际代码执行，优先使用转换构造函数

    A a = b.operator A();  // 正确，显式调用类型转换运算符
    A a2 = A(b);  // 正确，显式调用转换构造函数
}

int main(){

    test1();
    test2();
    test3();

    system("pause");
    return 0;
}