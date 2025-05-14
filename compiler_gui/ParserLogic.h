#pragma once

#include <string>
#include <vector>
#include <stack>
#include <map>
#include <unordered_set>
#include "LexerLogic.h"

struct ParseError {
    std::string message;
    int tokenIndex;
    std::string tokenValue;
    int line;
};

class Parser {
private:
    std::vector<Token> tokens;
    std::stack<std::string> parseStack;
    int current = 0;
    std::vector<ParseError> errors;
    std::unordered_set<std::string> declaredIdentifiers;
    std::string lastNonTerminal;

    Token peek();
    void error(const std::string& msg);
    bool matchTerminal(const std::string& terminal);
    void initializeParseTable();
    std::map<std::string, std::map<std::string, std::vector<std::string>>> parseTable;

public:
    Parser(const std::vector<Token>& tokenList);
    bool parse();
    std::vector<ParseError> getErrors() const;
};