#include <string>
#include <iostream>
#include <bitset>
using namespace std;

void test1(){
    bitset<32> bitvec(1U);  // 32位，低位为1，其他位为0

    bitset<13> bitvec1(0xbeef);  // 二进制为1111011101111，bitvec1比初始值小，初始值中的高位被丢弃
    bitset<20> bitvec2(0xbeef);  // 二进制为0000101111011101111，bitvec2比初始值大，它的高位被置为0
    bitset<128> bitvec3(~0ULL);  // 0~63为为1，63 ~127位位0

    bitset<32> bitvec4("1100");  // 2,3位为1，剩余两位为0
}

void test2() {
    bitset<32> bitvec(1U);
    bool is_set = bitvec.any();  // true，有1位置位
    bool is_not_set = bitvec.none();  // false，因为有1位置位了
    bool all_set = bitvec.all();  // false，因为有1位置位了
    size_t onBits = bitvec.count();  // 返回1，置位的位数
    size_t sz = bitvec.size();  // 返回32
    bitvec.flip();  // 翻转bitvec中的所有位
    bitvec.reset();  // 将所有位复位
    bitvec.set();  // 将所有位置位

    bitvec.flip(0);  // 翻转第一位
    bitvec.set(bitvec.size() - 1);  // 置位最后一位
    bitvec.set(0, 0);  // 复位第一位
    bitvec.reset(0);  // 复位第一位
    bitvec.test(0);  // 返回false，因为第一位是复位的

    bitvec[0] = 0;  // 将一位复位
    bitvec[31] = bitvec[0];  // 将最后一位设置而为与第一位一样
    bitvec[0].flip();  // 翻转第一位
    bool b = bitvec[0];  // 将第一位的值转换为bool类型    

    unsigned long ulong = bitvec.to_ulong();
}

int main(){

    test1();
    test2();

    system("pause");
    return 0;
}