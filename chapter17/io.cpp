#include <string>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <fstream>
using namespace std;

void test1(){
    // boolalpha操纵符可以控制bool类型的输出格式
    cout << boolalpha << true << " " << false << endl;  // true false，打印的不再是1 0

    cout << true << endl;  // true，操纵符的影响是持续的

    cerr << true << endl;  // 1,其他流不受影响

    cout << noboolalpha << true << endl;  // 1, 可以通过noboolalpha取消控制

    cout << oct << 20 << " " << 1024 << endl;  // 24 2000， 整型值输出用八进制
    cout << hex << 20 << " " << 1024 << endl;  // 14 400，整型值输出用十六进制

    cout << 20.25 << endl;  // 20.25，浮点型输出不会受影响

    cout << dec << 20 << " " << 1024 << endl;  // 20 1024， 整型值输出用十进制

    // 输出时显示进制
    cout << showbase;
    cout << oct << 20 << " " << 1024 << endl;  // 024 02000， 前导0表示八进制
    cout << hex << 20 << " " << 1024 << endl;  // 0x14 0x400，前导0x表示十六进制
    cout << uppercase << 20 << " " << 1024 << endl;  // 0X14 0X400，大写输出
    cout << dec << 20 << " " << 1024 << endl;  // 20 1024， 无前导表示十进制
    cout << noshowbase << nouppercase;  // 恢复状态，输出时不再显示进制

}

// 浮点值输出控制
void test2() {
    // cout.precision()返回当前精度值
    cout << cout.precision() << " " << sqrt(2.0) << endl;  // 6   1.41421
    // 设置精度值
    cout.precision(12);
    cout << cout.precision() << " " << sqrt(2.0) << endl;  // 12   1.41421356237

    // 通过setprecision操纵符设置精度
    cout << setprecision(3);
    cout << cout.precision() << " " << sqrt(2.0) << endl;  // 3    1.41

    // 控制小数点显示
    cout << 10.0 << " " << showpoint << 10.0 << noshowpoint << endl;  // 10 10.0
}


// 输出空白
void test3() {
    int i = -16;
    double d = 3.14159;

    // 补白第一列，setw指定下一个数字或字符串的最小空间
    cout << "i: " << setw(12) << i << "next col" << '\n' << "d: " << setw(12) << d << "next col" << '\n';

    // 补白第一列且左对齐所有列
    cout << left << "i: " << setw(12) << i << "next col" << '\n' << "d: " << setw(12) << d << "next col" << '\n' << right;

    // 补白第一列且右对齐所有列
    cout << right << "i: " << setw(12) << i << "next col" << '\n' << "d: " << setw(12) << d << "next col" << '\n';

    // 补白第一列但补在域的内部
    cout << internal << "i: " << setw(12) << i << "next col" << '\n' << "d: " << setw(12) << d << "next col" << '\n';

    // 补白第一列，用#作为补白字符
    cout << setfill('#') << "i: " << setw(12) << i << "next col" << '\n' << "d: " << setw(12) << d << "next col" << '\n' << setfill(' ');

    /*
    i:          -16next col
    d:         3.14next col
    i: -16         next col
    d: 3.14        next col
    i:          -16next col
    d:         3.14next col
    i: -         16next col
    d:         3.14next col
    i: -#########16next col
    d: ########3.14next col
    */
}

// 未格式化IO
void test4() {
    char ch0;
    cin.get(ch0);  // 读取下一个字节存入到ch0字符中

    int ch;  // 使用一个int而不是一个char来保存get()返回的值
    while((ch = cin.get()) != EOF)
        cout.put(ch);
}

// 随机访问
void test5() {
    ostringstream writeStr;
    // 记录当前写位置
    ostringstream::pos_type mark = writeStr.tellp();
    // 回到刚才记录的位置
    writeStr.seekp(mark);
}

// 读写同一文件
void test6() {
    // 以读写方式打开文件，并定位到文件尾
    fstream inOut("G:/Project/learncpp/build/test.txt", fstream::ate | fstream::in | fstream::out);
    if(!inOut) {
        cout << "unable to open file!" << endl;
        return;
    }
    // inOut以ate模式打开，因此一开始就定义到其文件末尾
    auto end_mark = inOut.tellg();

    inOut.seekg(0, fstream::beg);  // 重定位到文件开始，seek到距文件起始位置偏移为0的地方

    size_t cnt = 0;  // 字节数累加器

    string line;  // 保存输入中的每行

    while(inOut && inOut.tellg() != end_mark && getline(inOut, line)) {
        cnt += line.size() + 1;  // 加1表示换行符
        auto mark = inOut.tellg();  // 记住读取位置

        inOut.seekp(0, fstream::end);  // 将写标记移到文件尾
        inOut << cnt;  // 输出累计的长度
        if(mark != end_mark) inOut << " ";

        inOut.seekg(mark);  // 恢复读位置
    }

    inOut.seekp(0, fstream::end);  // 定位到文件尾
    inOut << "\n";  // 在文件尾输出一个换行符
    inOut.close();
}

int main(){

    test1();
    test2();
    test3();
    // test4();
    test5();
    test6();

    system("pause");
    return 0;
}