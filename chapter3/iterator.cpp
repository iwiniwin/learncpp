#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <deque>
using namespace std;

void print(vector<int> &vec){
    for(auto i : vec){
        cout << i << " ";
    }
    cout << endl;
}

void print(deque<int> &vec){
    for(auto i : vec){
        cout << i << " ";
    }
    cout << endl;
}

void test1()
{
    vector<int> vec{1, 2};
    auto b = vec.begin();   // 指向第一个元素的迭代器
    auto e = vec.end();     // 指向尾元素下一个位置的迭代器，尾后迭代器
    cout << *(b) << endl;   // 通过解引用迭代器获取它所指示的元素，值是1
    cout << *(b++) << endl; // b++，令b指向容器中的下一个元素
    // cout << *e << endl;  // 非法，解引用尾后迭代器是未被定义的行为

    string s("some string");
    for (auto it = s.begin(); it != s.end(); it++)
    {
        *it = toupper(*it);
    }
    cout << s << endl;

    vector<int>::iterator it;        // 能读写vector<int>的元素
    vector<int>::const_iterator cit; // 只能读不能写

    vector<int> v;
    const vector<int> cv;
    auto it1 = v.begin();  // 是vector<int>::iterator类型
    auto it2 = cv.begin(); // 是vector<int>::const_iterator类型

    auto it3 = v.cbegin(); // C++11引入的新函数，固定是vector<int>::const_iterator类型

    cout << (v.end() == v.begin()) << endl; // 1
    vector<int> v1(5);
    cout << (v1.end() == v1.begin()) << endl;        // 0
    cout << (v1.end() == (v1.begin() + 30)) << endl; // 0
    cout << (v1.end() == (v1.begin() + 5)) << endl;  // 1

    cout << (v1.begin() < v1.end()) << endl; // 1，可以用<,>符号，比较迭代器所指向的位置谁前谁后

    cout << (v1.end() - v1.begin()) << endl; // 5，表示两个迭代器的类型

    vector<int>::difference_type d = v1.begin() - v1.end(); // 有符号整型数，可以是负数
    cout << d << endl;                                      // -5

    // 注意没有定义两个迭代器相加的操作
    // auto x = v1.begin() + v1.end();  // error : 未定义该操作

    auto begin = vec.crbegin(), end = vec.crend(); // c表示const迭代，r表示反向迭代
    while (begin != end)
    { // 将打印2 1
        cout << (*begin) << endl;
        begin++;
    }
}


// 插入迭代器
void test2(){
    vector<int> veci = {1, 2, 3, 4, 5};
    auto back_iter = back_inserter(veci);
    // cout << (*back_iter) << endl;  // error : 输出解引用的值无意义
    *back_iter = 6;  // 赋值时会调用push_back插入元素
    print(veci);  // 1 2 3 4 5 6
    ++ back_iter;
    *back_iter = 7;  // 无任何作用的操作
    print(veci);  // 1 2 3 4 5 6 7


    deque<int> veci1 = {1, 2, 3, 4, 5};
    auto front_iter = front_inserter(veci1);
    // cout << (*front_iter) << endl;  // error : 输出解引用的值无意义
    *front_iter = 0;  // 赋值时会调用push_front插入元素，对应的集合必须支持push_front操作
    print(veci1);  // 0 1 2 3 4 5
    front_iter++;  // 无任何作用的操作
    *front_iter = -1;
    print(veci1);  // -1 0 1 2 3 4 5

    vector<int> veci2 = {1, 2, 3, 4, 5};
    auto beg = veci2.begin();
    cout << (beg == veci2.begin()) << endl;  // 1
    auto insert_iter = inserter(veci2, beg);
    // cout << *insert_iter << endl;  // error : 输出解引用的值无意义
    *insert_iter = 0;  // 赋值时会调用insert(it, val)插入元素，然后it++，重新指向它原来的元素
    print(veci2);  // 0 1 2 3 4 5
    *insert_iter = -1;
    print(veci2);  // 0 -1 1 2 3 4 5
    insert_iter ++;
    *insert_iter = -2;
    print(veci2);  // 0 -1 -2 1 2 3 4 5
}

int main()
{
    // test1();
    test2();


    system("pause");
    return 0;
}