#include <string>
#include <iostream>
using namespace std;

void test1(){
    int i = 42;
    int &r = i;  // 正确r引用i
    // int &&rr = i;  // error : 不能将一个右值引用绑定到一个左值上
    // int &r2 = i * 42;  // error : i*42是一个右值
    const int &r3 = i * 42;  // 正确，可以加个一个const的引用绑定到一个右值上
    int &&rr2 = i * 42;  // 正确，将rr2绑定到乘法结果上

    cout << rr2 << endl;  // 1764

    rr2 = 4;

    cout << rr2 << endl;  // 4

    // int &&rr3 = rr2; // error : 表达式rr2是左值

    int &&rr4 = std::move(rr2);  // 正确，move函数可以获得绑定的左值上的右值引用

    // cout << rr2 << endl; // 4, error : 不应该再访问移后源的值

    cout << rr4 << endl;  // 4

    rr4 = 3;

    // cout << rr2 << endl;  // 3, error : 不应该再访问移后源的值

    rr2 = 9;

    cout << rr4 << endl;  // 9
}

class Test {
public:
    int a;
    int b;
};

class Test2 {
public:
    Test2() {

    }
    Test2(Test2 &&t) { // 移动构造函数

    }
    int a;
    int b;
};

void test2() {
    Test2 a;
    // Test2 b(a);  // error : 定义了移动构造函数，默认的拷贝构造函数将会被定义为删除的

    int f = 3;
    int &&b = std::move(f);
    cout << b << endl;
    b = 4;
    cout << f << endl;
}

class Foo {
public:
    Foo &operator=(const Foo&) &;  // 引用限定符，只能向可修改的左值赋值
    // Foo someMem() & const;  // error : 同时使用const和&限定符，引用限定符必须跟在const后面
    Foo someMem() const &;
    // Foo someMem();  // error : 缺少引用限定符，如果一个成员函数有引用限定符，则具有相同参数列表的所有版本都必须有引用限定符
    Foo someMem() &&;
};

Foo &Foo::operator=(const Foo &rhs) & {  // 引用限定符，声明和定义必须同时存在
    return *this;
}

Foo foo;
Foo &retFoo() {  // 返回的是一个左值引用
    return foo;
}
Foo retVal() {  // 返回的是一个值
    return foo;
}

void test3() {
    Foo i, j;  // i, j都是左值
    i = j;  // 正确，i是左值，可以向i赋值
    retFoo() = j;  // 正确，retFoo返回的是一个左值
    // retVal() = j;  // error : retVal返回的是一个右值，由于operator=限定为左值引用，所以不能赋值
    i = retVal();  // 正确
}

int main(){

    test1();
    test2();
    test3();

    system("pause");
    return 0;
}