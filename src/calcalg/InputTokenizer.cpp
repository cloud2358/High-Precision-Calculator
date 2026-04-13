#include <InputTokenizer.h>

// Split user input into tokens, throw invalid expression.
const std::vector<Token> InputTokenizer::split(const std::string& input) {
    size_t position = 0;
    std::vector<Token> targetVector;
    bool isSignValid = true;
    while (position < input.size()) {
        Token token = getNextToken(input, position, isSignValid);
        if (token.type == TokenType::End) break;
        if (token.type == TokenType::LeftParen || token.type == TokenType::Comma) isSignValid = true;
        else isSignValid = false;
        targetVector.push_back(token);
    }
    if (!targetVector.empty() && targetVector.back().type == TokenType::Comma) targetVector.pop_back();
    return targetVector;
}

const bool InputTokenizer::check(const std::vector<Token> &tokens, bool detailed_check) {
    bool isValidOp = false;
    int parenCount = 0;
    std::vector<size_t> subTokenSize;
    subTokenSize.push_back(0);
    
    for (size_t i = 0; i < tokens.size(); ++i) {
        Token token = tokens[i];
        if (token.type == TokenType::Number || token.type == TokenType::Variant || token.type == TokenType::Constant) {
            if (isValidOp) {
                if (detailed_check) throw std::runtime_error("Expect a value");
                return false;
            }
            isValidOp = true;
            subTokenSize[parenCount]++;
        }
        else if (token.type == TokenType::Function) {
            if (isValidOp) {
                if (detailed_check) throw std::runtime_error("Expect a value");
                return false;
            }
            isValidOp = false;
            subTokenSize[parenCount]++;
        }
        else if (token.type == TokenType::Operator) {
            if (!isValidOp) {
                if (detailed_check) throw std::runtime_error("Expect a operator");
                return false;  
            }
            isValidOp = false;
            subTokenSize[parenCount]++;
        }
        else if (token.type == TokenType::LeftParen) {   
            if (isValidOp) {
                if (detailed_check) throw std::runtime_error("Expect a value");
                return false;
            }
            subTokenSize.push_back(0); parenCount++;
            isValidOp = false;
        }
        else if (token.type == TokenType::RightParen) {
            if (!isValidOp) {
                if (detailed_check) throw std::runtime_error("Expect a operator");
                return false;
            }
            parenCount--;
            if (parenCount < 0) {
                if (detailed_check) throw std::runtime_error("Parenthesis mismatch");
                return false;
            }
            subTokenSize[parenCount] += 1;
            subTokenSize.pop_back();
            isValidOp = true;
        }
        else if (token.type == TokenType::Comma) {
            if (subTokenSize[parenCount] != 0) {
                if (tokens[i - 1].type == TokenType::Operator) return false;
                if (tokens[i - 1].type == TokenType::Function) return false;
            }
            subTokenSize[parenCount] = 0;
            isValidOp = false;
        }
        else {
            return false;
        }
    }
    if (parenCount != 0) return false;
    if (subTokenSize[0] != 0) {
        if (tokens.back().type == TokenType::Operator) {
            if (detailed_check) throw std::runtime_error("Should end with a value");
            return false;
        }
        if (tokens.back().type == TokenType::Function) {
            if (detailed_check) throw std::runtime_error("Should end with a value");
            return false;
        }
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
        token.type = TokenType::End;
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