#include <string>
#include <iostream>
using namespace std;

// Token0类型的对象只有一个成员，该成员的类型可能是下列类型中的任意一种

union Token0 {
    char cval;
    int ival;
    double dval;
    void f2() {

    }
    // virtual void f() {  // error : union中不能定义虚函数

    // }
};

// class Test : public Token0 {  // error : union不能作为基类使用，因为union不是class或struct

// };

void test1(){
    Token0 a;
    cout << a.ival << endl;  // -2，默认情况下union是未初始化的

    Token0 first = {'a'};  // 初始化cval成员。如果体用了初始值则该初始值用于初始化第一个成员
    Token0 *pt = new Token0;  

    first.cval = 'c';
    pt->ival = 42;
    cout << pt->cval << endl;  // 上面为ival赋值，将会导致cval变成未定义的
}

// 匿名union，编译器将自动的为该union创建一个未命名的对象
static union {
    char cval;
    int ival;
    double dval;
    // void fff(){  // error : 匿名union不能包含成员函数

    // }
};

// 匿名union
void test2() {
    cval = 'c';  // 对于未命名的union对象，可以直接访问它的成员
}

class Token {
public:
    // 因为union含有string成员，所以Token必须定义拷贝控制成员
    Token() : tok(INT), ival(0) {}
    Token(const Token &t) : tok(t.tok) {copyUnion(t);}
    Token &operator=(const Token& t) { 
        if(tok == STR && t.tok != STR) sval.~string();
        if(tok == STR && t.tok == STR)
            sval = t.sval;  // 无需构造一个新的string
        else
            copyUnion(t);   // 如果t.tok是str则需要构造新的
        tok = t.tok;
        return *this;
    }
    ~Token() {
        // 如果union含有string成员，则必须销毁它
        if(tok == STR)
            sval.~string();
    }
    // 下面的赋值运算符赋值设置union的不同成员
    Token &operator=(const string &s) {
        if(tok == STR) {
            sval = s;
        }else{
            new(&sval) string(s);  // 利用定位new表达式，则内存中为sval构造一个string
        }
        tok = STR;
        return *this;
    }
    Token &operator=(char);
    Token &operator=(int i) {
        if(tok == STR)  // 如果当前存储的是string，则释放它
            sval.~string();  
        ival = i;
        tok = INT;  // 更新判别式
        return *this;
    }
    Token &operator=(double);

private:
    enum {INT, CHAR, DEL, STR} tok;  // 使用toke作为判别式，记录union存储的到底是什么类型的值
    union {
        char cval;
        int ival;
        double dval;
        string sval;
    };
    // 检查判别式，并酌情拷贝union成员
    void copyUnion(const Token&t) {
        switch(t.tok){
            case Token::INT:
                ival = t.ival;
                break;
            case Token::CHAR: cval = t.cval; break;
            case Token::DEL: dval = t.dval; break;
            case Token::STR: new(&sval) string(t.sval); break;  // 使用定位new构造它
        }
    }
};

// 含有类类型成员的union
void test3() {

}

int main(){

    test1();
    test2();
    test3();

    system("pause");
    return 0;
}