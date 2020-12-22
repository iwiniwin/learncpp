#include <string>
#include <iostream>
using namespace std;

namespace space1 {
    inline namespace space2 {
        int a = 1;
    }
    namespace space3 {
        int b = 2;
        int bb = 3;
        namespace space4 {
            int bbb = 4;
        }
    } 
    // 未命名的命名空间，定义的变量拥有静态生命周期，在第一次使用前创建，并直到程序结束才销毁
    namespace {
        int c = 3;  // c是静态的
    }
}

void test1(){
    cout << space1::space2::a << endl;  // 1
    cout << space1::a << endl;  // 1，正确，space2是内联的，内联命名空间的名字可以被外层空间直接使用

    cout << space1::space3::b << endl;  // 2
    // cout << space1::b << endl;  // error 

    cout << space1::c << endl;  // 3
}

// 定义space1::space3的别名为space1_3
namespace space1_3 = space1::space3;

// 命名空间别名
void test2() {
    cout << space1_3::b << endl;  // 2

    using space1::space3::b;  // using声明语句，一次只引入命名空间的一个成员，它的有效范围从using声明开始的地方开始，一直到using声明所在作用域结束为止
    cout << b << endl;  // 2

    using namespace space1::space3;   // using指示，一次性注入命名空间的所有名字
    cout << bb << endl;  // 3

    cout << space4::bbb << endl;  // 4
}

namespace ns {
    int a = 2;
}

void test3() {
    int a = 1;
    // using ns::a;  // error : a已经声明了
    using namespace ns;
    cout << a << endl;  // a是1
}

namespace ns2 {
    class Test {

    };
    void t1(Test t) {

    }
    void t2() {

    }
}

void test4() {
    ns2::Test t;
    t1(t);  // 正确，当给函数传递一个类类型的对象时，除了在常规的作用域查找外，还会查找实参类所属的命名空间。对于传递类的引用或指针的调用同样有效
    // t2();  // error : t2未定义
}

int main(){

    test1();
    test2();
    test3();
    test4();

    system("pause");
    return 0;
}