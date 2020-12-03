#include <string>
#include <iostream>
#include <memory>
#include <list>
#include <vector>
using namespace std;

void test1(){
    shared_ptr<string> pl;   // 默认初始化的智能指针保存着一个空指针

    shared_ptr<list<int>> p2;

    shared_ptr<string> pl3;

    if(pl && pl->empty()){  // pl可以作为条件判断，如果pl不为空，并且指向的是一个空string
        *pl = "sss";  // 修改pl指向的字符串值
    }

    cout << pl.get() << endl;  // 0，返回pl中保存的指针，这里0表示是空指针

    swap(pl, pl3);  // 交换pl和pl3的指针
}

void test2(){
    /* make_shared */
    // 指向一个值为42的int的shared_ptr
    shared_ptr<int> p1 = make_shared<int>(42);

    shared_ptr<string> p2 = make_shared<string>(10, '5');

    shared_ptr<int> p5 = make_shared<int>();
    cout << *p5 << endl;  // p5指向的int，值初始化

    auto p6 = make_shared<vector<string>>();

    /* shared_ptr拷贝和赋值 */
    auto p = make_shared<int>(42);  // p指向的对象只有p一个引用者
    auto q(p);  // q是p的拷贝，p和q指向相同对象，此对象有两个引用者

    auto r = make_shared<int>(42);
    r = q;  // 给r赋值，递增q指向的对象的引用计数，递减r原来指向的对象的引用计数，r原来指向的对象已经没有了引用者，会自动释放
}

/* 多个对象间数据共享
StrBlob使用默认版本的拷贝，赋值和销毁成员函数，而StrBlob类只有一个shared_ptr数据成员，所以当操作StrBlob对象时，它的shared_ptr成员会被拷贝，赋值和销毁 
对于由StrBlob构造函数分配的vector，当最后一个指向它的StrBlob对象被销毁时，它会随之被销毁
*/
class StrBlob {
public:
    typedef vector<string>::size_type size_type;
    StrBlob();
    StrBlob(initializer_list<string> il);
    size_type size() const {return data->size();}
    bool empty() const {return data->empty();}
    // 添加和删除元素
    void push_back(const string &t) {data->push_back(t);}
    void pop_back();
    // 元素访问
    string &front();
    string &back();
private:
    shared_ptr<vector<string>> data;
    // 如果data[i]不合法，则抛出异常
    void check(size_type i, const string &msg) const;
};

StrBlob::StrBlob() : data(make_shared<vector<string>>()) {}
StrBlob::StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {}

void StrBlob::check(size_type i, const string &msg) const {
    if(i >= data->size())
        throw out_of_range(msg);
}

string &StrBlob::front(){
    check(0, "front on empty StrBlob");
    return data->front();
}

string &StrBlob::back(){
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back(){
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

void test3(){
    StrBlob b1;
    StrBlob b2 = {"aa", "bb"};
    b1 = b2;  // b1和b2将共享一个vector
    b2.push_back("cc");

    cout << b1.size() << endl;  // 3
}

void test4(){
    shared_ptr<string> p;
    p.reset(new string("ss"));  // 将p指向新分配的内存，reset会更新引用计数，如果需要的话，会释放p之前所指向的对象

    cout << p.use_count() << endl;  // 1，返回与p共享对象的智能指针的数量

    if(!p.unique())  // 如果p.use_count 为1返回true，否则返回false
        p.reset(new string(*p));  // 我们不是唯一用户，修改值之前，拷贝一份
    *p += "vv";
    cout << *p << endl;  // ssvv
}

// 删除器，参数必须是shared_ptr<T>的T元素的指针
void my_delete(int *p){
    cout << "delete p" << endl;
    delete p;
}

void test5_a(){
    shared_ptr<int> p(new int(42), my_delete);
}

// 自定义释放操作
void test5(){
    test5_a();
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