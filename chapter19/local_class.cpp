/*
 * @Author: iwiniwin
 * @Date: 2020-12-24 21:36:32
 * @Last Modified by: iwiniwin
 * @Last Modified time: 2020-12-24 22:34:05
 * @Description: 局部类
 */
#include <string>
#include <iostream>
using namespace std;

int a, val;

void test1(int val){
    static int si;
    enum Loc {a = 1024, b};

    // Bar是test1的局部类
    struct Bar {
        Loc locVal;  // 正确，可以使用一个局部类型名
        int barVal;

        // static int c;  // error : 局部类不能含有静态成员，因为没法定义这样的成员

        void foo(Loc l = a) {  // 正确，默认实参是Loc::a
            // barVal = val;  // error : val是test1的局部变量，不能访问

            barVal = ::val;  // 正确，可以及使用全局对象
            barVal = si;  // 正确，可以使用一个局部静态对象
            locVal = b;  // 正确，使用一个枚举成员
        }

        void foo2();

        class Nested;  // 嵌套类
    };

    // void Bar::foo2() {  // erorr : 局部类的所有成员（包括函数在内）必须完整定义在类的内部
        
    // }

    class Bar::Nested {

    };
}

int main(){

    test1(3);

    system("pause");
    return 0;
}