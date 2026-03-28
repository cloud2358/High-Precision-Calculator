#ifndef INPUT_TOKENIZER_H
#define INPUT_TOKENIZER_H

#include <vector>
#include <string>
#include <token.h>
#include <stdexcept>

class InputTokenizer {
public:
    static const std::vector<Token> tokenize(const std::string &input);
private:
    static const Token getNextToken(const std::string &input, size_t &position);
    static const bool isValid(char op);
    static const bool isDigit(char op);
    static const bool isLetter(char op);
    static const bool isOperator(char op);
};

#endif