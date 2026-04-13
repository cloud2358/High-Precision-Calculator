#ifndef INPUT_TOKENIZER_H
#define INPUT_TOKENIZER_H

#include <vector>
#include <string>
#include <token.h>
#include <stdexcept>
#include <MathUtils.h>

class InputTokenizer {
public:
    static const std::vector<Token> split(const std::string &input);
    static const bool check(const std::vector<Token>& tokens, bool detailed_check = false);
private:
    static const Token getNextToken(const std::string &input, size_t &position, bool isSignValid);
    static const bool isDigit(char ch);
    static const bool isInitial(char ch);
    static const bool isOperator(char ch);
    static const bool isLeftParen(char ch);
    static const bool isRightParen(char ch);
};

#endif