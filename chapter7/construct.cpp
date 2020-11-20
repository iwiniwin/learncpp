#include <string>
#include <iostream>
using namespace std;

class ConstRef
{
public:
    ConstRef(int li);
private:
    int i;
    const int ci; 
    int &ri;  
};

// ConstRef::ConstRef(int li){
//     i = li;
//     ci = li;  // error : 常量未初始化，这里仅表示赋值操作
//     ri = i;  // error : 引用未初始化
// }

ConstRef::ConstRef(int li) : ci(li), ri(i){  // 正确，通过构造函数初始值初始化
    i = li;
}

class X {
public:
    int i;
    int j;
    int k;
    X(int val) : j(val), i(j) {  // 这里有问题，i的值将是未定义的，因为构造函数初始值列表，不限定初始化的具体执行顺序。成员的初始化顺序与它们在类定义中出现的顺序一致
        cout << "construct 2" << endl;
    }
    X(int val1, int val2) : X(val1) {  // 将先打印2再打印1，委托构造函数，使用了委托构造函数，就不能再定义自己的初始值初始化
        cout << "construct 1" << endl;
    }
    X() = default;
};

void test1(){
    X x(3);
    cout << x.i << endl;  // 未定义
    cout << x.j << endl;  // 3
    cout << x.k << endl;  // 未定义

    X y(3, 4);

    X v();  // 注意：这里是定义了一个函数，而非对象
    //  cout << v.i << endl;  // error : v是一个函数，而非类类型，没有i成员

    X z;  // 正确，使用默认构造函数初始化的对象
    cout << z.i << endl;  // 未定义

    X u = X();  // 显式地请求值初始化
    cout << u.i << endl;  // 0

    X w1{};  // 触发默认构造函数，值初始化
    cout << w1.i << endl;  // 0

    X w2{3}; // 触发X(int val)构造函数
    X w3{3, 4};  // X(int val1, int val2)构造函数
}

class T1 {
public:
    T1(int a){}
};

class T2 {
public:
    T1 t;
    // T2(){}  // error : t没有初始值
};

class T3 {
public:
    int i;
    int j;
    int k;
    T3(int i = 0, int j = 1){  // 每个参数都提供了默认值的构造函数也是默认构造函数
        cout << "construct T3" << endl;
    }
    T3(double i){  // 如果构造函数只接受一个头参，那它实际上定义了转换为此类类型的隐式转换规则
        this->i = i;
    };
    T3(string s){
        
    };
    explicit T3(int *c){  // 抑制构造函数定义的隐式转换
        
    };
    T3(char c);
    void test(const T3 &t){  // 注意这里必须是常量引用，才能实现t3.test(4.25);这种调用，因为转化过程中产生的是临时量
        i = t.i;
    }
};

// explicit T3::T3(char c){  // error : explicit不应在类外使用，应在类内声明构造函数时使用

// }

void test2(){
    // T2 t;   // error : 不能为T1合成默认构造函数

    T3 t3;
    cout << t3.i << endl;  // 未定义的

    double i =  5.62;
    t3.test(i);  // 合法，编译器将使用i自动创建一个T3对象（临时量）传递给test
    cout << t3.i << endl;  // 5

    t3.test(4.25);

    // t3.test("aff");  // error : const char [4]不能转化到const T3&，只允许一步类类型转换

    string s = "aff";
    t3.test(s);  // 正确
    T3 t4 = s;


    int u = 3;
    // t3.test(&u);  // error : int*不能自动转化为T3对象，因为T3(int *c)声明是explicit的，被抑制了
    // T3 t5 = &u;  // error : int*不能自动转化为T3对象，因为T3(int *c)声明是explicit的，被抑制了
    t3.test(T3(&u));  // 正确，实参是一个显式构造的T3对象
    t3.test(static_cast<T3>(&u));  // 正确，static_cast可以使用explicit构造函数
}

/*
聚合类，可以用花括号括起来的初始值列表进行初始化
1. 所有成员都是public的
2. 没有定义构造函数
3. 没有类内初始值
4. 没有基类，也没有virtual函数
缺点
添加或删除一个成员后，所有的初始化语句都需要更新
*/
class Data {
public:
    int a;
    string s;
// private:  // 当含有私有成员时，将不再是聚合类，不能使用初始值列表初始化了
//     int b;
};

class Da {
public:
    Da(int a){

    }
    int a;
private:
    int b;
};

void test3(){
    Data d = {3, "sdsfs"};  
    cout << d.s << endl;  // sdsfs
    Data dd{3, "ddd"};
    // Data d1 = {"dsf", 3};  // error : 初始值的顺序必须与声明的顺序一致
    // Data d2 = {3, "sdsfs", 4};   // error : 初始值列表的元素个数必须少于类的成员数量

    Da ab = {1};  // 不是聚合类，但是有对应的构造函数，也可以用花括号括起来的初始值列表进行初始化
}

class Debug {
public:
    constexpr Debug(bool b = true) : hw(b), io(b), other(b) { }  // constexpr构造函数，用于生成constexpr独享
    constexpr Debug(bool h, bool i, bool o) : hw(h), io(i), other(o) {}
    // constexpr Debug(bool h, bool i) : hw(h), io(i) {}  // error : constexpr构造函数必须初始化所有数据成员
private:
    bool hw;
    bool io;
    bool other;
};

void test4(){
    constexpr Debug io_sub(false, true, false);
}

main()
{
    test1();
    test2();
    test3();
    test4();

    system("pause");
    return 0;
}