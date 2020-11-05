#include <string>
using std::string;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <vector>
using std::vector;

int main(){

    vector<int> vec{1, 2};
    auto b = vec.begin();  // 指向第一个元素的迭代器
    auto e = vec.end();  // 指向尾元素下一个位置的迭代器，尾后迭代器
    cout << *(b) << endl;  // 通过解引用迭代器获取它所指示的元素，值是1
    cout << *(b++) << endl;  // b++，令b指向容器中的下一个元素
    // cout << *e << endl;  // 非法，解引用尾后迭代器是未被定义的行为
    
    string s("some string");
    for(auto it = s.begin(); it != s.end(); it++){
        *it = toupper(*it);
    }
    cout << s << endl;

    vector<int>::iterator it;  // 能读写vector<int>的元素
    vector<int>::const_iterator cit;  // 只能读不能写

    vector<int> v;
    const vector<int> cv;
    auto it1 = v.begin();  // 是vector<int>::iterator类型
    auto it2 = cv.begin();  // 是vector<int>::const_iterator类型

    auto it3 = v.cbegin();  // C++11引入的新函数，固定是vector<int>::const_iterator类型

    cout << (v.end() == v.begin()) << endl;  // 1
    vector<int> v1(5);
    cout << (v1.end() == v1.begin()) << endl;  // 0
    cout << (v1.end() == (v1.begin() + 30)) << endl;  // 0
    cout << (v1.end() == (v1.begin() + 5)) << endl;   // 1

    cout << (v1.begin() < v1.end()) << endl;  // 1，可以用<,>符号，比较迭代器所指向的位置谁前谁后

    cout << (v1.end() - v1.begin()) << endl;  // 5，表示两个迭代器的类型

    vector<int>::difference_type d = v1.begin() - v1.end(); // 有符号整型数，可以是负数
    cout << d << endl; // -5

    // 注意没有定义两个迭代器相加的操作
    // auto x = v1.begin() + v1.end();  // error : 未定义该操作

    system("pause");
    return 0;
}