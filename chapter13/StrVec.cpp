#include <string>
#include <iostream>
#include <memory>
using namespace std;

class StrVec {
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}  // alloc将执行默认初始化
    StrVec(const StrVec&);  // 拷贝构造函数
    StrVec(StrVec&&) noexcept;  // 移动构造函数，移动操作不应该抛出任何异常
    StrVec &operator=(const StrVec&);  // 拷贝赋值运算符
    StrVec &operator=(StrVec&&) noexcept; // 移动赋值运算符，如果移动赋值不会抛出异常，则它应该声明为noexcept
    ~StrVec();
    void push_back(const string&);  // 拷贝元素
    void push_back(string &&);  // 移动元素
    size_t size() const {return first_free - elements;}
    size_t capacity() const {return cap - elements;}
    string *begin() const {return elements;}
    string *end() const {return first_free;}
private:
    static allocator<string> alloc;

    void chk_n_alloc() {
        if(size() == capacity()){
            reallocate();
        }
    }
    // 分配足够的内存来保存给定范围的元素，返回值是新空间的开始位置和尾后位置
    pair<string *, string *> alloc_n_copy(const string *, const string *);
    void free();  // 销毁元素，并释放内存
    void reallocate();  // 获得更多内存，并拷贝已有元素。为保证性能，要能够避免分配和释放string的额外开销
    string * elements;  // 指向数组首元素的指针
    string *first_free;  // 指向数组第一个空闲元素的指针
    string *cap;  // 指向数组尾后位置的指针
};

allocator<string> StrVec::alloc;

void StrVec::push_back(const string& s){
    cout << "copy..." << endl;
    chk_n_alloc();  // 确保有空间容纳元素
    alloc.construct(first_free++, s);  // 在first_free指向的元素中构建s的副本
}

void StrVec::push_back(string &&s) {
    cout << "move..." << endl;
    chk_n_alloc();
    alloc.construct(first_free ++, std::move(s));
}

pair<string*, string*> StrVec::alloc_n_copy(const string *b, const string *e) {
    auto data = alloc.allocate(e - b);
    return {data, uninitialized_copy(b, e, data)};  // 拷贝元素
}

void StrVec::free() {
    if(elements) {
        // 逆序销毁旧元素
        for(auto p = first_free; p != elements;)
            alloc.destroy(--p);  // destroy会运行string的构函数，string的析构函数会释放自己分配的内存空间
        alloc.deallocate(elements, cap - elements);
    }
}

StrVec::StrVec(const StrVec &s) {
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

// 移动构造函数，noexcept通知标准库我们的构造函数不抛出任何异常
StrVec::StrVec(StrVec &&s) noexcept : elements(s.elements), first_free(s.first_free), cap(s.cap) {
    // 令s进入这样的状态，对其运行析构函数是安全的
    s.elements = s.first_free = s.cap = nullptr;
}

StrVec::~StrVec(){
    free();
}

StrVec &StrVec::operator=(const StrVec &rhs) {
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

// 移动赋值运算符也必须能够处理自赋值
StrVec &StrVec::operator=(StrVec &&rhs) noexcept {
    // 直接检测自赋值
    if(this != &rhs){
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;

        // 将rhs置于可析构状态
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

void StrVec::reallocate() {
    // 分配当前大小2倍的内存空间
    auto newcapacity = size() ? 2 * size() : 1;
    // 分配新内存
    auto newdata = alloc.allocate(newcapacity);

    // 将数据从旧内存移到新内存
    // auto dest = newdata;
    // auto elem = elements;
    // for(size_t i = 0; i != size(); ++i){
    //     alloc.construct(dest ++, std::move(*elem++));  // 调用move返回的结果会令construct使用string的移动构造函数
    // }

    // 利用移动迭代器将数据从旧内存移动到新内存
    auto dest = uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), newdata);

    free();  // 释放旧内存空间
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

void test1(){
    StrVec vec;
    vec.push_back("aa");  // 移动元素, "aa"是临时string
    vec.push_back("bb");  // 移动元素
    vec.push_back("cc");  // 移动元素

    string s = "dd";
    vec.push_back(s);  // 拷贝元素
    for(auto begin = vec.begin(); begin != vec.end(); ++begin) {
        cout << *begin << " ";  // aa bb cc dd
    }
    cout << endl;
    cout << vec.size() << endl;  // 4
    cout << vec.capacity() << endl;  // 4
}

int main(){

    test1();

    system("pause");
    return 0;
}