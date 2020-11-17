#include <string>
using std::string;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void test1(){
    // static_cast

    int j = 1, i = 2;
    double slope = static_cast<double>(j) / i;  // 0.5

    void *p = &j;
    int *jp = static_cast<int *>(p);
    cout << *jp << endl;  // 1

    // const_cast
    const char *cp = "abc";
    // char *q = static_cast<char *>(cp);  error : 不同通过static_cast去掉cosnt性质
    string s = static_cast<string>(cp);  // 正确，字符串字面值转换成string
    s[0] = 'y';
    cout << s << endl;   // ybc
    cout << cp << endl;  // abc

    char *q1 = const_cast<char*>(cp);
    // cp[0] = 'z';  // error : 不允许修改常量
    // q1[0] = 'z';   // error : 编译可以通过，但运行会报错，尝试去修改了一个常量

    char ca[] = {'a', 'b', 'c', '\0'};
    char *q2 = ca;
    const char *q3 = const_cast<char*>(q2);
    // *q3 = 'f';  // error : 不能修改常量
    auto q4 = const_cast<const char*>(q2);
    // *q4 = 'f';  // error : 不能修改常量

    // reinterpret_cast
    int *ip;
    char *pc = reinterpret_cast<char *>(ip);
    // string str(pc);  // error : 编译可以通过，但运行会报错，因为pc本质上还是整型指针
}

int main(){

    test1();

    system("pause");
    return 0;
}