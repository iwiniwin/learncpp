#include <string>
#include <iostream>
#include <memory>
using namespace std;

void test1(){

    weak_ptr<int> wp0;  // 空的weak_ptr

    auto p = make_shared<int>(42);
    weak_ptr<int> wp(p);  // wp弱共享p

    wp = wp0;  // wp与wp0共享对象，可以使用weak_ptr向weak_ptr赋值
    wp = p;  // wp与p共享对象，可以使用shared_ptr向weak_ptr赋值

    // cout << *wp << endl;  // error : 由于对象可能不存在，所以不能使用weak_ptr直接访问对象
    
    // cout << (wp == nullptr) << endl;  // error : 不能比较

    cout << wp.use_count() << endl;  // 1，与wp共享对象的shared_ptr的数量

    cout << wp.expired() << endl;  // 0， wp的use_count是否为0，为0返回true，否则返回false
    
    if(shared_ptr<int> np = wp.lock()){  // lock检查weak_ptr指向的对象是否仍存在，如果存在，返回一个指向共享对象的shared_ptr，否则返回空的shared_ptr

    }

    wp.reset();  // 将wp置为空
    cout << wp.use_count() << endl;  // 0
    cout << p.use_count() << endl;  // 1
}

int main(){

    test1();

    system("pause");
    return 0;
}