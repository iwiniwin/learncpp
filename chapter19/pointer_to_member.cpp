#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

class Screen {
public:
    string str = "test";

    // data是返回数据成员指针的函数
    static const string Screen::*data() {
        return &Screen::contents;
    }

    char get_cursor() const {
        return 'a';
    }

    char get() const {
        return 'b';
    }

    char get(int ht, int wd) const {
        return 'c';
    }

    using ActionType = Screen &(Screen::*)();
    enum Direction {HOME, FORWARD, BACK, UP};

    Screen &move(Direction d) {
        return (this->*menu[d])();   // menu[d]指向一个成员函数
    }

    Screen &home() {

    }

    Screen &forward() {
        
    }

    Screen &back() {
        
    }

    Screen &up() {
        
    }
private:
    string contents = "contents";
    static ActionType menu[];  // 函数表
};

Screen::ActionType menu[] = {
    &Screen::home,
    &Screen::forward,
    &Screen::back,
    &Screen::up,
};

// 数据成员指针
void test1(){
    // pdata是一个成员指针，可以指向一个常量（非常量）Screen对象的string成员
    const string Screen::*pdata;

    pdata = &Screen::str;  // 当初始化一个成员指针时，令其指向类的某个成员，但不指定成员所属的对象，直到使用成员指针时，才提供成员所属的对象
    auto pdata2 = &Screen::str;

    Screen s, *ps = &s;
    cout << s.*pdata << endl;  // test，.*运算符，首先解引用指针，然后通过.获取成员
    cout << ps->*pdata << endl;  // test

    const string Screen::*pdata3 = Screen::data();
    cout << s.*pdata3 << endl;  // contents
}

// 函数成员指针
void test2() {
    auto pmf = &Screen::get_cursor;

    // char Screen::*pmf1(int, int) const;  // error : 括号不能少，少了以后，编译器认为其是一个无效的函数声明

    char (Screen::*pmf2)(int, int) const;
    pmf2 = &Screen::get;

    Screen s, *ps = &s;

    // (s.*pmf)的括号不能少，因为调用运算符的优先级高于指针指向成员运算符的优先级
    cout << (s.*pmf)() << endl;  // a
    cout << (ps->*pmf2)(1, 3) << endl;  // c
}

using Action = char (Screen::*)(int, int) const;

// action接受一个Screen引用，和一个指向Screen成员函数的指针
Screen &action(Screen &, Action = &Screen::get) {
    cout << "enter" << endl;
}

// 使用成员指针的类型别名
void test3() {
    Action get = &Screen::get;

    Screen s;
    action(s);  // enter
    action(s, get);  // enter
    action(s, &Screen::get);  // enter
}

// 将成员函数用作可调用对象
void test4() {
    vector<string> svec = {"aaa", "bbb"};
    auto fp = &string::empty;
    // find_if(svec.begin(), svec.end(), fp);  // error : fp不是一个可调用对象

    // 使用function生成可调用对象

    function<bool(const string&)> fcn = &string::empty;
    find_if(svec.begin(), svec.end(), fcn);

    vector<string *> pvec;
    function<bool(const string*)> fp2 = &string::empty;
    find_if(pvec.begin(), pvec.end(), fp2);

    // 使用mem_fn生成可调用对象

    find_if(svec.begin(), svec.end(), mem_fn(&string::empty));  // 可以使用mem_fn生成一个可调用对象

    auto f = mem_fn(&string::empty);
    // mem_fn生成的可调用对象，既可以通过对象调用，也可以通过指针调用。可以认为mem_fn生成的可调用对象有一对重载的函数调用运算符：一个接受string*，一个接受string&
    cout << f(*svec.begin()) << endl;  // 0
    cout << f(svec.begin()) << endl;  // 0

    // 使用bind生成可调用对象
    find_if(svec.begin(), svec.end(), bind(&string::empty, placeholders::_1));
    auto f2 = bind(&string::empty, placeholders::_1);
    // 与mem_fn一样，bind生成的可调用对象的第一个实参可以是对象，也可以是指针
    cout << f2(*svec.begin()) << endl;  // 0
    cout << f2(svec.begin()) << endl;  // 0
}

int main(){

    test1();
    test2();
    test3();
    test4();

    system("pause");
    return 0;
}