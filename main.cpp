//Ŀǰֻ֧�ֲ������ļ�����������Ҫ�����붼д������ļ��С�
#include <iostream>
#include <fstream>
#include <string>

#include "info.h"
using namespace std;

int main(int argc, char* argv[])
{

    string file_name = argv[1]; //���ַ�������Ϊʶ���C���Գ����ļ���
    ifstream file(file_name);

    if ( !file.is_open() )
    {
        std::cerr << "�޷����ļ���" << std::endl;
        return 1;
    }

    string line;
    int lineCount = 0;
    while ( getline(file, line) )
    {
        lineCount++;
        Lexer lexer(line, lineCount);
        vector<Token> tokens = lexer.tokenize();
        // ���ÿ�� token �Լ��к�
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
    file.close(); // �ر��ļ�

	return 0;
}