#include <string>
#include <iostream>
using namespace std;

void *operator new(size_t size) {
    cout << "my new" << endl;
    if(void *mem = malloc(size))
        return mem;
    else
        throw bad_alloc();
}

// todo delete函数根本没有被调用
void operator delete(void *mem) noexcept {
    cout << "my delete" << endl;
    free(mem);
}

void test1(){
    string *sp = new string("value");  // 分配并初始化一个string对象
    string *arr = new string[10];  // 分配10个默认初始化的string对象

    sp->~string();  // 可以显式调用析构函数，调用析构函数会销毁对象，但不会释放内存

    delete sp;
    delete [] arr;

    int *p = new int();
    delete p;
}

int main(){

    test1();

    system("pause");
    return 0;
}