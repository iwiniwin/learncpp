#include <string>
#include <iostream>
#include <memory>
using namespace std;

void test1(){
    unique_ptr<double> pl;  // 可以指向double的unique_ptr，空指针
    cout << (pl == nullptr) << endl;  // 1

    unique_ptr<int> p2(new int(42));

    // unique_ptr<int> p3(p2);  // error : unique_ptr不支持拷贝
    unique_ptr<int> p4;
    // p4 = p2;  // error : unique_ptr不支持赋值

    // 通过reset和release可以将转移指针的所有权
    unique_ptr<int> p5(p2.release());  // p2.release()将放弃对指针的控制权，返回指针，并将p2置为空
    cout << (p2 == nullptr) << endl;  // 1
    p2.reset(p5.release());  // 如果p2不为空，reset会释放p2之前所指向的对象。并重新绑定到p5指定的对象上
    cout << *p2 << endl;  // 42

    auto p = p2.release();  // 注意release并不会释放内存
    delete p;  // release后返回的指针，如果不会再继续使用，记得手动release
}

unique_ptr<int> clone(int p){
    // 在此情况下编译器执行一种特殊的拷贝
    return unique_ptr<int>(new int(p));  // 虽然unique_ptr不允许拷贝和赋值，但是可以拷贝和赋值一个即将要销毁的unique_ptr，比如这里作为返回值返回
}

unique_ptr<int> clone2(int p){
    unique_ptr<int> ret = unique_ptr<int>(new int(p));
    return ret;  // 虽然unique_ptr不允许拷贝和赋值，但是可以拷贝和赋值一个即将要销毁的unique_ptr，比如这里作为返回值返回
}

void test2(){
    unique_ptr<int> p1 = clone(3);
    unique_ptr<int> p2 = clone2(4);
}

void my_delete(int *p){
    cout << "delete p" << endl;
    delete p;
}

void test3_a(){
    unique_ptr<int, decltype(my_delete)*> p(new int(42), my_delete);
}

// 使用自己的删除器
void test3(){
    test3_a();
}

int main(){

    test1();
    test2();
    test3();

    system("pause");
    return 0;
}