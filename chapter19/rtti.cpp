#include <string>
#include <iostream>
#include <typeinfo>
using namespace std;

class Base {
    virtual void f() {}  // 如果没有虚函数，将无法进行dynamic_cast转换
};
class Derived : public Base {

};

// dynamic
void test1(){
    Base *bp = new Derived();
    if(Derived *p = dynamic_cast<Derived*>(bp)){  // 在条件部分执行dynamic_cast操作可以确保类型转换和结果检查在同一表达式中完成

    }else{

    }

    Base &b = *bp;

    try{
        const Derived &d = dynamic_cast<const Derived&>(b);  // 当对引用的类型转换失败时，程序抛出bad_cast的异常
    }catch(bad_cast) {
        // 处理类型转换失败的情况
    }
}

void test2() {
    Derived *dp = new Derived;
    Base *bp = dp;

    // 运行时比较两个对象的类型
    if(typeid(*bp) == typeid(*dp)) {
        // bp和dp指向同一对象
    }

    // 检查运行时类型是否是某种指定的类型
    if(typeid(*bp) == typeid(Derived)) {
        // bp实际指向的是Derived对象
    }

    cout << (typeid(bp) == typeid(Derived)) << endl;  // 0，永远都是false，typeid应该作用于对象，这里比较的其实是Base *与Derived

    cout << typeid(bp).name() << endl;  // P4Base，类型名字，生成方式因系统而异

    // bp = nullptr;
    // typeid(*bp);  // 将会抛出异常bad_typeid
}

int main(){

    test1();
    test2();

    system("pause");
    return 0;
}