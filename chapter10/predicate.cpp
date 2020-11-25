#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void print(vector<string> &v){
    for(auto s : v){
        cout << s << " ";
    }
    cout << endl;
}

bool isShorter(const string &s1, const string &s2){
    return s1.size() < s2.size();
}

void test1(){
    vector<string> vecs = {"ab", "b", "cd"};
    sort(vecs.begin(), vecs.end());
    print(vecs);  // ab b cd

    // sort重载方法，第三个函数接收一个谓词
    // 谓词是一个可调用的表达式，其返回结果是一个能用作条件的值
    sort(vecs.begin(), vecs.end(), isShorter);
    print(vecs);  // b ab cd

    stable_sort(vecs.begin(), vecs.end(), isShorter);  // 稳定排序，维持相等元素的原有顺序
    print(vecs);  // b ab cd
}

int main(){

    test1();

    system("pause");
    return 0;
}