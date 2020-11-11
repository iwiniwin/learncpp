#include <string>
using std::string;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <stdexcept>

void test1(){
    // else与离它最近的尚未匹配的if匹配
    if(true)
        if(false)
            cout << "11" << endl;
    else
        cout << "22" << endl;  // 会执行22

    if(false)
        if(false)
            cout << "11" << endl;  // 不会执行
    else
        cout << "22" << endl;  // 不会执行
}

void test2(){
    char a = 'a';
    switch(a){
        case 'a':
            // string s;  // error : 控制流可能绕过一个隐式初始化的变量
            // string str = "";  // error : 控制流可能绕过一个显示初始化的变量
            a = 'b';
            cout << "enter a" << endl;
            break;
        // case a:  // error : case标签必须是常量
        case 'b':
            {
                string s1;
                string str1;
                cout << "enter b" << endl;
            }
            break;
        case 'c':
            cout << "enter c" << endl;
            break;
        default:
            ;
    }
}

void test3(){
    do{
    
    // }while(int a = 3);  // error : 不允许在条件部分定义变量，因为do_while是先执行语句后判断条件，这样就相当于变量的使用出现在定义之前
    }while(false);

    // do{
    //     bool b = false;
    // }while(b);  // error : b是未定义的
}

void test4(){
    int a = 0;
a:  // 标签名独立于变量和其他标识符
    // int a = 0;  // 如果a定义在这里（标签内），则a每次都会被重新销毁再创建
    a ++;
    if(a > 2)
        return;
b:
    // goto c;  // error : 错误这里不能goto c，因为goto语句不能将程序的控制权从变量的作用域之外转到作用域之内
    int b = 0;
    b = 1;
    cout << "bbb" << endl;
c:
    b = 4;
    cout << "ccc" << endl;


    goto a;
    // goto c;  // 无限循环
}

void test55(){
    throw std::runtime_error("failed!!!");  // 抛出一个异常
}

void test5(){
    try{
        int a = 3;
        test55();
    }catch(std::runtime_error err){
        // a = 3;  // error : catch语句内也无法访问到try语句定义的变量
        cout << err.what() << endl;  // 输出 failed!!!
    }
}

int main(){
    test1();
    test2();
    test3();
    test4();
    test5();

    system("pause");
    return 0;
}