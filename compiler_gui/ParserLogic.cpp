#include "ParserLogic.h"
#include <iostream>
#include <cctype>

Parser::Parser(const std::vector<Token>& tokenList) : tokens(tokenList), current(0) {
    errors.clear();
    initializeParseTable();
}

Token Parser::peek() {
    while (current < tokens.size() && tokens[current].type == COMMENT)
        current++;
    int lastLine = tokens.empty() ? 1 : tokens.back().line;
    return current < tokens.size() ? tokens[current] : Token("", UNKNOWN, lastLine + 1);
}

bool Parser::matchTerminal(const std::string& terminal) {
    Token token = peek();
    if (token.lexeme == terminal ||
        (terminal == "IDENTIFIER" && token.type == IDENTIFIER) ||
        (terminal == "NUMBER" && token.type == NUMBER) ||
        (terminal == "STRING" && token.type == STRING) ||
        (terminal == "$" && current >= tokens.size())) {

        // ############### Check identifier declaration ###############
        if (terminal == "IDENTIFIER" && token.type == IDENTIFIER) {
            if (lastNonTerminal == "<assign_stmt>" || lastNonTerminal == "<read_stmt>" || lastNonTerminal == "<factor>") {
                if (declaredIdentifiers.find(token.lexeme) == declaredIdentifiers.end()) {
                    error("Undeclared identifier used: '" + token.lexeme + "'");
                }
            }
            else if (lastNonTerminal == "<declare_stmt>") {
                declaredIdentifiers.insert(token.lexeme);
            }
        }

        current++;
        return true;
    }
    return false;
}

void Parser::error(const std::string& msg) {
    ParseError err;
    err.message = msg;
    err.tokenIndex = current;
    err.tokenValue = peek().lexeme;
    err.line = peek().line;
    errors.push_back(err);
}

void Parser::initializeParseTable() {
    using P = std::vector<std::string>;

    // <program>
    for (const auto& k : { "if", "repeat", "IDENTIFIER", "read", "write", "int" })
        parseTable["<program>"][k] = { "<stmt_list>" };
    parseTable["<program>"]["synch"] = { "$" };

    // <stmt_list>
    for (const auto& k : { "if", "repeat", "IDENTIFIER", "read", "write", "int" })
        parseTable["<stmt_list>"][k] = { "<stmt>", "<stmt_list_tail>" };
    for (const auto& k : { "$", "end", "until" })
        parseTable["<stmt_list>"]["synch"].push_back(k);

    // <stmt_list_tail>
    for (const auto& k : { "if", "repeat", "IDENTIFIER", "read", "write", "int" })
        parseTable["<stmt_list_tail>"][k] = { "<stmt>", "<stmt_list_tail>" };
    for (const auto& k : { "$", "else", "end", "until" })
        parseTable["<stmt_list_tail>"][k] = { "ε" };

    // <stmt>
    parseTable["<stmt>"]["if"] = { "<if_stmt>" };
    parseTable["<stmt>"]["repeat"] = { "<stmt_tail>", ";" };
    parseTable["<stmt>"]["IDENTIFIER"] = { "<stmt_tail>", ";" };
    parseTable["<stmt>"]["read"] = { "<stmt_tail>", ";" };
    parseTable["<stmt>"]["write"] = { "<stmt_tail>", ";" };
    parseTable["<stmt>"]["int"] = { "<stmt_tail>", ";" };
    for (const auto& k : { "$", "else", "end", "until" })
        parseTable["<stmt>"]["synch"].push_back(k);

    parseTable["<stmt_tail>"]["repeat"] = { "<repeat_stmt>" };
    parseTable["<stmt_tail>"]["IDENTIFIER"] = { "<assign_stmt>" };
    parseTable["<stmt_tail>"]["read"] = { "<read_stmt>" };
    parseTable["<stmt_tail>"]["write"] = { "<write_stmt>" };
    parseTable["<stmt_tail>"]["int"] = { "<declare_stmt>" };
    parseTable["<stmt_tail>"]["synch"].push_back(";");

    parseTable["<if_stmt>"]["if"] = { "if", "<exp>", "then", "<stmt_list_tail>", "<else_part>", "end" };
    for (const auto& k : { "repeat", "IDENTIFIER", "read", "write", "int", "else", "end", "until", "$" })
        parseTable["<if_stmt>"]["synch"].push_back(k);

    parseTable["<else_part>"]["else"] = { "else", "<stmt_list>" };
    parseTable["<else_part>"]["end"] = { "ε" };

    parseTable["<repeat_stmt>"]["repeat"] = { "repeat", "<stmt_list>", "until", "<exp>" };
    parseTable["<repeat_stmt>"]["synch"].push_back(";");

    parseTable["<assign_stmt>"]["IDENTIFIER"] = { "IDENTIFIER", ":=", "<exp>" };
    parseTable["<assign_stmt>"]["synch"].push_back(";");

    parseTable["<read_stmt>"]["read"] = { "read", "IDENTIFIER" };
    parseTable["<read_stmt>"]["synch"].push_back(";");

    parseTable["<write_stmt>"]["write"] = { "write", "<write_stmt_tail>" };
    parseTable["<write_stmt>"]["synch"].push_back(";");

    parseTable["<write_stmt_tail>"]["STRING"] = { "STRING" };
    for (const auto& k : { "(", "IDENTIFIER", "NUMBER" })
        parseTable["<write_stmt_tail>"][k] = { "<exp>" };
    parseTable["<write_stmt_tail>"]["synch"].push_back(";");

    parseTable["<declare_stmt>"]["int"] = { "int", "IDENTIFIER" };
    parseTable["<declare_stmt>"]["synch"].push_back(";");

    for (const auto& k : { "(", "IDENTIFIER", "NUMBER" })
        parseTable["<exp>"][k] = { "<simple_exp>", "<exp_tail>" };
    for (const auto& k : { ";", "then", ")" })
        parseTable["<exp>"]["synch"].push_back(k);

    for (const auto& k : { ";", "then", ")" })
        parseTable["<exp_tail>"][k] = { "ε" };
    parseTable["<exp_tail>"]["="] = { "<comparison_op>", "<simple_exp>" };
    parseTable["<exp_tail>"]["<"] = { "<comparison_op>", "<simple_exp>" };

    parseTable["<comparison_op>"]["="] = { "=" };
    parseTable["<comparison_op>"]["<"] = { "<" };
    for (const auto& k : { "(", "IDENTIFIER", "NUMBER" })
        parseTable["<comparison_op>>"]["synch"].push_back(k);

    for (const auto& k : { "(", "IDENTIFIER", "NUMBER" })
        parseTable["<simple_exp>"][k] = { "<term>", "<add_op_term_list>" };
    for (const auto& k : { "<", "=", ")", ";", "then" })
        parseTable["<simple_exp>"]["synch"].push_back(k);

    parseTable["<add_op_term_list>"]["+"] = { "<add_op>", "<term>", "<add_op_term_list>" };
    parseTable["<add_op_term_list>"]["-"] = { "<add_op>", "<term>", "<add_op_term_list>" };
    for (const auto& k : { ")", ";", "then", "=", "<" })
        parseTable["<add_op_term_list>"][k] = { "ε" };

    parseTable["<add_op>"]["+"] = { "+" };
    parseTable["<add_op>"]["-"] = { "-" };
    for (const auto& k : { "(", "IDENTIFIER", "NUMBER" })
        parseTable["<add_op>"]["synch"].push_back(k);

    for (const auto& k : { "(", "IDENTIFIER", "NUMBER" })
        parseTable["<term>"][k] = { "<factor>", "<mul_op_factor_list>" };
    for (const auto& k : { "then", ";", ")", "=", "<", "+", "-" })
        parseTable["<term>"]["synch"].push_back(k);

    parseTable["<mul_op_factor_list>"]["*"] = { "<mul_op>", "<factor>", "<mul_op_factor_list>" };
    parseTable["<mul_op_factor_list>"]["/"] = { "<mul_op>", "<factor>", "<mul_op_factor_list>" };
    for (const auto& k : { ")", ";", "then", "+", "-", "=", "<" })
        parseTable["<mul_op_factor_list>"][k] = { "ε" };

    parseTable["<mul_op>"]["*"] = { "*" };
    parseTable["<mul_op>"]["/"] = { "/" };
    for (const auto& k : { "(", "IDENTIFIER", "NUMBER" })
        parseTable["<mul_op>"]["synch"].push_back(k);

    parseTable["<factor>"]["("] = { "(", "<exp>", ")" };
    parseTable["<factor>"]["NUMBER"] = { "NUMBER" };
    parseTable["<factor>"]["IDENTIFIER"] = { "IDENTIFIER" };
    for (const auto& k : { "then", ";", ")", "=", "<", "+", "-", "*", "/" })
        parseTable["<factor>"]["synch"].push_back(k);
}

