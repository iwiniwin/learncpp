#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main(){

    int null = 0;
    // int *p = null;  // error : 不能将int转化为int *
    // int *p2 = 3;  // error : 不能将int转化为int *
    int *p3 = nullptr;  // 正确 : 空指针
    int *p4 = 0;  // 正确 : 空指针

    system("pause");
    return 0;
}