#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

void test1(){
    ofstream out1, out2;
    // out1 = out2;  // error : IO对象不能拷贝和赋值

    int ival;
    if(cin >> ival){  // 如果输入的是字符，则将读取失败
        cout << ival << endl;
    }else{
        cout << "error" << endl;
    }

    cout << cin.good() << endl;  
    cout << cin.fail() << endl;

    auto old_state = cin.rdstate();  // 记录cin的当前状态
    cin.clear();
    cin.setstate(old_state);

    cin.clear(old_state & ~cin.failbit & ~cin.badbit);  // 复位failbit和badbit，保持其它标志位不变


    cout << "hi" << endl;  // 输出hi和一个换行符，然后刷新缓冲区
    cout << "hi" << flush;  // 输出hi，然后刷新缓冲区，不附加任何额外字符
    cout << "hi" << ends;  // 输出hi和一个空字符，然后刷新缓冲区
    cout << "z";

    cout << unitbuf;  // 所有输出操作后都会立即刷新缓冲区

    cout << nounitbuf;  // 回到正常的缓冲方式

    // cin >> ival;  // 标准库cout和cin关联在一起，因此这句会导致cout的缓冲区被刷新

    cin.tie(&cout);  // 将cin和cout关联到一起
    ostream *old_tie = cin.tie(nullptr);  // cin不再与其它流关联
    cin.tie(&cerr);  // 读取cin会刷新cerr而不是cout
    cin.tie(old_tie);  // 恢复cin和cout的关联
}

istream &read(istream &is){
    int a;
    is >> a;
    return is;
}

// fstream
void test2(){
    ifstream in("");
    read(in);  // 接收iostream类型引用的函数，可以使用fstream调用

    string out_file = "G:/Project/learncpp/build/abc.txt";

    ofstream out;  // 默认情况下，当打开一个ofstream时，文件内容会被丢弃。阻止丢弃的方式是显式指定app模式
    out.open(out_file);   // 如果open失败，failbit会被置位
    if (out) {  // 检查open是否成功
        cout << out_file << " open success" << endl;
    }else{
        cout << out_file << " open failed" << endl;;
    }

    in.close();  // 关闭文件
    string in_file = "G:/Project/learncpp/build/abc.txt";
    in.open(in_file);  // 打开另一个文件，如果open成功，是的good()为true

    ofstream out2(out_file, ofstream::out | ofstream::app);  // 追加，可以保留文件内容
    cout << out2.is_open() << endl;
    if (out2) {
        cout << out_file << " open success" << endl; 
        out2 << "this is a test" << endl;  // 向文件中写入内容
        out2.close();
    }else{
        cout << out_file << " open failed" << endl;;
    }
    
}

// sstream
void test3(){
    string s = "lee 654554455 205545655 8651146565";
    istringstream record(s);  // 保存s的一个拷贝

    string name, word;
    record >> name;
    cout << "name : " << name << endl;
    while(record >> word){
        cout << "phone : " << word << endl;
    }

    cout << record.str() << endl;  // 返回record所保存的string的拷贝

    ostringstream badNumbers;
    badNumbers << "bad1 : " <<  "654554455";
    badNumbers << "bad2 : " <<  "8651146565";


    cout << "badNumbers : " << badNumbers.str() << endl;
}

int main(){
    // test1();
    // test2();
    test3();

    system("pause");
    return 0;
}