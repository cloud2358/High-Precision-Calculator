#include <InputTokenizer.h>

const std::vector<Token> InputTokenizer::tokenize(const std::string& input) {
    size_t position = 0;
    std::vector<Token> targetVector;
    while (position < input.size()) {
        Token token = getNextToken(input, position);
        targetVector.push_back(token);
    }
    return targetVector;
}

const Token InputTokenizer::getNextToken(const std::string& input, size_t& position) {
    size_t inputSize = input.size();
    if (position < 0 || position >= inputSize) {
        throw std::runtime_error("Error: invalid position in InputTokenizer::getNextToken!");
    }

    Token token;
    while (position < inputSize && !isNotBlank(input[position])) position++;

    if (position >= inputSize) {
        token.type = TokenType::Fullstop;
    }
    else if (isDigit(input[position])) {
        token.type = TokenType::Number;
        bool isFloat = false;
        while (position < inputSize) {
            if (isDigit(input[position])) {
                token.name += input[position]; position++;
            }
            else if (!isFloat && input[position] == '.') {
                token.name += input[position]; position++;
                isFloat = true;
            }
            else break;
        }
    }
    else if (isOperator(input[position])) {
        token.type = TokenType::Operator;
        token.name += input[position]; position++;
    }
    else if (isInitial(input[position])) {
        while (position < inputSize) {
            if (!isInitial(input[position]) && !isDigit(input[position])) break;
            token.name += input[position]; position++;
        }
        if (MathUtils::isMathFunc(token.name)) {
            token.type = TokenType::Function;
        }
        else token.type = TokenType::Variant;
    }
    return token;
}

const bool InputTokenizer::isNotBlank(char op) {
    if (op == ' ') return false;
    return true;
}

const bool InputTokenizer::isDigit(char op) {
    return op >= '0' && op <= '9';
}

const bool InputTokenizer::isInitial(char op) {
    return op >= 'A' && op <= 'Z' || op >= 'a' && op <= 'z' || op == '_';
}

const bool InputTokenizer::isOperator(char op) {
    std::vector<char> stdops = {'+', '-', '*', '/', '(', ')'};
    for (char stdop : stdops) {
        if (op == stdop) return true;
    }
    return false;
}