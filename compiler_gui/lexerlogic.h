#pragma once
#include <string>
#include <vector>

enum TokenType
{
    RESERVED_WORD,
    IDENTIFIER,
    NUMBER,
    COMPARISON_OP,
    ARITHMETIC_OP,
    ASSIGN_OP,
    SYMBOL,
    STRING,
    COMMENT,
    UNKNOWN
};

struct Token
{
    std::string lexeme;
    TokenType type;
    int line;
    Token(std::string lex, TokenType t, int ln)
        : lexeme(lex), type(t), line(ln) {
    }
};

std::vector<Token> tokenize(const std::string& input);
std::string tokenTypeToString(TokenType type, const std::string& lexeme);