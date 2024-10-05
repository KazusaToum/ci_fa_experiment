//
// Created by betsy on 2024/10/4.
//

#ifndef CI_FA_EXPERIMENT_INFO_H
#define CI_FA_EXPERIMENT_INFO_H

#include <vector>
#include <iostream>
#include <sstream>  // 用于分割字符串
#include <string>
using namespace std;

enum State
{
    LETTER,       //标识符或者关键字
    OPERATOR = 2,     //运算符
    DELIMITER,    //分隔符
    CHAR,         //字符常量
    STRING,       //字符串
    NUM,          //数字
    ERROR         //错误
};

class attribute
{
private:
    //vector<string> words; // 用于存储分割后的字符串
    State state;
    int forward;   //前向指针
    string word;

    int type[7];

public:

    void cleanUp() { }
};


#endif //CI_FA_EXPERIMENT_INFO_H
