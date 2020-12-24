#include <string>
#include <iostream>
using namespace std;

class Test {
public:
    Test() = default;
    Test(const volatile Test&) {  // 通过一个volatile对象进行拷贝

    }
};

void test1(){
    volatile int dr;  // 该int值可能发生改变
    volatile int* cur;  // cur指向一个volatile对象
    volatile int iax[3];  // iax的每个元素都是volatile
    volatile Test t;  // t的每个成员都是volatile的

    int *volatile vip;  // vip是一个volatile指针，它指向int
    volatile int *ivp;  // ivp是一个指针，它指向一个volatile int
    volatile int *volatile vivp;  // vivp是一个volatile指针，它指向volatile int

    // int *ip = &dr;  // error : 必须使用指向volatile int的指针
    ivp = &dr;
    vivp = &dr;
}

int main(){

    test1();

    system("pause");
    return 0;
}