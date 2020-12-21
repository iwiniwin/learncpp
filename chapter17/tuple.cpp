#include <string>
#include <iostream>
#include <tuple>
#include <vector>
#include <list>
using namespace std;

void test1(){
    tuple<size_t, size_t, size_t> three;  // 3个成员都设置为0，每个成员执行值初始化
    tuple<size_t, size_t, size_t> three2{0, 0, 1};

    tuple<string, vector<double>, list<int>> some("sss", {3.14, 4.2}, {2, 3});

    // tuple<size_t, size_t> two = {1, 2};  // error : tuple<T1, T2>::tuple(T1 t1, T2 t2)的构造函数是explict的
    tuple<size_t, size_t> two2{1, 2};  // 正确，直接初始化

    auto item = make_tuple("aaa", 3, 20.01);  // make_tuple使用初始值的类型来推断tuple的类型，item是tuple<const char*, int, double>

    cout << get<0>(item) << endl;  // aaa， 返回item的第一个成员，尖括号的值必须是一个常量表达式
    cout << get<1>(item) << endl;  // 3
    cout << get<2>(item) << endl;  // 20.01

    get<1>(item) = 4;  // 返回的是成员的引用
    cout << get<1>(item) << endl;  // 4

    typedef decltype(item) trans;  // trans是item的类型
    size_t sz = tuple_size<trans>::value;  // 表示tuple类型中成员的数量
    cout << sz << endl;  // 3
    tuple_element<1, trans>::type cnt = get<1>(item);  // tuple_element表示tuple类型中指定成员的类型，cnt是一个int
    cout << cnt << endl;  // 4

    // bool b = three == two2;  // error : 成员数量不同，不能比较
    // bool b2 = three == item;  // error : 对于第一个元素const char*与size_t不能比较
    bool b3 = three == three2;
    cout << b3 << endl;  // 0
}

tuple<int, int> f() {
    return make_tuple(1, 2);
}

void test2() {
    auto t = f();

    cout << get<0>(t) << endl;  // 1
    cout << get<1>(t) << endl;   // 2
}

int main(){

    test1();
    test2();

    system("pause");
    return 0;
}