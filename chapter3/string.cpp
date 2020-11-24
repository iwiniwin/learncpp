#include <string>
using std::string;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <cctype>
#include <cstring>

void test()
{
    string str("some string, hello world !");
    for (auto c : str)
    {
        if (ispunct(c))
            cout << c << endl;
    }

    // 使用范围for语句改变字符串中的内容
    for (auto &c : str)
        c = toupper(c);  // c是一个引用，因此赋值语句将改变s中字符的值
    cout << str << endl; // SOME STRING, HELLO WORLD !

    // decltype(str[1]) a;  // error : a是引用必须初始化，str[1]，通过下标访问，返回的是该位置上字符的引用

    const string uu("tff");
    // uu[0] = 'a';  // error : 常量，不能修改

    // 通过下标遍历字符串
    for (decltype(str.size()) index = 0; index != str.size(); index++)
        cout << str[index] << endl;

    string sss;
    cout << sss[6] << "vvv" << endl; // 是一个未定义的值
}

// C风格字符串
void test2()
{
    char ca[] = {'a', 'b', 'c', '\0', 'd'};
    char cb[] = {'a', 'b', 'c', '\0'};
    cout << std::strlen(ca) << endl;     // 字符串长度3，不包含空字符
    cout << std::strcmp(ca, cb) << endl; // 比较两个字符串是否相等，这里是0，表示相等
    std::strcat(ca, cb);                 // 将cb附加到ca之后
    cout << ca << endl;                  // abcabc

    std::strcpy(cb, ca); // 将ca拷贝给cb
    cout << cb << endl;  // abcabc

    string s = "abcdefg";
    // char *str = s;  // error : 不能直接将string转换为char *
    // char *str = s.c_str();  // 不能从const char *转换成char *
    const char *str = s.c_str(); // c_str()函数返回一个c风格的字符串，即指针，指向一个以空字符结束的字符数组
    cout << str << endl;         // abcdefg
    s = "xyz";
    cout << s.c_str() << endl; // xyz
    cout << str << endl;       // xyz
}

void test3()
{
    // 初始化string对象
    string s1;                  // 默认初始化，s1是一个空字符串
    string s2 = s1;             // s2是s1的副本，[拷贝初始化]
    string s3 = "hiya";         // s3是该字符串字面值的副本，[拷贝初始化]
    string s4(5, 'c');          // s4的内容是ccccc，[直接初始化]
    string s5 = "";             // s1 == s5 true
    cout << s1.empty() << endl; // 1
    cout << s3.size() << endl;  // 4

    string ss1 = {"vvv"};
    string ss2 = {'k', 'd', 'v'};
    string ss3{"ss"};
    string ss4{'s', 'd'};
    cout << ss1 << endl;
    cout << ss2 << endl;
    cout << ss3 << endl;
    cout << ss4 << endl;

    string::size_type a = s3.size(); // a == 4 true

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
}

void test4(){
    string s = "abcd";
    cout << s.substr(0, 2) << endl;  // ab
    s.substr(0, 2)[0] = 'z';  // substr返回的只是字符的拷贝
    cout << s << endl;  // abcd

    s.insert(2, 2, '!');  // 在b后面插入2个!
    cout << s << endl;  // ab!!cd
    s.erase(2, 2);  // 删除包括2位置后的共2个元素
    cout << s << endl;  // abcd
    s.replace(2, 2, "zz");  // 从位置2开始，替换2个字符为zz
    cout << s << endl;  // abzz
}

// find
void test5(){
    string name("AnnaBelle");
    auto pos1 = name.find("Anna");
    cout << pos1 << endl;  // 0
    auto pos2 = name.find("anna");  // 搜索是大小写敏感的
    cout << (pos2 == string::npos) << endl;  // 1

    cout << name.find_first_of("efg") << endl;  // 5，查找参数中任何一个字符第一次出现的位置
    cout << name.find_last_of("efg") << endl;  // 8，查找参数中任何一个字符最后一次出现的位置
    cout << name.find_first_not_of("efg") << endl;  // 0，查找name中第一个不在参数中的字符
    cout << name.find_last_not_of("efg") << endl;  // 7，查找name中最后一个不在参数中的字符

    cout << name.rfind("Be", 7) << endl;  // 4，从7位置开始，从右至左（逆向）搜索
}

void test6(){
    string s1 = "ab";
    string s2 = "abc";
    string s3 = "a";
    string s4 = "ab";
    cout << s1.compare(s2) << endl;  // -1，小于
    cout << s1.compare(s3) << endl;  // 1，大于
    cout << s1.compare(s4) << endl;  // 0，等于
}

// 数值转换
void test7(){
    int i = 42;
    string s = std::to_string(i);  // 将i转换Wie字符串
    double d = stod(s);  // 将字符串转化为浮点数
    float f = stof(s);
    int j = stoi(s);
    long long ll = stoll(s);
    long double ld = stold(s);
}

int main()
{
    // test();
    // test2();
    // test3();
    // test4();
    // test5();
    // test6();
    test7();

    system("pause");
    return 0;
}