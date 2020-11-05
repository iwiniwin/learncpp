#include <string>
using std::string;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <cctype>

void test(){
    string str("some string, hello world !");
    for(auto c : str){
        if(ispunct(c))
            cout << c << endl;
    }

    // 使用范围for语句改变字符串中的内容
    for(auto &c : str)
        c = toupper(c);  // c是一个引用，因此赋值语句将改变s中字符的值
    cout << str << endl;  // SOME STRING, HELLO WORLD !

    // decltype(str[1]) a;  // error : a是引用必须初始化，str[1]，通过下标访问，返回的是该位置上字符的引用

    const string uu("tff");
    // uu[0] = 'a';  // error : 常量，不能修改

    // 通过下标遍历字符串
    for(decltype(str.size()) index = 0; index != str.size(); index ++)
        cout << str[index] << endl;

    string sss;
    cout << sss[6] << "vvv" << endl;  // 是一个未定义的值
}

int main()
{
    test();
    // 初始化string对象
    string s1;          // 默认初始化，s1是一个空字符串
    string s2 = s1;     // s2是s1的副本，[拷贝初始化]
    string s3 = "hiya"; // s3是该字符串字面值的副本，[拷贝初始化]
    string s4(5, 'c');  // s4的内容是ccccc，[直接初始化]
    string s5 = "";     // s1 == s5 true
    cout << s1.empty() << endl;  // 1
    cout << s3.size() << endl;  // 4

    string ss1 = {"vvv"};
    string ss2 = {'k', 'd', 'v'};
    string ss3{"ss"};
    string ss4{'s', 'd'};
    cout << ss1 << endl;
    cout << ss2 << endl;
    cout << ss3 << endl;
    cout << ss4 << endl;

    string::size_type a = s3.size();  // a == 4 true

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
    // while(cin >> word)  // 如果流有效，即没有遇到文件结束标记或非法输入
    //     cout << word << endl;

    // 使用getline读取一行
    string line;
    while (getline(cin, line))
        cout << line << endl; // line对象中并不包含换行符

    system("pause");
    return 0;
}