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
    int line_count = 0;
    attribute total;
    /*����ÿ������ֻ��Ҫ����ʶ��һ��C���Գ���;
      ��Ҫʹ�ö�ȡ�ļ��Ĳ���,�������Լ��ı��ػ����ﴴ�������ļ����в��ԣ�
      ���Լ���IDE�����ʱ���Խ�file_name��������ֵ��
      ��ע�⣬���ղ���ʱ��ƽ̨�ṩ��main�����������ļ���*/
    while ( getline(file, line) )
    {
        line_count++;

    }

    file.close(); // �ر��ļ�

    std::cout << "�ļ��ܹ��� " << line_count << " �С�" << std::endl;

	return 0;
}