#include <string>
#include <iostream>
#include <array>
#include <list>
#include <vector>
#include <deque>
#include <forward_list>
using namespace std;

void test1(){
    array<int, 32> arr;  // 保存32个int的数组
    // array<int> arr2;  // error : 使用array类型，必须同时指定元素类型与大小
    array<int, 32> arr3 = {1, 2};  // 列表初始化
    arr = arr3;  // 与内置数组类型不同的是，允许对标准库array类型进行拷贝或赋值

    cout << arr[1] << endl;  // 2
}

void test2(){
    list<string> names = {"11", "22", "33"};
    vector<const char*> oldstyle = {"11"};
    // names = oldstyle;  //  error : 容器类型不匹配
    names.assign(oldstyle.cbegin(), oldstyle.cend());  // 将names中的元素替换为迭代器指定范围中元素的拷贝
    cout << names.size() << endl;  // 1
    names.assign(10, "vvv");
    cout << names.size() << endl;  // 10
}

void test3(){
    vector<string> vec1(10);
    vector<string> vec2(5);
    swap(vec1, vec2);  // 交换两个相同类型容器的内容。交换两个容器内容的操作保证会很快，因为元素本身并未交换，只是交换了两个容器内部的数据结构
    cout << vec1.size() << " " << vec2.size() << endl;  // 5 10
}

// 添加元素
void test4(){
    string s = "abcd";
    s.push_back('e');  // string 是一个字符容器，也可以用push_back在string末尾添加字符
    cout << s << endl;  // abcde
    // s.push_front('a');  // string不支持push_front
    s.insert(s.begin(), 'a');  // string支持insert方法。将元素插入到迭代器所指定的位置之前
    cout << s << endl;  // aabcde
    s.insert(s.end(), 3, 'x'); // 将3个元素插入到容器末尾
    cout << s << endl;  // aabcdexxx

    string s1 = "xyz";
    auto iter = s.insert(s.end(), s1.end() - 2, s1.end());  // 将s1的后两个元素加到容器的末尾
    cout << s << endl;  // aabcdexxxyz

    s.insert(iter, 'u');  // iter是insert的返回值，insert返回的是第一个新加入元素的迭代器，如果范围为空，不插入任何元素，则返回第一个参数
    cout << s << endl;  // aabcdexxxuyz
    

    vector<int> veci = {1, 2, 3};
    // veci.push_front(1);  // vector不支持push_front
    veci.push_back(4);

    deque<int> deq;
    deq.push_front(1);  // 将元素插入到容器头部
}

class Test {
public:
    Test(int a, int b){}
    int a;
    int b;
};

void test5(){
    vector<Test> t;
    t.emplace_back(3, 4);  // emplace_back会在容器管理的内存空间中直接创建对象，其参数与元素类型的构造函数相匹配
}

// 访问元素
void test6(){
    vector<int> v = {1, 2, 3};
    cout << v.front() << endl;  // 1
    cout << v.back() << endl;  // 3
    forward_list<int> fl = {4, 5, 6};
    cout << fl.front() << endl;  // 4
    // cout << f1.back() << endl;  // error : forward_list没有back函数
    cout << v.at(2) << endl;  // 3
    // cout << fl.at(1) << endl;  // error : forward_list没有at函数

    int &i = v.front();  // 返回的是引用
    i = 0;
    cout << v.front() << endl;  // 0
    int j = v.front();
    j = 1;
    cout << v.front() << endl;  // 0
}

// 删除元素
void test7(){
    vector<int> v = {1, 2, 3};
    // v.pop_front();  // errror : vector不支持pop_front
    v.pop_back();  // 删除尾元素
    v.erase(v.begin());  // 删除指定位置的元素
    cout << v.size() << endl;  // 1
    cout << v[0] << endl;  // 2

    v.erase(v.begin(), v.end() - 1);  // 等于没有删除
    cout << v.size() << endl;  // 1

    v.erase(v.begin(), v.end());  // 清空元素
    cout << v.size() << endl;  // 0
    v.clear();  // 清空元素
}

// forward_list
void test8(){
    forward_list<int> fl = {1, 2, 3, 4, 5};
    auto prev = fl.before_begin();  // 返回首前迭代器
    fl.erase_after(prev); // 删除首元素
    fl.insert_after(++ prev, 5);
    auto beg = fl.begin(), end = fl.end();
    while(beg != end){
        cout << (*beg ++) << " ";  // 2 5 3 4 5
    }
    cout << endl;
}

void test9(){
    list<int> l(3, 42);  // 3个int，每个值都是42
    l.resize(5);  // 将2个值为0的元素添加到末尾
    l.resize(8, -1);  // 将3个值为-1的元素添加到末尾
    l.resize(7);  // 从末尾删除一个元素
    for(auto i : l){
        cout << i << " ";  // 42 42 42 0 0 -1 -1
    }
    cout << endl;
}

void testx(){
    vector<int> vi = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto iter = vi.begin();

    // 删除偶数元素，复制奇数元素
    while(iter != vi.end()){
        if(*iter % 2 == 0){
            iter = vi.erase(iter);
        }else{
            iter = vi.insert(iter, *iter);
            iter += 2;
        }
    }

    for(auto i : vi){
        cout << i << " ";  // 1 1 3 3 5 5 7 7 9 9
    }
    cout << endl;
}

void testx1(){
    vector<int> vi = {0, 1, 2};
    cout << vi.capacity() << endl;  // 3，capacity表示不重新分配内存空间的话，容器可以保存多少元素
    vi.push_back(3);
    cout << vi.capacity() << endl;  // 6
    vi.reserve(100);  // 分配至少能容纳100个元素的内存空间，reserve永远也不会减少容器占用的内存空间
    cout << vi.capacity() << endl;  // 100
    vi.reserve(9);  // reserve的值，小于当前容量，什么也不做
    cout << vi.capacity() << endl;  // 100
    vi.shrink_to_fit();  // 请求将capacity减少为与size相同的大小，注意，并不保证一定退回内存空间
    cout << vi.capacity() << endl;  // 4
}

int main(){

    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    testx();
    testx1();

    system("pause");
    return 0;
}