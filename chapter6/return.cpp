#include <string>
#include <iostream>
#include <vector>
using namespace std;

// 当函数结束时，其中局部对象所占用的空间也随之释放了
const string &manip(){  
    string ret = "";
    if(false)
        return ret;  // error : 返回的是局部对象的引用，将是未定义的
    else
        return "Empty";  // error: 返回的是局部临时量的引用，将是未定义的
}

char &get(string &str){
    return str[0];
}

// 列表初始化返回值
vector<string> process(){
    return {"sf", "bb"};
}

int process2(){
    return {1};
    // return {1, 2, 3};  // error : 对于内置类型，花括号列表最多包含一个值
}

void test1(){
    // cout << manip() << endl;  // error : segmentation fault

    string s("abc");
    get(s) = 'd';
    cout << s << endl;  // dbc

    int a = process2();
}

using arr = int[10];
arr *func();  // func返回一个含有10个整数的数组的指针
int (*func2())[10];  // func2返回一个含有10个整数的数组的指针
auto func3() -> int(*)[10];  // func3返回一个含有10个整数的数组的指针，尾置返回类型

int odd[] = {1, 2, 3, 4, 5};
decltype(odd) *arrPtr(int i){  // 利用decltype声明返回值类型
    return &odd;
}

int main(){

    test1();

    system("pause");
    

    bool has_error = true;

    if(has_error)
        return EXIT_FAILURE;  // 预处理变量
    else
        return EXIT_SUCCESS;
}