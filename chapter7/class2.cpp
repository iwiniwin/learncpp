#include <string>
#include <iostream>
#include <vector>
using namespace std;

int cursor;

class Window_mgr;  // 类的声明，前向声明，不完全类型

class Screen {
public:
    friend class Window_mgr;  // 设置友元类，该类的成员函数可以访问此类包括非公有成员在内的所有成员
    friend void f();

    typedef string::size_type pos;  // 类可以自定义某种类型在类中的别名
    // using pos = string::size_type;  // 与上面等价

    Screen() = default;
    Screen(pos ht, pos wd, char c) : height(ht), width(wd), contents(ht*wd, c) {}

    char get() const {
        // f();  // error : f未声明，因为友元声明的作用仅仅是影响作用域，而不是普通意义上的声明
        // height = 3;  // error : 无法通过指向常量的指针，修改值
        ttt = 4;  // 可以修改，因为ttt是可变的

        cout << cursor << endl;  // 访问成员cursor
        cout << this->cursor << endl;  // 显式访问成员cursor
        cout << Screen::cursor << endl;  // 显式访问成员cursor的另一种方式
        cout << ::cursor << endl;  // 访问类外定义的cursor

        return contents[cursor];
    }  // 类内定义，隐式内联
    inline char get(pos ht, pos wd) const;
    Screen &move(pos r, pos c);

    Screen &set(char);
    Screen &set(pos, pos, char);

    Screen &display(ostream &os){  // 必须要定义一个非常量版本，否则从常量display返回的对象将无法再调用set方法
        do_display(os);
        return *this;
    }

    const Screen &display(ostream &os) const{
        do_display(os);
        return *this;
    }

    void do_display(ostream &os) const{  // 定义在类内，隐式内联函数，调用do_display不会带来额外的开销
        os << contents;
    }   

private:
    mutable pos ttt = 0;  // 可变数据成员，永远不会是const，即使它是const对象的成员
    pos cursor = 0;  // 类内初始值
    pos height = 0, width = 0;
    string contents;
};

inline Screen &Screen::move(pos r, pos c){
    pos row = r * width;
    cursor = row + c;
    return *this; 
}

char Screen::get(pos r, pos c) const{
    pos row = r * width;
    return contents[row + c]; 
}

inline Screen &Screen::set(char c){
    contents[cursor] = c;
    return *this;
}

inline Screen &Screen::set(pos r, pos col, char ch){
    contents[r * width + col] = ch;
    return *this;
}

class Test {
public:
    // Test a;  // error : 类的成员类型不能是该类自己
    Test *b;  // 允许类成员是其自身类型的引用或指针
    Test &c;

    Test *next;
    Test *prev;

    void tt(Window_mgr &w);
    void tt(Window_mgr &w, int a);

    void t2(Window_mgr &w);
};

class Window_mgr {
    // friend Test;
    friend void Test::tt(Window_mgr &w);  // 使成员函数成为友元
public:
    using ScreenIndex = vector<Screen>::size_type;
    void clear(ScreenIndex);
    ScreenIndex addScreen(const Screen&);
private:
    vector<Screen> screens{Screen(24, 80, ' ')};  // 类内初始值，直接初始化形式。当我们提供一个类内初始值时，必须以符号=或者花括号表示
};

void Window_mgr::clear(ScreenIndex i){  // 这里可以直接使用ScreenIndex，因为定义在函数名Window_mgr::clear之后，已经知道是在类作用域内了
    Screen &s = screens[i];
    s.contents = string(s.height * s.width, ' ');  // Window_mgr是Screen的友元，所以可以访问Screen的私有成员
}

// 这里的ScreenIndex必须带上类名，因为定义在Window_mgr::addScreen之后，并不知道是在类作用域
Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s){
    screens.push_back(s);
    return screens.size() - 1;
}

void Test::tt(Window_mgr &w){
    Screen s =  w.screens[0];  // tt可以访问私有成员
    // cout << w.screens[0].height << endl;  // error : 不能访问height，友元关系不存在传递性
}

void Test::tt(Window_mgr &w, int a){
    // Screen s =  w.screens[0];  // error : 这个重载的tt不是友元成员函数，不能访问Window_mgr的私有成员
}

void Test::t2(Window_mgr &w){
    // Screen s =  w.screens[0];  // error : t2不是友元成员函数，不能访问Window_mgr的私有成员
}

int main(){
    // pos a;  // error : 在Screen中定义的类型别名无法直接使用
    Screen::pos a;

    Screen s;
    s.move(4, 0).set('#');  // 将光标移动到一个指定位置，然后设置该位置的字符值

    const Screen s1;

    s.display(cout).set('#');

    system("pause");
    return 0;
}