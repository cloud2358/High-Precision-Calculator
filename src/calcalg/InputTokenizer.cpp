#include <InputTokenizer.h>

// Split user input into tokens, throw invalid expression.
const std::vector<Token> InputTokenizer::split(const std::string& input) {
    size_t position = 0;
    std::vector<Token> targetVector;
    bool isSignValid = true;
    while (position < input.size()) {
        Token token = getNextToken(input, position, isSignValid);
        if (token.type == TokenType::Fullstop) break;
        if (token.type == TokenType::LeftParen) isSignValid = true;
        else isSignValid = false;
        targetVector.push_back(token);
    }
    return targetVector;
}

const bool InputTokenizer::check(const std::vector<Token> &tokens) {
    bool isValidOp = false;
    int parenCount = 0;
    for (size_t i = 0; i < tokens.size(); ++i) {
        Token token = tokens[i];
        if (token.type == TokenType::Number || token.type == TokenType::Variant || token.type == TokenType::Constant) {
            if (isValidOp) return false;
            isValidOp = true;
        }
        else if (token.type == TokenType::Function) {
            if (isValidOp) return false;
            isValidOp = false; // function must be followed by '('
        }
        else if (token.type == TokenType::Operator) {
            if (!isValidOp) return false;  
            isValidOp = false;
        }
        else if (token.type == TokenType::LeftParen) {   
            if (isValidOp) return false;
            parenCount++;
            isValidOp = false;
        }
        else if (token.type == TokenType::RightParen) {
            if (!isValidOp) return false;
            parenCount--;
            if (parenCount < 0) return false;
            isValidOp = true;
        }
        else if (token.type == TokenType::Fullstop) {
        }
        else {
            return false;
        }
    }
    if (parenCount != 0) return false;
    if (!tokens.empty()) {
        if (tokens.back().type == TokenType::Operator) return false;
        if (tokens.back().type == TokenType::Function) return false;
    }
    return true;
}

const Token InputTokenizer::getNextToken(const std::string &input, size_t &position, bool isSignValid) {
    size_t inputSize = input.size();
    if (position < 0 || position >= inputSize) {
        throw std::runtime_error("Error: invalid position in InputTokenizer::getNextToken!");
    }

    Token token;
    while (position < inputSize && input[position] == ' ') position++;

    if (position >= inputSize) {
        token.type = TokenType::Fullstop;
    }
    else if (isDigit(input[position]) || isSignValid && (input[position] == '+' || input[position] == '-')) {
        token.type = TokenType::Number;
        if (isSignValid && (input[position] == '+' || input[position] == '-')) {
            token.name += input[position]; position++;
            if (position >= inputSize || !isDigit(input[position])) throw std::runtime_error("Invalid input");
        }
        bool isFloat = false;
        while (position < inputSize) {
            if (isDigit(input[position])) {
                token.name += input[position]; position++;
            }
            else if (input[position] == '.') {
                if (isFloat) {
                    throw std::runtime_error("Invalid input");
                }
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
    else if (isLeftParen(input[position])) {
        token.type = TokenType::LeftParen;
        token.name += input[position]; position++;
    }
    else if (isRightParen(input[position])) {
        token.type = TokenType::RightParen;
        token.name += input[position]; position++;
    }
    else if (input[position] == ',') {
        token.type = TokenType::Comma;
        token.name += input[position]; position++;
    }
    else if (isInitial(input[position])) {
        while (position < inputSize) {
            if (!isInitial(input[position])) break;
            token.name += input[position]; position++;
        }
        if (MathUtils::isMathConst(token.name)) {
            token.type = TokenType::Constant;
        }
        else if (MathUtils::isMathFunc(token.name)) {
            token.type = TokenType::Function;
        }
        else token.type = TokenType::Variant;
    }
    else throw std::runtime_error("Invalid input");
    return token;
}

const bool InputTokenizer::isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

const bool InputTokenizer::isInitial(char ch) {
    return ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z' || ch == '_';
}

const bool InputTokenizer::isOperator(char ch) {
    std::vector<char> ops = {'+', '-', '*', '/'};
    for (char op : ops) {
        if (ch == op) return true;
    }
    return false;
}

const bool InputTokenizer::isLeftParen(char ch) {
    for (char op : {'('}) {
        if (ch == op) return true;
    }
    return false;
}

const bool InputTokenizer::isRightParen(char ch) {
    for (char op : {')'}) {
        if (ch == op) return true;
    }
    return false;
}