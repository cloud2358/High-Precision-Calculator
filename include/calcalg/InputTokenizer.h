#ifndef INPUT_TOKENIZER_H
#define INPUT_TOKENIZER_H

#include <vector>
#include <string>
#include <token.h>
#include <stdexcept>
#include <MathUtils.h>

class InputTokenizer {
public:
    static const std::vector<Token> tokenize(const std::string &input);
private:
    static const Token getNextToken(const std::string &input, size_t &position);
    static const bool isNotBlank(char op);
    static const bool isDigit(char op);
    static const bool isInitial(char op);
    static const bool isOperator(char op);
};

#endif