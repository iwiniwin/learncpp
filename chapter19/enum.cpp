#include <string>
#include <iostream>
using namespace std;

enum color {red, yellow, green};  // 不限定作用域的枚举类型

// enum light {red, yellow, green};  // error : 枚举成员重复定义

enum class peppers {red, yellow, green}; // 正确，限定作用域的枚举类型

void test1(){
    color eyed = green;  // 正确，不限定作用域的枚举类型的成员位于有效的作用域内
    // peppers p = green;  // error : 自己的green访问不到，而color::green又类型错误

    color eyed2 = color::green;

    peppers p2 = peppers::green;

    // color eyed3 = 2;  // error : 2属于类型color

    int i = color::red;  // 正确，不限定作用域的枚举类型的成员隐式的转换成int
    // int j = peppers::red;  // error : 限定作用域的枚举类型成员不会隐式转换
}

enum class intTypes {
    charTyp = 8, shortTyp = 16, intTyp = 16, longTyp = 32, long_longTyp = 64
};

void test2() {
    constexpr intTypes charbits = intTypes::charTyp;
}

// enum intValues;  // error : 由于不限定作用域的枚举没有默认类型，所以声明时必须指定大小
enum intValues : unsigned long long;  // intValues的前置声明

enum class open_nodes;  // 限定作用域的枚举类型的前置声明。其有默认类型，所以可以不指定其成员大小

enum intValues : unsigned long long {
    charTyp = 255, shortTyp = 65535,
    longTyp = 4294967295UL,
};

void test3() {

}

int main(){

    test1();
    test2();
    test3();

    system("pause");
    return 0;
}