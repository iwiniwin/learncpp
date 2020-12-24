/*
 * @Author: iwiniwin
 * @Date: 2020-12-24 20:22:14
 * @Last Modified by: iwiniwin
 * @Last Modified time: 2020-12-24 21:36:11
 * @Description: 嵌套类
 */
#include <string>
#include <iostream>
using namespace std;

class TextQuery {
public:
    typedef int INT;
    static const int a = 4;
    class QueryResult;  // 嵌套类，是一种类型成员

    // 因为QueryResult嵌套在TextQuery中，所以TextQuery可以直接使用QueryResult的名字
    QueryResult query(const QueryResult &);
};

// 嵌套类可以在外层类之外定义，注意必须以外层类的名字进行限定
class TextQuery::QueryResult {  
public:
    // 位于类的作用域内，所以不必对QueryResult形参限定
    void f(const QueryResult &){}
    void f2(INT) {  // 嵌套类可以访问到外层类的成员
        cout << a << endl;  
    }

    // 构造函数
    QueryResult();
    static int b;
};

// 嵌套类构造函数可以在外层类之外定义
TextQuery::QueryResult::QueryResult() {

}

// 内部类静态成员定义
int TextQuery::QueryResult::b = 0;

TextQuery::QueryResult TextQuery::query(const QueryResult &) {

}

void test1(){
    TextQuery::QueryResult r;
    r.f2(3);  // 4
}

int main(){

    test1();

    system("pause");
    return 0;
}