#include <string>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

// 普通类的成员模板
class DebugDelete {
public:
    DebugDelete(ostream &s = cerr) : os(s) {}
    // 成员函数模板
    template <typename T> void operator()(T *p) const {
        os << "delete ptr" << endl;
        delete p;
    }
private:
    ostream &os;
};

// 类模板的成员模板
template <typename T> class Blob {
public:
    Blob() = default;
    template <typename U> Blob(U b);
};

// 在类外定义成员模板时，必须同时为类模板和成员模板提供参数列表，类模板的参数在前
template <typename T>
template <typename U>
Blob<T>::Blob(U b) {

}

// 成员模板
void test1(){
    double *p = new double;
    DebugDelete d;
    d(p);  // 自动推断模板参数
    DebugDelete()(p);  // 在临时对象上调用

    unique_ptr<int, DebugDelete> p2(new int, DebugDelete());  // DebugDelete对象作为unique_ptr的删除器

    Blob<int> b(3);  // 成员模板参数由编译器推断
}

template <typename T> T com(T a){
    return T();
}

extern template class Blob<string>;  // 模板实例化声明，当编译器遇到extern模板声明时，它不会在本文件中生成实例化代码
extern template int com(int);  // 函数模板实例化声明

// 控制实例化
void test2() {
    Blob<string> sa;  // 实例化会出现在其他地方

    com(3);  // 实例化会出现在其他地方
}

template class Blob<string>;  // 模板实例化定义，此时会实例化模板的所有成员
template int com(int);  // 函数模板实例化定义

class NoDefault {
public:
    NoDefault() = delete;
};

void test3() {
    vector<NoDefault> d;  // 正确，只实例化模板用到的
    // vector<NoDefault> d2(10);  // errror : 该定义会用到NoDefault的默认构造函数，而NoDefault没有
}

// template class vector<NoDefault>;  // error ： 实例化定义，会实例化模板的所有成员，而vector有成员函数会使用类型的默认构造函数，而NoDefault没有

int main(){

    test1();
    test2();
    test3();
    

    system("pause");
    return 0;
}