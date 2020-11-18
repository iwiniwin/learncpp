#include <string>
#include <iostream>
using namespace std;

bool compare(const string &, const string &){
    return false;
}

int len(const string &, const string &){

}

void test1(){
    bool (*pf)(const string &, const string &);  // 指向函数的指针

    bool *fun(const string &, const string &);  // 声明了一个func函数，返回值是bool*

    pf = compare;  // 当将函数名作为一个值使用时，会自动的转换成指针
    pf = &compare;  // 与上句等价

    cout << pf("hl", "dd") << endl;  // 可以直接使用函数的指针调用函数，无需提前解引用
    cout << (*pf)("hl", "dd") << endl;  // 与上句等价

    pf = 0;  // 正确，pf不指向任何函数

    // pf = len;  // error : 类型不匹配
}

typedef bool F(const string &, const string &);  // 函数类型
typedef decltype(compare) F2;  // 与上句等价
typedef bool (*FP)(const string &, const string &);  // 函数指针类型
typedef decltype(compare) *FP2;   // 与上句等价

void use(const string &s1, bool pf(const string &, const string &)){  // 第二个参数是函数类型，它会自动的转换成指向函数的指针

}  
// void use(const string &s1, bool (*pf)(const string &, const string &)){  // 与上句等价

// }  

// void use(const string &s1, F f){}  // 与上句等价
// void use(const string &s1, FP f){}  // 与上句等价

// 函数指针形参
void test2(){
    use("hs", compare);  // 可以直接把函数作为实参使用，会自动转换成指针
}


using FUN = bool(const string &, const string &);  // FUN是函数类型
using FUNP = bool(*)(const string &, const string &);  // FUNP是指针类型

// FUN f1(int a){  // error : FUN是函数类型，不能返回一个函数
//     return compare;
// }

FUN *f2(int a){
    return compare;
}

FUNP f3(int a){
    // return len;  // error : 类型不匹配
    return compare;
}

// auto f3(int) -> bool(const string &, const string &);  // error : 声明的f3返回类型是一个函数
auto f3(int) -> bool(*)(const string &, const string &);  // 尾置类型声明


// 返回指向函数的指针
void test3(){
    cout << f3(3)("hh", "ss") << endl;
}

int main(){

    test1();
    test2();
    test3();

    system("pause");
    return 0;
}