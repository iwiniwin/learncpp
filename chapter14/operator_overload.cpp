#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

// int operator+(int, int);  // error : 不能为内置类型重载运算符。对于运算符函数，至少要有一个类类型的参数

class Test {
public:
    int a = 0;
    string s = "ss";
    // 支持接收花括号内的元素列表作为参数
    Test &operator=(initializer_list<string> il);
    Test &operator+=(const Test &rhs);

    // 下标运算符通常定义常量和非常量两个版本

    string &operator[](size_t n) {
        return s;
    }

    const string &operator[](size_t n) const {
        return s;
    }

    // 前置运算符
    Test &operator++();
    Test &operator--();

    // 后置运算符，后置版本接受一个额外的（不被使用的）int类型的参数
    Test operator++(int);
    Test operator--(int);

    // 解引用运算符
    const string &operator*() const {
        return s;
    }

    string &operator*() {
        return s;
    }

    // 箭头运算符
    const string *operator->() const {
        return &this->operator*();  // 将实际工作委托给解引用运算符，返回的结果是解引用结果的地址
    }

    // string operator->() {  // error : 函数的返回类型必须是指针类型
    //     return this->operator*();  // 将实际工作委托给解引用运算符，返回的结果是
    // }

    string* operator->() {  // error : 函数的返回类型必须是指针类型
        return &this->operator*();  // 将实际工作委托给解引用运算符，返回的结果是
    }

    // 函数调用运算符
    int operator()(int val) const {
        return val < 0 ? -val : val;
    }

    // 可以重载多个函数调用运算符
    string operator()(string a, int b) {
        return "vv";
    }
};
void operator-(Test &t1, Test &t2) {

}

// 重载+运算符
Test operator+(const Test &lhs, const Test &rhs) {
    Test temp = lhs;  // 复制左侧对象的数据
    temp.a += rhs.a;
    return temp;
}

// 重载输出运算符
ostream &operator<<(ostream &os, const Test &t) {
    os << t.a;  // 输出运算符不应该打印换行符
    return os;
}

// 重载输入运算符
istream &operator>>(istream &is, Test &t) {
    is >> t.a;
    if(is){  // 检查输入是否成功
        // 输入成功
        cout << "input success : " << t << endl;
    }else{
        // 输入失败
        t = Test();  // 将对象置于为默认状态，确保对象处于正确的状态
        cout << "input failed : " << t << endl;
    }
    return is;
}

// 重载相等运算符
bool operator==(const Test &lhs, const Test &rhs) {
    return lhs.a == rhs.a;
}

bool operator!=(const Test &lhs, const Test &rhs) {
    return !(lhs == rhs);  // 这里应该直接调用==，委托它实现真正的比较操作
}

// 重载赋值运算符
Test &Test::operator=(initializer_list<string> il){
    auto beg = il.begin(), end = il.end();
    while(beg != end) {
        cout << "receive " << *beg ++ << " ";
    }
    cout << endl;
    return *this;
}

// 重载复合赋值运算符，通常也应该定义为类的成员
Test &Test::operator+=(const Test &rhs) {
    a += rhs.a;
    return *this;
}

// 重载递增前置版本
Test &Test::operator++() {
    ++ a;
    return *this;
}

// 重载递减前置版本
Test &Test::operator--() {
    -- a;
    return *this;
}

// 重载递增后置版本
Test Test::operator++(int) {   // 因为不会用到这个int形参，所以无需为其命名
    Test temp = *this;  // 记录当前值
    ++ *this;  // 调用前置版本来完成实际的工作
    return temp;  // 返回之前记录的状态
}

// 重载递减后置版本
Test Test::operator--(int) {
    Test temp = *this;
    -- *this;
    return temp;
}

void test1(){
    Test t1, t2;
    t1 - t2;
    operator-(t1, t2);  // 正确，与上句等价，可以像调用普通函数一样直接调用运算符函数

    cout << t1 << endl;  // 0
    cin >> t2;
}

void test2() {
    Test t1, t2;
    const Test t3;
    t1.a = 1;
    t2.a = 3;
    cout << (t1 + t2).a << endl;  // 4

    t1 = {"aa", "bb", "cc"};  // receive aa receive bb receive cc

    t1 += t2;
    cout << t1.a << endl;  // 4

    t1[1] = "hh";
    cout << t1.s << endl;  // hh
    cout << t3[2] << endl;  // ss
    // t3[2] = "bb";  // error : 不能对常量引用赋值

    cout << t1 << endl;  // 4
    cout << ++ t1 << endl;  // 5
    -- t1;
    cout << t1 << endl;  // 4

    cout << t1 ++ << endl;  // 4
    cout << t1 << endl;  // 5

    cout << t1.operator++(0) << endl;  // 5，显示调用后置版本
    cout << t1.operator++() << endl;  // 7，显示调用前置版本

    cout << (*t1).size() << endl;  // 2
    cout << t1->size() << endl;  // 2
}

// 可调用对象
void test3() {
    Test t1, t2;
    cout << t1(1) << endl;  // 1
    // cout << t1("bb") << endl;  // error : 没有匹配的函数
    cout << t1("bb", 1) << endl;  // vvv


    // 标准库定义的函数对象
    plus<int> intAdd;
    cout << intAdd(3, 3) << endl;  // 6

    negate<int> intNegate;
    cout << intNegate(3) << endl; // -3

    // 在算法中使用标准库函数对象
    vector<int> vec = {3, 2, 4};
    sort(vec.begin(), vec.end(), greater<int>());
    for(int a : vec) {
        cout << a << " ";  // 4 3 2
    }
    cout << endl;
}

int main(){

    // test1();
    // test2();
    test3();
    
    system("pause");
    return 0;
}