#include <string>
#include <iostream>
#include <map>
#include <functional>
using namespace std;

// 以下可调用对象共享同一种调用形式 int(int, int)

int add(int i, int j) {return i + j;}

auto mod = [](int i, int j) {
    return i % j;
};

struct divide {
    int operator()(int i, int j) {
        return i / j;
    }
};

// 重载的函数
int add(int i, int j, int k) {
    return i + j + k;
}

void test1(){
    map<string, int(*)(int, int)> binops1;
    binops1.insert({"+", add});
    binops1.insert({"%", mod});
    // binops1.insert({"/", divide()}); // error : divide()不是一个函数指针

    // function<int(int, int)> f1 = add;  // error : add函数有二义性
    // 解决方法1，利用函数指针
    int(*fp)(int, int) = add;  // 指针所指的是接受两个int参数的add
    function<int(int, int)> f1 = fp; 
    // 解决方法2，利用lambda表达式
    function<int(int, int)> f11 = [](int i, int j){
        return add(i, j);  
    };

    function<int(int, int)> f2 = mod;
    function<int(int, int)> f3 = divide();
    cout << f1(4, 2) << endl;  // 6
    cout << f2(4, 2) << endl;  // 0
    cout << f3(4, 2) << endl;  // 2

    if(f1){
        cout << "true" << endl;  // true，当f作为条件，当f含有可调用对象时为真，否则为假
    }

    function<int(int, int)> f4;
    if(!f4){
        cout << "false" << endl;  // false
    }

    // 利用function重新定义map
    map<string, function<int(int, int)>> binops2;
    binops2.insert({"+", fp});
    binops2.insert({"%", mod});
    binops2.insert({"/", divide()});
    binops2.insert({"-", [](int i, int j){ return i - j;}});

    cout << binops2["-"](4, 3) << endl;  // 1
}

int main(){

    test1();

    system("pause");
    return 0;
}