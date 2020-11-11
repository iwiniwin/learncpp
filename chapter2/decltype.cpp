#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int f(){
    cout << "execute" << endl;
    return 0;
}

int main(){
    decltype(f()) m = 3;  // f不会执行

    const int ci = 0, &cj = ci;
    decltype(ci) x = 0;  // x的类型是const int
    decltype(cj) y = x;  // y的类型是const int &，y绑定到x
    // decltype(cj) z;  // error : z是一个引用必须初始化

    int j = 0, &k = j; 
    decltype(k) n = j;  // n是引用，绑定到j
    n = 4;
    cout << j << endl;

    int i = 42, *p = &i, &r = i;
    decltype(r + 0) b;  // 正确，b是未初始化的int

    // 如果表达式的内容是解引用操作，则decltype将得到引用类型
    // decltype(*p) c;  // error : c是int &，必须进行初始化

    (j) = 7;
    cout << j << endl;
    // 如果decltype使用的是一个不加括号的变量，则得到的结果就是该变量的类型，如果给变量加上了一层或多层括号，编译器就会把它当成是一个表达式，得到引用类型
    decltype(j) d;  // 正确，d是一个未初始化的int
    // decltype((j)) e;  // error : e是int &，必须初始化

    int a = 3, bb = 4;
    decltype(a) c = a;
    // 赋值时产生引用的一类典型表达式，引用的类型就是左值的类型
    decltype(a = bb) dd = a;  // 注意这里的a = bb是不会执行的
    cout << a << " " << bb << " " << c << " " << dd << endl;  // 3 4 3 3 
    a ++;
    cout << a << " " << bb << " " << c << " " << dd << endl;  // 4 4 3 4 

    int *q = &j;
    decltype(*q) dq = j;  // dq是引用类型

    system("pause");
    return 0;
}