#include <string>
#include <iostream>
#include <regex>
using namespace std;

void test1(){
    string pattern("[^c]ei");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";  // regex使用的正则表达式语言是ECMAScript，[[:alpha:]]表示匹配任意子
    regex r(pattern);  // 构造一个用于查找模式的regex
    smatch results;  // 定义一个对象保存搜索结果

    string test_str = "receipt freind theif receive";

    if(regex_search(test_str, results, r)) {  // 如果有匹配子串
        cout << results.str() << endl;  // freind， 打印匹配的单词
    }
}

void test2() {
    regex r("[[:alnum:]]+\\.(cpp|cxx|cc)$", regex::icase);  // 一个或多个字母或数字后接一个句点再接3个文件扩展名之一，忽略大小写

    try {
        regex r("[[:alnum:]+\\.(cpp|cxx|cc)$");  // 运行时检查会有错误，漏掉了一个]
    }catch(regex_error e) {
        cout << e.what() << "\ncode: " << e.code() << endl;
    }

    smatch results;  // 将匹配string输入序列，而不是char*
    // regex_search("myfile.cc", results, r);  // error : 输入的是char*，不匹配
    cmatch results2;
    regex_search("myfile.cc", results2, r);  // 正确，搜索的是一个字符数组，所以使用cmatch
}

// 处理多个匹配结果
void test3() {
    string pattern("[^c]ei");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";  // regex使用的正则表达式语言是ECMAScript，[[:alpha:]]表示匹配任意子
    regex r(pattern, regex::icase);  // 在匹配时忽略大小写

    string test_str = "receipt freind theif receive";

    for(sregex_iterator it(test_str.begin(), test_str.end(), r), endit; it != endit; ++it) {  // sregex_iterator的构造函数会调用regex_search将it定位到第一个匹配的位置
        cout << it->str() << endl;  // freind  theif
    }
}

// 获取匹配结果的上下文
void test4(){
    string pattern("[^c]ei");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";  // regex使用的正则表达式语言是ECMAScript，[[:alpha:]]表示匹配任意子
    regex r(pattern, regex::icase);  // 在匹配时忽略大小写

    string test_str = "receipt freind theif receive";

    for(sregex_iterator it(test_str.begin(), test_str.end(), r), endit; it != endit; ++it) {  // sregex_iterator的构造函数会调用regex_search将it定位到第一个匹配的位置
        // it->prefix，一个ssub_match对象，表示当前匹配之前的序列
        auto pos = it->prefix().length();  // 前缀的大小
        cout << "prefix : " << it->prefix().str() << "\nsuffix: " << it->suffix().str() << endl;
        /*
            prefix : receipt
            suffix:  theif receive
            prefix :
            suffix:  receive
        */
    }
}

// 子表达式
void test5() {
    regex r("([[:alnum:]]+)\\.(cpp|cxx|cc)$", regex::icase);   // r有两个子表达式，第一个是点之前表示文件名的部分，第二个表示文件扩展名
    smatch results;
    string test_str = "myfile.cc";
    if(regex_search(test_str, results, r)) {
        cout << results.str(1) << endl;  // myfile，打印第一个子表达式
        cout << results.str(2) << endl;  // cc

        cout << results.str(0) << endl;  // myfile.cc，匹配位置0，表示整个模式对应的匹配
        cout << results.str() << endl;  // myfile.cc，打印匹配结果
    }
}

// regex_replace
void test6() {
    regex r("([[:alnum:]]+)\\.(cpp|cxx|cc)$", regex::icase);
    string test_str = "myfile.cc";
    string fmt = "$1-$2";  // 将文件名与后缀名用-相连
    cout << regex_replace(test_str, r, fmt) << endl;  // myfile-cc

    test_str = "aaa-myfile.cc";
    cout << regex_replace(test_str, r, fmt) << endl;  // aaa-myfile-cc

    // regex_constants::format_no_copy指示丢弃未匹配的部分
    cout << regex_replace(test_str, r, fmt, regex_constants::format_no_copy) << endl;  // myfile-cc
}

int main(){

    test1();
    test2();
    test3();
    test4();
    test5();
    test6();

    system("pause");
    return 0;
}