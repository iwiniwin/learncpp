#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <deque>
#include <algorithm>
#include <numeric>
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
    ++ back_iter;  // 无任何作用的操作
    *back_iter = 7;  
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
    insert_iter = -3;  // 可以忽略解引用操作
    print(veci2);  // 0 -1 -2 -3 1 2 3 4 5
}

class Test {
public:
    int a = 0;
};

// 流迭代器
void test3(){
    // ostream_iterator<int> out_iter;  // error : 不允许空的或表示尾后的ostream_iterator，必须绑定到流
    ostream_iterator<int> out_iter(cout);
    ostream_iterator<int> out_iter2(cout, " ");  // 在输出每个元素后都会添加此字符串

    // string s = "ss";
    // ostream_iterator<int> out_iter3(cout, s);  // error : s必须是c风格字符串

    vector<int> vec2 = {1, 2, 3};
    for(auto e : vec2){
        *out_iter++ = e;  // 输出e，123
        // *out_iter = e;  // 等价于上面的写法
        // out_iter = e;  // 等价于上面的写法，解引用和递增运算，可以忽略，实际上它们什么也不做，但仍建议写成第一种样式，更清晰
    }
    cout << endl;

    copy(vec2.begin(), vec2.end(), out_iter);  // 利用copy算法，输出vec中元素
    cout << endl;

    // todo，利用流迭代器处理类类型
    // ostream_iterator<Test> out_iter4(cout);
    // Test t();
    // out_iter4 = t;


    istream_iterator<int> int_iter(cin);  // 将迭代器绑定到cin，从cin读取int，istream_iterator使用>>来读取流
    istream_iterator<int> int_eof;   // 默认初始化迭代器，相当于尾后迭代器
    while(int_iter != int_eof){
        cout << *int_iter++ << endl;  // 获得从流读取的值，且迭代器递增
    }

    istream_iterator<int> in_iter(cin), eof;
    vector<int> vec(in_iter, eof);  // 利用流迭代器构造vector

    // 使用算法操作流迭代器
    istream_iterator<int> in(cin), ieof;
    cout << accumulate(in, ieof, 0) << endl;
}

// 反向迭代器
void test4(){
    vector<int> vec = {1, 2, 3, 4};
    for(auto r_iter = vec.rbegin(); r_iter != vec.rend(); ++r_iter){  // 对于反向迭代器而言，递增和递减的含义颠倒了过来
        cout << *r_iter << " ";  // 4 3 2 1
    }
    cout << endl;

    sort(vec.begin(), vec.end());
    print(vec);  // 1 2 3 4

    sort(vec.rbegin(), vec.rend());
    print(vec);  // 4 3 2 1


    string line = "abc,def,ghi,jkl";
    auto comma = find(line.begin(), line.end(), ',');
    cout << string(line.begin(), comma) << endl;  // abc，打印逗号前的第一个单词

    auto comma2 = find(line.rbegin(), line.rend(), ',');
    cout << string(line.rbegin(), comma2) << endl;  // lkj，打印逗号后的最后一个单词，注意，输出的是逆序，而不是jkl
    // 注意comma2也同样是一个反向迭代器
    auto comma3 = comma2.base(); // 将返回一个正常的迭代器
    cout << string(comma3, line.end()) << endl;  // jkl

    // 普通迭代器和反向迭代器的关系反映了左闭合区间的特性
    cout << *comma2 << " " << *comma3 << endl;  // , j  注意，comma2和comma3指向的是不同的元素，这种不同保证了元素范围无论是正向处理还是反向处理都是相同的
}

int main()
{
    // test1();
    // test2();
    // test3();
    test4();


    system("pause");
    return 0;
}