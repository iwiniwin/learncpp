#include <string>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <utility>
using namespace std;

// map
void test1(){
    map<string, size_t> world_count;
    world_count["hello"] = 2;
    cout << world_count["hello"] << endl;  // 2

    // 下标操作，如果关键字不在map中，会为它创建一个元素并插入到map中，关联值将进行值初始化
    world_count["world"] ++;

    world_count["world1"] ++;

    world_count["world3"] ++;

    world_count["world2"] ++;

    cout << world_count["bbb"] << endl;  // 0，如果不存在该元素，会自动创建

    // cout << world_count.at("ccc") << endl;  // exception : 访问一个关键字为ccc的元素，如果不在容器中，则抛出out_of_range异常

    // 遍历一个map,multimap, set或multiset时，按关键字升序遍历
    for(auto &w : world_count){
        cout << w.first << " " << w.second << " ";  // bbb 0 hello 2 world 1 world1 1 world2 1 world3 1
    }
    cout << endl;

    cout << world_count["jj"] << endl;  // 0

    map<string, string> authors = {  // 列表初始化
        {"Joyce", "James"},
        {"Austen", "Jane"},
        {"Dickens", "Charles"},
        {"Dickens", "Test"},
    };
    cout << authors["Dickens"] << endl;  // Charles

    // 插入元素，注意插入的元素类型是pair
    authors.insert({"aa", "bb"});
    authors.insert(make_pair("bvv", "sss"));
    auto ret2 = authors.insert(pair<string, string>("a", "b"));
    // 当关键字已在容器中时，insert什么也不做，且返回值的bool部分为false
    auto ret = authors.insert(map<string, string>::value_type("aa", "hh"));

    // 删除元素
    int ei = authors.erase("Austen");  // erase返回值非0即1，返回0表示要删除的元素不在容器中
    cout << ei << endl;  // 1

    for(auto &w : authors){
        cout << w.first << " = " << w.second << ", ";  // Dickens = Charles, Joyce = James, a = b, aa = bb, bvv = sss,
    }
    cout << endl;
    cout << ret.second << endl;  // 0，false
    // insert返回值的first指向的是具有给定关键字的元素pair<>
    cout << ret.first->first << endl;  // aa
    cout << ret.first->second << endl;  // bb

    cout << ret2.second << endl;  // 1
    cout << ret2.first->first << endl;  // a
    cout << ret2.first->second << endl;  // b
}

// multimap
void test2(){
    multimap<string, string> au;
    // 由于multimap语序重复关键字，所以insert总是成功，返回的是指向新元素的迭代器
    au.insert({"aa", "bb"});
    auto ret3 = au.insert({"aa", "cc"});
    cout << ret3->first << " " << ret3->second << endl;  // aa cc

    for(auto &w : au){
        cout << w.first << " = " << w.second << ", ";  // aa = bb, aa = cc,
    }
    cout << endl;

    cout << au.count("aa") << endl;  // 2

    auto iter = au.find("aa");  // 返回一个迭代器，指向key == aa的元素，若key不存在则返回尾后迭代器
    cout << iter->first << " " << iter->second << endl;  // aa bb

    // 希望找到关键字aa关联的所有元素
    // 方法1，利用count和find
    auto c = au.count("aa");
    while(c){
        cout << iter->first << " " << iter->second << ", ";  // aa bb, aa cc,
        ++ iter;
        -- c;
    }
    cout << endl;

    // 方法2，利用lower_bound和upper_bound
    // 如果lower_bound和upper_bound返回相同的迭代器，则给定关键字不在容器中
    for(auto beg = au.lower_bound("aa"), end = au.upper_bound("aa"); beg != end; ++ beg){
        cout << beg->first << " " << beg->second << ", ";  // aa bb, aa cc,
    }
    cout << endl;

    // 方法3，利用equal_range，若关键字存在，则第一个迭代器指向第一个与关键字匹配的元素，第二个迭代器指向最后一个匹配元素之后的位置
    for(auto pos = au.equal_range("aa"); pos.first != pos.second; ++ pos.first){
        cout << pos.first->first << " " << pos.first->second << ",, ";  // aa bb,, aa cc,,
    }
    cout << endl;

    cout << au.erase("aa") << endl;  // 2，表示删除了2个元素，对于可重复关键字容器来说
    cout << au.size() << endl;  // 0
}

// set
void test3(){
    set<string> exclude = {"vv", "aa"};
    cout << (exclude.find("aa") == exclude.end()) << endl;  // 0，find返回一个迭代器，如果给定关键字在set中，则迭代器指向该关键字
    cout << (exclude.find("ww") == exclude.end()) << endl;  // 1

    cout << exclude.count("aa") << endl;  // 1，统计关键字值有多少个元素

    // exclude["ddd"] = 1;
    exclude.insert("vvv");

    // 插入元素
    exclude.insert({"bb", "cc"});
}

class Test {
public:
    int a = 1;
    int b = 2;
};

bool compare(const Test &t1, const Test &t2){
    return t1.a < t2.a;
}

// multiset
void test4(){
    vector<int> ivec = {1, 2, 3, 1, 2, 3};
    set<int> iset(ivec.cbegin(), ivec.cend());
    multiset<int> miset(ivec.cbegin(), ivec.cend());

    cout << iset.size() << endl;   // 3
    cout << miset.size() << endl;  // 6

    // multiset<Test> tset = {Test(), Test()};  // error : 对于有序关联容器，关键字类型必须定义元素比较的方法
    // multiset<Test, decltype(compare)*> tset2 = {Test(), Test()};
    // multiset<Test, bool (*)(const Test &, const Test &)> tset2 = {Test(), Test()};
}

// pair
void test5(){
    pair<string, string> anon;
    pair<string, size_t> world_count;  
    cout << world_count.second << endl;  // 0，pair的默认构造函数对数据成员进行值初始化

    pair<string, size_t> world_count2{"dd", 6};  

    auto p = make_pair("ddd", 3);  // 返回一个用ddd和3初始化的pair，pair的类型从参数推断出来
    cout << p.first << endl;  // ddd
}

void test6(){
    set<string>::value_type v1;  // v1是一个string
    set<string>::value_type v2;  // v2是一个string
    map<string, int>::key_type v3; // v3是一个string
    map<string, int>::value_type v4;  // v4是pair<const string, int>，不是int
    v4.second = 3;
    // v4.first = "ddd";  // error : map的关键字不能改变，是只读的

    map<string, int>::mapped_type v5;  // v5是一个int
    v5 = 6;

    map<string, size_t> world_count = {{"aa", 1}, {"cc", 2}, {"bb", 3}};
    auto map_iter = world_count.begin();
    cout << map_iter->first << endl;  // aa
    cout << map_iter->second << endl;  //  1
    map_iter->second ++;
    // map_iter->first = "vvv";  // error ： 关键字是const的
    cout << map_iter->second << endl;  //  2

    set<int> iset = {1, 2, 3};
    set<int>::iterator set_iter = iset.begin();
    cout << *set_iter << endl;  // 1
    // *set_iter = 4;  // error : set中的关键字是只读的

    // 遍历map
    while(map_iter != world_count.end()){
        cout << map_iter->first << " = " << map_iter->second << ", ";  // aa = 2, bb = 3, cc = 2,  当使用一个迭代器遍历一个map，multimap, set, multiset时，迭代器按关键字升序遍历元素
        ++ map_iter;
    }
    cout << endl;
}

int main(){

    test1();
    test2();
    // test3();
    // test4();
    // test5();
    // test6();

    system("pause");
    return 0;
}