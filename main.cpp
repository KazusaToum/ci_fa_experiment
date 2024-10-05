//目前只支持测评单文件程序，所以需要将代码都写到这个文件中。
#include <iostream>
#include <fstream>
#include <string>

#include "info.h"
using namespace std;

int main(int argc, char* argv[])
{

    string file_name = argv[1]; //该字符串变量为识别的C语言程序文件名
    ifstream file(file_name);

    if ( !file.is_open() )
    {
        std::cerr << "无法打开文件！" << std::endl;
        return 1;
    }

    string line;
    int line_count = 0;
    attribute total;
    /*程序每次运行只需要考虑识别一个C语言程序;
      需要使用读取文件的操作,可以在自己的本地环境里创建样例文件进行测试；
      在自己的IDE里测试时可以将file_name赋其他的值，
      但注意，最终测评时由平台提供的main参数来传入文件名*/
    while ( getline(file, line) )
    {
        line_count++;

    }

    file.close(); // 关闭文件

    std::cout << "文件总共有 " << line_count << " 行。" << std::endl;

	return 0;
}