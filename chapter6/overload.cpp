#include <string>
#include <iostream>
using namespace std;

bool lookup();
// int lookup();  // error : 不允许两个函数除了返回类型外其他要素都相同

typedef int tt;
tt tes(){

}
// int tes(){  // error : 重复定义

// }

int test0(const int a){

}

// int test0(int a){  // error : 重复定义

// }


/*
编译器可以通过实参是否是常量来推断应该调用哪个函数
*/

int test1(int &a){
    return 3;
}

int test1(const int &a){
    return 2;
}

const string &test33(const string &s1, const string &s2){
    return s1;
}

string &test33(string &s1, string &s2){
    auto &s = test33(const_cast<const string&>(s1), const_cast<const string&>(s2));
    return const_cast<string&>(s);
}

void test3(){
    string s1 = "aa";
    string s2 = "bb";
    test33(s1, s2);
}

void test44(int a);
void test44(const string &s);

void test4(){
    void test44(int a);
    // test44("aa");  // error : 局部作用域内声明了void test44(int a);，所以外部作用域的void test44(const string &s);将会被隐藏，不可见
}

void test55(int a){
    cout << "int test55" << endl;
}
void test55(double a){
    cout << "double test55" << endl;
}

void test5(){
    test55(3);  // 调用int
    test55(3.14);  // 调用double
}

void sss(int a, int b, char c){
    cout << a << " " << b << " " << c << endl;
}

char a = 'a';
void sss(int, int, char = a);  // 可以使用非局部变量作为默认实参
// void sss(int, int, char = 'b');  // error : 重复声明
void sss(int = 4, int = 3, char);  // 正确

void test6(){
    sss();  // 输出 4 3 a
    a = 'b';
    sss();  // 输出 4 3 b
}

void f(int, int){

}
void f(double, double){

}

void fu(long){}
void fu(float){}

void test7(){
    f(3, 3);
    f(3.14, 3.14);
    // f(4, 3.14);  // error : 二义性

    // fu(3.14);  // error : 二义性，3.14的类型是double，它既能转换成long也能转换成float
}

int calc(char*){}
int calc(const char*){}
// int calc(char* const){}  // error : 重复定义 与  int calc(char*){}，顶层const不影响传入函数的对象
 
// int main(int argc, char *argv[]){  error : main函数不支持重载

// }

int main(){
    int a = 0;
    cout << test1(a) << endl;  // 3，当传递一个非常量对象或指针时，编译器会优先选用非常量版本
    const int b = 0;
    cout << test1(b) << endl;  // 2

    test3();
    test4();
    test5();
    test6();
    test7();


    system("pause");
    return 0;
}