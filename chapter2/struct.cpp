#include <string>
using std::string;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

struct Foo {
    // 类内初始值，在声明类的数据成员时同时提供的初始值，必须置于等号右侧或花括号内
    int a = {3};
    string b= "ss";
    int u{4};
};

struct Sales_data{
    string bookNo;
    unsigned unitsSold = 0;
    double revenue = 0.0;
};

int main(){

    Foo f;
    string c("uuu");
    int d(7);
    int g{8};
    cout << f.a << " " << f.b << " " << f.u << endl;
    cout << c << " " << d << " " << g << endl;

    system("pause");
    return 0;
}