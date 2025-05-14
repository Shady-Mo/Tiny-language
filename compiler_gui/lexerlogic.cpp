#include "LexerLogic.h"
#include <unordered_set>
#include <map>
#include <cctype>
#include <string>

// استخدام namespace std بشكل محلي (يمكنك تعديله حسب رغبتك)
using namespace std;

// تعريف مجموعات الكلمات المحجوزة والعمليات والمعاني
unordered_set<string> reservedWords = {
    "if", "then", "else", "end", "repeat", "until", "read", "write", "int"
};

unordered_set<string> comparisonOps = { "=", "<" };
unordered_set<string> arithmeticOps = { "+", "-", "*", "/" };
unordered_set<string> symbols = { "(", ")", ";", "," };

map<string, string> synonym = {
    {"=", "Equal"},
    {"<", "Less than"},
    {"+", "Addition"},
    {"-", "Subtraction"},
    {"*", "Multiplication"},
    {"/", "Division"},
    {"(", "Left bracket"},
    {")", "Right bracket"},
    {";", "Semi colon"},
    {",", "Comma"}
};

// دالة تفحص إذا كان ال lexeme رقم أم لا
bool isNumber(const string& lexeme)
{
    if (lexeme.empty())
        return false;
    for (char c : lexeme)
    {
        if (!isdigit(c))
            return false;
    }
    return true;
}

// دالة تحدد نوع التوكن
TokenType getTokenType(const string& lexeme)
{
    if (reservedWords.count(lexeme))
        return RESERVED_WORD;
    if (comparisonOps.count(lexeme))
        return COMPARISON_OP;
    if (arithmeticOps.count(lexeme))
        return ARITHMETIC_OP;
    if (symbols.count(lexeme))
        return SYMBOL;
    if (lexeme == ":=")
        return ASSIGN_OP;
    if (isNumber(lexeme))
        return NUMBER;
    if (!lexeme.empty() && isalpha(lexeme[0]))
        return IDENTIFIER;
    return UNKNOWN;
}

// الدالة الرئيسية لتحليل النص وإرجاع قائمة التوكنات
std::vector<Token> tokenize(const std::string& input)
{
    std::vector<Token> tokens;
    std::string current;
    bool inString = false;
    bool inComment = false;
    int currentLine = 0;  // Start with line 0

    for (size_t i = 0; i < input.length(); ++i)
    {
        char c = input[i];

        if (inString)
        {
            current += c;
            if (c == '"')
            {
                tokens.push_back({ current, STRING, currentLine });
                current.clear();
                inString = false;
            }
        }
        else if (inComment)
        {
            current += c;
            if (c == '}')
            {
                tokens.push_back({ current, COMMENT, currentLine });
                current.clear();
                inComment = false;
            }
        }
        else if (c == '"')
        {
            if (!current.empty())
            {
                tokens.push_back({ current, getTokenType(current), currentLine });
                current.clear();
            }
            inString = true;
            current += c;
        }
        else if (c == '{')
        {
            if (!current.empty())
            {
                tokens.push_back({ current, getTokenType(current), currentLine });
                current.clear();
            }
            inComment = true;
            current += c;
        }
        else if (isspace(c))
        {
            if (c == '\n') {
                currentLine++;  // Increment line number for each newline
            }

            if (!current.empty())
            {
                tokens.push_back({ current, getTokenType(current), currentLine });
                current.clear();
            }
        }
        else if (c == ':' && i + 1 < input.length() && input[i + 1] == '=')
        {
            if (!current.empty())
            {
                tokens.push_back({ current, getTokenType(current), currentLine });
                current.clear();
            }
            tokens.push_back({ ":=", ASSIGN_OP, currentLine });
            i++;
        }
        else if (comparisonOps.count(string(1, c)) ||
            arithmeticOps.count(string(1, c)) ||
            symbols.count(string(1, c)))
        {
            if (!current.empty())
            {
                tokens.push_back({ current, getTokenType(current), currentLine });
                current.clear();
            }
            tokens.push_back({ string(1, c), getTokenType(string(1, c)), currentLine });
        }
        else
        {
            if (isalnum(c)) {
                current += c;
            }
            else {
                if (!current.empty()) {
                    tokens.push_back({ current, getTokenType(current), currentLine });
                    current.clear();
                }
                tokens.push_back({ string(1, c), UNKNOWN, currentLine });
            }
        }
    }

    if (!current.empty())
    {
        tokens.push_back({ current, getTokenType(current), currentLine });
    }

    return tokens;
}


// دالة تحويل نوع التوكن إلى سلسلة نصية لعرضها في الواجهة
std::string tokenTypeToString(TokenType type, const std::string& lexeme)
{
    switch (type)
    {
    case RESERVED_WORD:
        return "reserved word";
    case IDENTIFIER:
        return "identifier";
    case NUMBER:
        return "number";
    case COMPARISON_OP:
        return synonym[lexeme] + " comparison operator";
    case ARITHMETIC_OP:
        return synonym[lexeme] + " arithmetic operator";
    case ASSIGN_OP:
        return "assignment operator";
    case SYMBOL:
        return synonym[lexeme] + " symbol";
    case STRING:
        return "string";
    case COMMENT:
        return "comment";
    default:
        return "unknown";
    }
}