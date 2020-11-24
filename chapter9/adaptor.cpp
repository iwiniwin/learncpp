#include <string>
#include <iostream>
#include <deque>
#include <stack>
#include <vector>
#include <queue>
using namespace std;

void test1(){
    deque<int> deq = {1, 2, 3};
    stack<int> stk(deq);  // 从deq拷贝元素到stk

    vector<string> vec = {"a", "bb"};
    stack<string, vector<string>> str_stk(vec);  // str_stk在vector上实现
    // stack<string> str_stk2(vec);  // error : stack和queue默认是基于deque实现的
    queue<string, vector<string>> q1(vec);
}

// stack适配器
void test2(){
    stack<int> s;  // 空栈
    s.push(3);
    s.pop();
    // auto a = s.pop();  // error : pop函数没有返回值
    cout << s.size() << endl;  // 0
}

// 队列适配器
void test3(){
    queue<int> q1;
    q1.push(1);
    q1.push(5);
    q1.push(3);
    priority_queue<int> q2;
    q2.push(1);
    q2.push(5);
    q2.push(3);

    cout << q1.back() << endl;  // 3，返回尾元素，但不删除
    cout << q1.size() << endl;  // 3
    // q2.back();  // error : priority_queue没有成员函数back

    // q1.top();  // error : queue没有成员函数top
    cout << q2.top() << endl;  // 5，返回最高优先级元素，但不删除

    cout << q2.size() << endl;  // 3
    q2.pop();
    // auto a = q2.pop();    // error : pop函数没有返回值
    cout << q2.size() << endl;  // 2

    cout << q1.front() << endl;  // 1
    q1.pop();
    cout << q1.front() << endl;  // 5
}

int main(){

    test1();
    test2();
    test3();

    system("pause");
    return 0;
}