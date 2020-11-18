#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Screen {
public:
    typedef string::size_type pos;  // 类可以自定义某种类型在类中的别名
    // using pos = string::size_type;  // 与上面等价

    Screen() = default;
    Screen(pos ht, pos wd, char c) : height(ht), width(wd), contents(ht*wd, c) {}

    char get() const {
        // height = 3;  // error : 无法通过指向常量的指针，修改值
        ttt = 4;  // 可以修改，因为ttt是可变的
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

class Window_mgr {
private:
    vector<Screen> screens{Screen(24, 80, ' ')};  // 类内初始值，直接初始化形式。当我们提供一个类内初始值时，必须以符号=或者花括号表示
};

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