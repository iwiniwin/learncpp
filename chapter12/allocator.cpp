#include <string>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

void test1(){
    allocator<string> alloc;  // 可以分配string的allocator对象
    auto const p = alloc.allocate(3);  // 分配3个未初始化的string，原始的，未构造的内存

    auto q = p;

    // cout << *p << endl;  // error : 还未构造对象的情况下就使用原始内存

    alloc.construct(q ++, "args");   // 用来在p指向的内存中构造一个对象，在q指向的位置上
    alloc.construct(q ++, "args2");  // 在下一个位置上构造对象

    cout << *p << endl;  // args
    cout << *(p + 1) << endl;  // args2

    alloc.destroy(q);  // error : 只能对真正构造了的元素进行destroy操作 

    while(q != p){
        // 在使用完对象后，必须对每个构造的元素调用destroy来销毁他们
        alloc.destroy(--q);  // // 对q指向的对象执行析构函数
    }

    alloc.deallocate(p, 3);  // 释放从指针p中地址开始的内存 ， 注意这里传入的大小，必须和分配时提供的大小相同
}

// 伴随算法
void test2(){
    vector<int> vec = {1, 2, 3};

    allocator<int> alloc;
    // 分配内存大小是vec的2倍
    auto p = alloc.allocate(vec.size() * 2);
    // 前一半拷贝vec的元素到内存
    auto q = uninitialized_copy(vec.begin(), vec.end(), p);  // uninitialized_copy返回递增后的目的位置迭代器
    // 后一半通过指定值构建对象，填充到内存中
    uninitialized_fill_n(q, vec.size(), 42);

    for(int i = 0; i < vec.size() * 2; i ++){
        cout << *(p + i) << " ";  // 1 2 3 42 42 42
    }
    cout << endl;

    allocator<string> alloc2;
    auto p2 = alloc2.allocate(3);
    // uninitialized_fill_n(p2, 3, 10, '3');  // error : 接收的不是类型的构造函数参数
    uninitialized_fill_n(p2, 3, "aa");
}

int main(){

    test1();
    test2();

    system("pause");
    return 0;
}