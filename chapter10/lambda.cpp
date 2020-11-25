#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void print(vector<string> &vecs){
    for(auto &s : vecs){
        cout << s << " ";
    }
    cout << endl;
}

void print(vector<int> &vecs){
    for(auto &s : vecs){
        cout << s << " ";
    }
    cout << endl;
}

void test1(){
    auto f = [](int ,float) -> void {
        
    };

    // 可以忽略参数列表和返回类型。如果省略返回类型则根据函数体中的代码推断出返回类型
    auto f2 = [] {
        return 42;
    };
    cout << f2() << endl;  // 42 调用lambda表达式

    // auto f3 = () -> int {  // error : 不能省略捕获列表
    //     return 42;
    // };

    auto f4 = [](int a) {
        return a;
    };
    cout << f4(30) << endl;

    auto f5 = [](int a = 3) {
        return a;
    };
    cout << f5() << endl;

    int i = 1, j = 2;
    static int k = 3;

    auto f6 = [](){
        // cout << j << endl;  // error : j并没有被捕获，不能使用
        cout << k << endl;  // 可以使用局部静态变量
    };
    f6();

    auto f7 = [i, j](){  // 值捕获，与参数不同，i，j是在lambda创建时拷贝初始化，而不是调用时
        // 可以使用cout，可以直接使用lambda所在函数之外的名字
        cout << i << " " << j << endl;  // 1 2

        // i = 0;  // error : i是只读的
    };

    f7();

    auto f8 = [&i, &j]{  // 引用方式捕获
        cout << i << " " << j << endl;  // 1 2
        i = 0;
    };
    f8();

    cout << i << " " << j << endl;  // 0 2

    auto f9 = [=]{  // 隐式值捕获，让编译器根据lambda体中的代码来推断要使用哪些变量
        cout << i << " " << j << endl;  // 0 2
        // i = 1;  // error : i是只读的
    };
    f9();

    auto fx = [&]{  // 隐式引用捕获，让编译器根据lambda体中的代码来推断要使用哪些变量
        cout << i << " " << j << endl;  // 0 2
        i = 1;
    };
    fx();
    cout << i << " " << j << endl;  // 1 2

    auto fx1 = [&, j]{  // 混合使用隐式捕获和显式捕获，默认都是引用捕获，j是值捕获
        cout << i << " " << j << endl;  // 1 2
        i = 0;
        // j = 1;  // error : j是只读的
    };
    fx1();

    auto fx2 = [=, &j]{  // 混合使用隐式捕获和显式捕获，默认都是值捕获，j是引用捕获
        cout << i << " " << j << endl;  // 0 2
        // i = 0;  // error : i是只读的
        j = 3;
    };
    fx2();

    // auto fx3 = [i, &]{  // error : 当混合使用隐式和显式捕获时，捕获列表的第一个元素必须是&或=

    // };

    // 可变lambda，与修改值捕获的变量
    auto fx4 = [i, j] ()mutable {
        cout << i << " " << j << endl;  // 0 3
        i = 4;  // 修改的只是i的拷贝，不会改变外面i的值
        cout << i << " " << j << endl;  // 4 3
    };
    fx4();

    cout << i << " " << j << endl;  // 0 3
}

void test2(){
    vector<string> vecs = {"sss", "dd"};
    stable_sort(vecs.begin(), vecs.end(), [](const string &a, const string &b){  // 给算法传递lambda表达式
        return a.size() < b.size();
    });
    print(vecs);  // dd sss
}

void test3(){
    vector<int> veci = {1, 2, 3, -1, -2, 4, -3};
    // 利用transform算法，将序列中的每个负数替换为其绝对值，第三个参数表示将结果写到的目的位置
    transform(veci.begin(), veci.end(), veci.begin(), [](int i){
        return i < 0 ? -i : i;
    });
    print(veci);  // 1 2 3 1 2 4 3
}

int main(){

    test1();
    test2();
    test3();

    system("pause");
    return 0;
}