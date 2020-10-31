#include <string>
using std::string;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    // 初始化string对象
    string s1;          // 默认初始化，s1是一个空字符串
    string s2 = s1;     // s2是s1的副本，[拷贝初始化]
    string s3 = "hiya"; // s3是该字符串字面值的副本，[拷贝初始化]
    string s4(5, 'c');  // s4的内容是ccccc，[直接初始化]
    string s5 = "";     // s1 == s5 true
    cout << s1.empty() << endl;  // 1
    cout << s3.size() << endl;  // 4

    string::size_type a = s3.size();

    string s6 = s1 + "a";
    string s7 = s1 + "a" + "b";
    // string s8 = "a" + "b"; // error，不能把字面值直接相加
    // string s9 = "a" + "b" + s1; // error，不能把字面值直接相加

    // 读写string对象
    string s;
    cin >> s;
    cout << s << endl;

    // 读取未知数量的string对象
    // string word;
    // while(cin >> word)
    //     cout << word << endl;

    // 使用getline读取一行
    string line;
    while (getline(cin, line))
        cout << line << endl; // line对象中并不包含换行符

    return 0;
}