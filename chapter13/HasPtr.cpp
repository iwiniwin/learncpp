#include <string>
#include <iostream>
using namespace std;

// 行为像值的类
class HasPtr1 {
public:
    friend void swap(HasPtr1&, HasPtr1&);  // 定义一个自己版本的swap，定义成友元以便可以访问私有成员
    HasPtr1(const string &s = string()) : ps(new string(s)), i(0) {}
    HasPtr1(const HasPtr1& p): ps(new string(*p.ps)), i(p.i) {}  // 拷贝构造函数，拷贝时，重新创建新的string。这里不用使用delete ps，是因为这是构造函数，ps还没分配呢
    HasPtr1& operator=(const HasPtr1 &);
    HasPtr1& operator=(int) {  // 支持重载拷贝赋值运算符
    }
    ~HasPtr1(){
        delete ps;
    }
    string *ps;
private:
    int i;
};

inline void swap(HasPtr1 &lhs, HasPtr1 &rhs){
    using std::swap;

    // 注意，如果使用的是内置类型，则可以使用std::swap，而如果是类类型，且定义了自己的swap，则应该调用类自己的swap函数
    // 所以下面的swap都应该是未限定的，直接写swap，而不是std::swap
    // 如果存在类型特定的swap版本，swap调用会与之匹配，如果不存在类型特定版本，则会使用std中的版本

    swap(lhs.ps, rhs.ps);  // 交换指针，而不是string数据
    swap(lhs.i, rhs.i);  // 交换int成员
}

HasPtr1& HasPtr1::operator=(const HasPtr1 &rhs) {
    auto newp = new string(*rhs.ps);
    delete ps;  // 释放旧的内存
    ps = newp;  

    /////////////
    // 注意不能这样写， 如此的话，如果rhs和this是同一个对象，则相当于从已释放的内存中拷贝数据
    delete ps;
    ps = new string(*rhs.ps);  
    /////////////

    i = rhs.i;
    return  *this;
}

// 行为像指针的类
class HasPtr2{
public:
    HasPtr2(const string &s = string()) : ps(new string(s)), i(0), use(new size_t(1)) {}  // 构造函数，将引用计数初始化为1
    HasPtr2(const HasPtr2 &p) : ps(p.ps), i(p.i), use(p.use) { ++ *use; }  // 拷贝构造函数，拷贝数据成员，并递增计数器。注意不能写成 *use++。因为++的优先级大于解引用
    HasPtr2& operator=(const HasPtr2 &);
    ~HasPtr2();
    string *ps;
private:
    int i;
    size_t *use;  // 引用计数，用来记录有多少个对象共享*ps的成员
};

HasPtr2& HasPtr2::operator=(const HasPtr2 &rhs) {
    // 递增右侧运算对象的引用计数
    ++ *rhs.use;
    if(-- *use == 0) {  // 然后递减本对象的引用计数
        delete ps;
        delete use;
    }
    i = rhs.i;
    ps = rhs.ps;
    use = rhs.use;
    return *this;
}

HasPtr2::~HasPtr2(){
    if(-- *use == 0){  // 每析构一次，递减引用计数
        delete ps;
        delete use;
    }
}

void test1(){
    HasPtr1 a1("aaa"), a2(a1);
    cout << *a1.ps << " " << *a2.ps << endl;  // aaa aaa
    *a1.ps = "aa1";
    cout << *a1.ps << " " << *a2.ps << endl;  // aa1 aaa

    HasPtr1 a3("aaa"), a4;
    a4 = a3;
    cout << *a3.ps << " " << *a4.ps << endl;  // aaa aaa
    *a3.ps = "aa1";
    cout << *a3.ps << " " << *a4.ps << endl;  // aa1 aaa





    HasPtr2 b1("bbb"), b2(b1);
    cout << *b1.ps << " " << *b2.ps << endl;  // bbb bbb
    *b1.ps = "bb1";
    cout << *b1.ps << " " << *b2.ps << endl;  // bb1 bb1




    HasPtr2 b3("bbb"), b4("bb2");
    cout << *b3.ps << " " << *b4.ps << endl;  // bbb bb2
    *b3.ps = "bb1";
    cout << *b3.ps << " " << *b4.ps << endl;  // bb1 bb2

    b4 = b3;
    cout << *b3.ps << " " << *b4.ps << endl;  // bb1 bb1
    *b3.ps = "bb2";
    cout << *b3.ps << " " << *b4.ps << endl;  // bb2 bb2
}

void test2(){
    HasPtr1 h;
    h = 3;
}

int main(){

    test1();
    test2();

    system("pause");
    return 0;
}