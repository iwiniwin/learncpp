#include <string>
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

template <typename T> 
class Blob {
public:
    typedef T value_type;
    typedef typename vector<T>::size_type size_type;
    // 构造函数
    Blob();
    Blob(initializer_list<T> il);
    // Blob中的元素数目
    size_type size() const {return data->size();}
    bool empaty() const {return data->empty();}
    // 添加和删除元素
    void push_back(const T &t) {data->push_back(t);}
    // 移动版本
    void push_back(T &&t) {data->push_back(std::move(t));}
    void pop_back();
    // 元素访问
    T &back();
    T &operator[](size_type i);

    Blob &test(Blob &);  // 正确，在类模板自己的作用域内，可以直接使用模板名，而不用带实参，相当于Blob<T> &
private:
    shared_ptr<vector<T>> data;
    void check(size_type i, const string &msg) const;
};

// error : 定义在类模板之外的成员函数必须以关键字template开始，后接类模板参数列表
// void Blob<T>::check(size_type i, const string &msg) const {
//     if(i >= data->size())
//         throw out_of_range(msg);
// }

// error : 定义在类模板之外的成员函数必须以关键字template开始，后接类模板参数列表
// void Blob::check(size_type i, const string &msg) const {
//     if(i >= data->size())
//         throw out_of_range(msg);
// }

template <typename T> void Blob<T>::check(size_type i, const string &msg) const {
    if(i >= data->size())
        throw out_of_range(msg);
}

template <typename T> T &Blob<T>::back(){
    check(0, "back on empty Blob");
    return data->back();
}

template <typename T> void Blob<T>::pop_back() {
    check(0, "pop back on empty Blob");
    data->pop_back();
}

template <typename T>
T &Blob<T>::operator[](size_type i){
    check(i, "subscript out of range");
    return (*data)[i];
}

// 构造函数定义
template <typename T>
Blob<T>::Blob() : data(make_shared<vector<T>>()) {

}

template <typename T>
Blob<T>::Blob(initializer_list<T> il) : data(make_shared<vector<T>>(il)) {

}

template <typename T>
Blob<T> &Blob<T>::test(Blob &) {  // 正确，在进入类作用域后可以直接省略模板实参
    Blob b;
    return b;
}

void test1(){
    // 下面的定义实例化出两个不同的Blob类型，对于我们指定的每一种元素类型，编译器都生成一个不同的类
    Blob<int> ia;  // 必须显式提供元素类型，因为编译器不能为类模板推断模板参数类型
    Blob<string> ia2;

    Blob<string> ia3 = {"bb", "aa"};
}

int main(){

    test1();

    system("pause");
    return 0;
}