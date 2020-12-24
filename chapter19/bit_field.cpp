/*
 * @Author: iwiniwin
 * @Date: 2020-12-24 21:49:33
 * @Last Modified by: iwiniwin
 * @Last Modified time: 2020-12-24 21:56:38
 * @Description: 位域
 */
#include <string>
#include <iostream>
using namespace std;

class File {
public:
    unsigned int mode: 2;  // mode位域占2位，通常情况下最好将位域设为无符号类型，存储在带符号类型中的位域的行为将因具体实现而异
    unsigned owner: 3;  // owner位域占3位

    enum modes {READ = 01, WRITE = 02, EXECUTE = 03};  // 八进制形式

    File &open(modes);
    void close() {
        // auto a = &mode;  // error : 取地址运算符不能作用域位域，因此任何指针都无法指向类的位域
        // 使用位域
        mode = 1;  
        if(mode) {
            mode |= mode;
            if(mode & owner) {
                
            }
        }
    }

    bool isRead() const {
        return mode & READ;
    }

    void setWrite() {
        mode |= WRITE;
    }
};

void test1(){

}

int main(){

    test1();

    system("pause");
    return 0;
}