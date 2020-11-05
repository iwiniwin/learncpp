#include <string>
using std::string;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <vector>
using std::vector;

int main(){

    vector<int> ivec;  // ivec保存int类型的对象，默认初始化，ivec空vector，不包含任何元素
    vector<vector<string>> file;

    ivec.push_back(33);

    vector<int> ivec2(ivec);  // 把ivec的元素拷贝给ivec2
    vector<int> ivec3 = ivec;  // 把ivec的元素拷贝给ivec3，注意是拷贝

    ivec3[0] = 1;
    cout << ivec3[0] << " " << ivec[0] << endl;

    vector<int> ivec4(10, -1);  // 10个int类型的元素，每个都被初始化为-1

    vector<string> articles = {"a" , "an", "the"};  // 列表初始化
    vector<string> articles2{"a" , "an", "the"};   // 列表初始化

    // vector<string> articles3("sss");  // error
    // vector<string> articles4("sss", "ttt");  // error
    vector<string> articles5(articles);
    articles5[0] = "bbb";
    cout << articles5[0] << " " << articles[0] << endl;

    // 值初始化
    vector<int> ivec5(10);  // 10个元素，每个都初始化为0，直接初始化
    vector<string> svec5(10);  // 10个元素，每个都初始化为空string对象，直接初始化

    // 列表初始化
    vector<int> ivec6{10};  // 1一个元素，值是10
    vector<int> ivec7{10, -1};  // 2一个元素，值是10和-1

    vector<string> v5 {"hi"}; // 列表初始化，一个元素hi
    vector<string> v7{10}; // 10个元素，每个都初始化为空string对象
    vector<string> v8{10, "hi"}; // 10个元素，每个都初始化为hi
    cout << v7[8] << " " << v8[8] << endl;


    vector<int> v9{1, 2, 3};
    for(auto i : v9){
        // v9.push_back(7);  // 未定义，禁止这样使用
        cout << i << endl;
    }

    // vector的下标类型
    vector<int>::size_type a;
    // vector::size_type b;  // error 

    system("pause");
    return 0;
}