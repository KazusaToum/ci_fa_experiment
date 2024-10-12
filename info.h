//
// Created by betsy on 2024/10/4.
//

#ifndef CI_FA_EXPERIMENT_INFO_H
#define CI_FA_EXPERIMENT_INFO_H

#include <vector>
#include <iostream>
#include <string>
#include <unordered_set>
#include <cctype>

using namespace std;
enum TokenType
{
    KEYWORD,       //关键字
    IDENTIFIER,     //标识符
    OPERATOR,     //运算符
    DELIMITER,    //分隔符
    CHAR,         //字符常量
    STRING,       //字符串
    NUM,          //数字
    ERROR         //错误
};
int record[8] = {0, 0, 0, 0, 0, 0, 0, 0};

// Token 类, 表示一个词法记号，包含类型 TokenType 和值 value，并有方法返回类型的字符串表示。
class Token
{
public:
    TokenType type;
    std::string value;
    int lineNumber;
    Token(TokenType type, const std::string& value, int lineNumber)
    : type(type), value(value) , lineNumber(lineNumber){}

    string getTokenTypeString() const
    {
        switch (type) {
            case TokenType::IDENTIFIER: return "IDENTIFIER";
            case TokenType::KEYWORD: return "KEYWORD";
            case TokenType::OPERATOR: return "OPERATOR";
            case TokenType::DELIMITER: return "DELIMITER";
            case TokenType::CHAR: return "CHARCON";
            case TokenType::STRING: return "STRING";
            case TokenType::NUM: return "NUMBER";
            default: return "ERROR";
        }
    }
};

// SymbolTable 类, 存储关键字、分割符和运算符的集合，提供检测是否是关键字、运算符或分割符的方法。
class SymbolTable
{
public:
    std::unordered_set<std::string> keywords = {"auto", "double", "int", "struct", "break", "else", "static", "long",
                                                "switch", "case", "enum", "register", "typedef", "char", "extern", "return",
                                                "union", "const", "float", "short", "unsigned", "continue", "for", "signed",
                                                "void", "default", "goto", "sizeof", "volatile", "do", "if", "while"};
    std::unordered_set<char> delimiters = {';', ',', ':', '?', '(', ')', '{', '}', '[', ']'};
    std::unordered_set<std::string> operators = {"+", "-", "*", "/", "%", "++", "--",
                                                 "==", "!=", "<", ">", "<=", ">=",
                                                 "&&", "||", "!",
                                                 "&", "|", "^", "~", "<<", ">>",
                                                 "=", "+=", "-=", "*=", "/=", "%=", "<<=",
                                                 ">>=", "&=", "^=", "|=", ".", "->"};

    bool isKeyword(const std::string& word)
    {
        return keywords.find(word) != keywords.end();
    }
/*
    bool isDelimiter(char ch)
    {
        return delimiters.find(ch) != delimiters.end();
    }
*/
    bool isOperator(const std::string& op)
    {
        return operators.find(op) != operators.end();
    }
};
class Lexer
{
private:
    string input;
    int pos;
    SymbolTable symbolTable;
    int lineNumber;
    bool isIdentifierStart(char ch)
    {
        return std::isalpha(ch) || ch == '_';
    }

    bool isIdentifierPart(char ch)
    {
        return std::isalnum(ch) || ch == '_';
    }

    bool isDigit(char ch)
    {
        return isdigit(ch);
    }

    char peek()
    {
        if (pos < input.size()) return input[pos];
        return '\0';
    }

    char next()
    {
        if (pos < input.size()) return input[pos++];
        return '\0';
    }
    void skipWhitespace()
    {
        while (isspace(peek())) next();
    }

public:
    Lexer(const std::string& input, int lineNumber)
            : input(input), pos(0), lineNumber(lineNumber) {}

    vector<Token> tokenize()
    {
        vector<Token> tokens;
        int state = 0;
        char current;
        while (pos < input.size())
        {

            switch (state)
            {
                //处理首个读取的字符
                case 0:
                    skipWhitespace();
                    current = peek();
                    switch (current)
                    {
                        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
                        case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
                        case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
                        case 'V': case 'W': case 'X': case 'Y': case 'Z':
                        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
                        case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
                        case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
                        case 'v': case 'w': case 'x': case 'y': case 'z': case '_':
                            state = 1;
                            break;

                        case '-': case '+': case '=': case '%': case '*': case '/': case '&':
                        case '|': case '!': case '<': case '>': case '.': case '^': case '~':
                            state = 2;
                            break;

                        case ':': case ',': case ';': case '?': case '(': case ')': case '{':
                        case '}': case '[': case ']':
                            state = 3;
                            break;

                        case '0': case '1': case '2': case '3': case '4': case '5': case '6':
                        case '7': case '8': case '9':
                            state = 5;
                            break;
                        default:
                            next();
                            state = 0;
                            break;
                    }
                    break;
                case 1:
                {
                    string identifier;
                    while (isIdentifierPart(peek())) {
                        identifier += next();
                    }
                    if (symbolTable.isKeyword(identifier)) {
                        tokens.push_back(Token(TokenType::KEYWORD, identifier, lineNumber));
                        record[TokenType::KEYWORD]++;
                    }
                    state = 0;
                    break;
                }
                case 2:
                {
                    string op;
                    op = next();
                    if (symbolTable.isOperator(op + peek() + input[pos + 1]))
                    {
                        op += next();
                        op += next();
                    } else if(symbolTable.isOperator(op + peek()) )
                    {
                        op += next();
                    }
                    tokens.push_back(Token(TokenType::OPERATOR, op, lineNumber));
                    record[TokenType::OPERATOR]++;
                    state = 0;
                    break;
                }

                case 3:
                {
                    record[TokenType::DELIMITER]++;
                    string de;
                    de += next();
                    tokens.push_back(Token(TokenType::DELIMITER, de, lineNumber));
                    state = 0;
                    break;
                }
                default:
                    state = 0;
                    break;
            }
            /*
            if (isIdentifierStart(current))
            {
                string identifier;
                while (isIdentifierPart(peek()))
                {
                    identifier += next();
                }
                if (symbolTable.isKeyword(identifier))
                {
                    tokens.push_back(Token(TokenType::KEYWORD, identifier, lineNumber));
                } else
                {
                    tokens.push_back(Token(TokenType::IDENTIFIER, identifier, lineNumber));
                }
            }

                // 数字常量
            else if (isDigit(current))
            {
                string number;
                while (isDigit(peek()))
                {
                    number += next();
                }
                tokens.push_back(Token(TokenType::NUM, number, lineNumber));
            }
            */
        }
        return tokens;
    }
};

#endif //CI_FA_EXPERIMENT_INFO_H
