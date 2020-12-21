#include <string>
#include <iostream>
#include <random>
#include <ctime>
using namespace std;

// 随机数引擎
void test1(){
    default_random_engine e;  // 生成随机无符号数
    cout << e() << endl;  // 一个随机数

    // 引擎可以生成的最小和最大数
    cout << e.min() << endl;  // 1
    cout << e.max() << endl;  // 2147483646
}

// 随机数分布
void test2() {
    uniform_int_distribution<unsigned> u(0, 9);  // 此类型生成均匀分布的unsigned值
    default_random_engine e;
    cout << u(e) << endl;  // 生成在指定范围内并服从均匀分布的值
}

// 随机数种子
void test3() {
    default_random_engine e1;  // 使用默认种子
    default_random_engine e2(2147483646);  // 使用给定的种子值


    default_random_engine e3;
    e3.seed(32767);  // 使用seed设置一个新种子值
    default_random_engine e4(32767);  // e4和e3将生成相同的序列

    default_random_engine e5(time(0));  // 稍微随机些的种子，秒级
}

// 生成随机实数
void test4() {
    default_random_engine e;
    uniform_real_distribution<double> u(0, 1);  // 生成均匀分布的0到1的浮点数
    cout << u(e) << endl;  // 一个随机浮点数

    uniform_real_distribution<> u2(0, 1);  // 使用默认参数类型double值
}

// 生成非均匀分布的随机数
void test5() {
    // 正态分布
    default_random_engine e;
    normal_distribution<> n(4, 1.5);  // 正态分布，生成均值4，标准差1.5
    cout << n(e) << endl;

    // 伯努利分布，总是返回一个bool值，返回true的概率默认是0.5
    bernoulli_distribution b;  // 默认是一半一半的概率
    cout << b(e) << endl;

    bernoulli_distribution b2(0.55);  // 0.55的概率返回true
    cout << b2(e) << endl;
}

int main(){

    test1();
    test2();
    test3();
    test4();
    test5();

    system("pause");
    return 0;
}