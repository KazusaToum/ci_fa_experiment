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
    int lineCount = 0;
    while ( getline(file, line) )
    {
        lineCount++;
        Lexer lexer(line, lineCount);
        vector<Token> tokens = lexer.tokenize();
        // 输出每个 token 以及行号
        for (const Token& token : tokens)
        {
            cout << token.lineNumber << " <"
                 << token.getTokenTypeString() << ","
                 << token.value << ">\n";
        }
    }
    cout << lineCount << endl;
    cout << record[0];
    for(int i = 0; i < 7; i++)
        cout <<  ' ' <<record[i];
    cout << endl << record[7];
    file.close(); // 关闭文件

	return 0;
}