bool Parser::parse() {
    parseStack.push("$");
    parseStack.push("<program>");

    while (!parseStack.empty()) {
        std::string top = parseStack.top();
        parseStack.pop();

        Token token = peek();

        std::string tokenKey;
        if (token.lexeme.empty()) {
            tokenKey = "$";
        }
        else if (token.lexeme == "if" || token.lexeme == "repeat" || token.lexeme == "read" ||
            token.lexeme == "write" || token.lexeme == "int" || token.lexeme == "then" ||
            token.lexeme == "else" || token.lexeme == "end" || token.lexeme == "until" ||
            token.lexeme == "+" || token.lexeme == "-" || token.lexeme == "*" ||
            token.lexeme == "/" || token.lexeme == "=" || token.lexeme == "<" ||
            token.lexeme == "(" || token.lexeme == ")" || token.lexeme == ";" ||
            token.lexeme == ":=") {
            tokenKey = token.lexeme;
        }
        else if (!token.lexeme.empty() && token.lexeme[0] == '"') {
            tokenKey = "STRING";
        }
        else if (!token.lexeme.empty() && isdigit(token.lexeme[0])) {
            tokenKey = "NUMBER";
        }
        else if (!token.lexeme.empty() && isalpha(token.lexeme[0])) {
            tokenKey = "IDENTIFIER";
        }
        else {
            tokenKey = token.lexeme;
        }

        if (top == "$" && tokenKey == "$")
            return errors.empty();

        bool isNonTerminal = top.size() >= 3 && top.front() == '<' && top.back() == '>';
        if (!isNonTerminal) {
            if (!matchTerminal(top)) {
                error("Expected terminal: " + top);
            }
        }
        else {
            lastNonTerminal = top;
            if (parseTable[top].count(tokenKey)) {
                const auto& production = parseTable[top][tokenKey];
                for (auto it = production.rbegin(); it != production.rend(); ++it)
                    if (*it != "ε") parseStack.push(*it);
            }
            else if (parseTable[top].count("synch")) {
                error("Synchronization error: skipping non-terminal " + top);
            }
            else {
                error("Unexpected token '" + token.lexeme + "' for non-terminal " + top);
                current++;
            }
        }
    }

    return current >= tokens.size() && errors.empty();
}

std::vector<ParseError> Parser::getErrors() const {
    return errors;
}