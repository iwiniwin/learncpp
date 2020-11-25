#include <string>
#include <iostream>
#include <functional>
using namespace std;

void check(const string& s, int i){
    cout << "call " << s << " " << i << endl;
}

void compute(int height, int redundant, int width){
    cout << "call " << height << " " << width << " " << redundant << endl;
}

ostream &print(ostream &os, const string &s, char c){
    return os << s << c << endl;;
}

ostream &printc(ostream &os, const string &s, char c){
    return os << s << c << endl;;
}

ostream &my_ref(ostream &os){
    return os;
}

void test1(){
    auto check1 = bind(check, std::placeholders::_1, 7);
    check1("slll");  // call slll 7

    auto compute1 = bind(compute, placeholders::_2, 0, placeholders::_1);
    int width = 1, height = 2;
    compute1(width, height);  // call 2 1 0

    // auto print1 = bind(print, cout, placeholders::_1, '.');  // error : ostream不能被拷贝
    auto print2 = bind(print, ref(cout), placeholders::_1, '.');  // ref返回一个对象，保存给定的引用，此对象是可以拷贝的
    print2("hello");  // hello.


    auto print3 = bind(print, placeholders::_1, placeholders::_2, '.');
    print3(cout, "world");  // world.

    // auto print4 = bind(print, my_ref(cout), placeholders::_1, '.');  // error
}

int main(){

    test1();

    system("pause");
    return 0;
}