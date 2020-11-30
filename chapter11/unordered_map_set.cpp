#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

void test1(){
    unordered_map<string, size_t> world_count;
    world_count["hello"] = 2;

    world_count["world"] ++;

    world_count["world1"] ++;

    world_count["world3"] ++;

    world_count["world2"] ++;

    for(const auto &w : world_count){
        // 打印将是无序的
        cout << w.first << " " << w.second << " ";  // world2 1 hello 2 world 1 world1 1 world3 1
    }
    cout << endl;
}

void test2(){
    unordered_map<string, size_t> world_count = {
        {"aa", 3},
        {"cc", 2},
        {"dd", 4},
        {"bb", 1},
    };
    cout << world_count.bucket_count() << endl;  // 5，正在使用的桶的数量
    cout << world_count.max_bucket_count() << endl;  // 119304647，容器能容纳的最多的桶的数量
    

    for(int i = 0; i < world_count.bucket_count(); i ++){
        cout << world_count.bucket_size(i) << " ";  // 0 2 1 0 1，第n个通中有多少个元素
    }
    cout << endl;

    cout << world_count.load_factor() << endl;  // 0.8，每个桶的平均元素数量，float值
    cout << world_count.max_load_factor() << endl;  // 1，试图维护的平均桶大小，load_factor <= max_load_factor
    world_count.rehash(10);  // 重组存储，使得bucket_count >= n 且 bucket_count > size / max_load_factor
    cout << world_count.bucket_count() << endl;  // 11，正在使用的桶的数量

    world_count.reserve(12);  // 重组存储，使得容器可以保存n个元素而不必rehash
}

class Test {
public:
    int a;
};

size_t hasher(const Test &t){
    return 0;
}

bool eq(const Test &t1, const Test &t2){
    // return t1 == t2;  // error : 未定义==操作
    return t1.a < t2.a;
}

void test3(){
    // unordered_multiset<Test> book;  // error : 非内置类型或标准库类型，没有定义hash模板，需要自己提供，且Test类没有定义==操作
    unordered_multiset<Test, decltype(hasher)*, decltype(eq)*> book;
}

int main(){

    test1();
    test2();
    test3();

    system("pause");
    return 0;
}