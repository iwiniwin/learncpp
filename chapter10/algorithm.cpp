#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

// 只读算法
void test1(){
    vector<int> vec = {1, 2, 3, 4};
    auto iter = find(vec.cbegin(), vec.cend(), 3);  // 在vec中查找3，如果3存在，返回3的迭代器，否则返回第二个参数
    cout << (iter == vec.cbegin()) << endl;  // 0 表示找到3
    cout << *iter << endl;  // 3

    int arr[] = {1, 2, 3, 4};
    auto iter2 = find(cbegin(arr), cend(arr), 3);  // 迭代器令算法不依赖于容器

    cout << accumulate(cbegin(arr), cend(arr), 0) << endl;  // 10, 计算范围内元素的和，其中0表示和的初值

    vector<string> vecs = {"ab", "cd"};
    cout << accumulate(vecs.cbegin(), vecs.cend(), string("zz")) << endl;;  // zzabcd
    // accumulate(vecs.cbegin(), vecs.cend(), "zz");  // error : const char*上没有定义+运算符，accumulate的第三个参数同时决定了函数中使用哪个加法运算符，以及返回值的类型

    vector<double> vecd = {3.14, 2.5};
    cout << accumulate(vecd.cbegin(), vecd.cend(), 0) << endl;  // 5, accumulate的第三个参数同时决定了函数中使用哪个加法运算符，以及返回值的类型
    cout << accumulate(vecd.cbegin(), vecd.cend(), 0.0) << endl;;  // 5.64

    cout << equal(vec.cbegin(), vec.cend(), begin(arr)) << endl;  // 1, 比较两个序列是否相等，不要求容器类型或元素类型一样

    for_each(vec.begin(), vec.end(), [](const int &i){  // for_each算法，接收一个可调用对象，并对输入序列的每个元素调用此对象
        cout << i << " ";  // 1 2 3 4
    });
    cout << endl;
}

// 写算法
void test2(){
    vector<int> vec = {1, 2, 3, 4};
    fill(vec.begin(), vec.end(), 0);  // 将0赋给序列范围中的每个元素
    fill_n(vec.begin(), 2, 1);  // 将前2个元素赋值为1

    vector<int> veci;
    // fill_n(veci.begin(), 2, 1);  // error : 修改veci中不存在的两个元素

    auto iter = back_inserter(veci);  // 插入迭代器，通过它赋值会将元素添加到vec中    
    *iter = 42;  // 当通过插入迭代器赋值时，赋值运算符会调用push_back将一个具有给定值的元素添加到容器中
    cout << veci[0] << endl;  // 42

    fill_n(back_inserter(veci), 3, 1);  // 添加3个元素1到veci
    cout << veci.size() << endl;  // 4


    int a1[] = {1, 2, 3, 4};
    int a2[sizeof(a1) / sizeof(*a1)];
    auto ret = copy(begin(a1), end(a1), begin(a2));  // 把a1的内容拷贝到a2，返回的ret是其目的位置迭代器之后的值

    replace(begin(a1), end(a2), 0, 42);  // 将所有值为0的元素都改为42

    vector<int> vec2;
    replace_copy(cbegin(a1), cend(a1), back_inserter(vec2), 4, 2);  // 将a1中的元素拷贝到vec2中，同时值为4的元素都改为2
    for(auto i : vec2){
        cout << i << " ";  // 1 2 3 2
    }
    cout << endl;
}

// 重排容器元素的算法
void test3(){
    vector<string> vecs = {"abc", "ab", "ef", "ef", "ab", "bc"};
    sort(vecs.begin(), vecs.end()); // 按字典序排序
    for(auto s : vecs){
        cout << s << " ";  //ab ab abc bc ef ef
    }
    cout << endl;

    auto end_unique = unique(vecs.begin(), vecs.end());  // unique重排输入范围，使得每个单词只出现一次。将相邻的元素“消除”，并返回一个指向不重复范围末尾的迭代器
    for(auto s : vecs){
        cout << s << "-";  //ab-abc-bc-ef--ef- ， end_unique之后的值是什么并不知道
    }
    cout << endl;
    cout << vecs.size() << endl;  // 6， 调用unique后，vecs的大小并不会改变，但是元素顺序改变了，begin-end_unique的范围内只有非重复元素

    auto begin = vecs.begin();
    while(begin != end_unique){
        cout << *begin++ << "-";  // ab-abc-bc-ef-
    }
    cout << endl;


    vecs.erase(end_unique, vecs.end());  // 使用erase真正的删除重复元素
    for(auto s : vecs){
        cout << s << "-";  //ab-abc-bc-ef-
    }
    cout << endl;
    cout << vecs.size() << endl;  // 4
}

int main(){

    test1();
    // test2();
    // test3();
    

    system("pause");
    return 0;
}