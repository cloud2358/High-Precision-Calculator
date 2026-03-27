#include <high_precision_calculator.h>
#include <assert.h>

const mpf_class HighPrecisionCalculator::calculate(const std::string& input) {
    std::vector<Token> tokens = tokenize(input);
    
    std::vector<mpf_class> numbers;
    std::vector<char> ops;
    for (Token token : tokens) {
        if (token.type == TokenType::Number) {
            numbers.push_back((mpf_class)token.value);
            continue;
        }
        if (token.type == TokenType::Constant) {
            numbers.push_back(MathConstants::getConstant(token.value));
            continue;
        }
        if (token.type == TokenType::Operator) {\
            assert(token.value.size() == 1);
            char op = token.value[0];
            while (ops.size() && getPrecedence(ops.back()) > getPrecedence(op)) {
                mpf_class y = numbers.back();
                numbers.pop_back();
                mpf_class x = numbers.back();
                numbers.pop_back();
                numbers.push_back(getCalculationResult(x, y, ops.back()));
                ops.pop_back();
            }
            ops.push_back(op);
        }

    }
    while (ops.size()) {
        mpf_class y = numbers.back();
        numbers.pop_back();
        mpf_class x = numbers.back();
        numbers.pop_back();
        numbers.push_back(getCalculationResult(x, y, ops.back()));
        ops.pop_back();
    }
    return numbers.back();
}

const std::vector<HighPrecisionCalculator::Token> HighPrecisionCalculator::tokenize(const std::string& input) {
    size_t position = 0;
    std::vector<HighPrecisionCalculator::Token> targetVector;
    while (position < input.size()) {
        HighPrecisionCalculator::Token token;
        bool flag = getNextToken(input, position, token);
        if (flag) targetVector.push_back(token);
    }
    return targetVector;
}

const bool HighPrecisionCalculator::getNextToken(const std::string& input, size_t& position, HighPrecisionCalculator::Token& token) {
    if (position < 0) throw std::runtime_error("Error: negative position in HighPrecisionCalculator::getNextToken!");

    size_t inputSize = input.size();
    while (position < inputSize && !isValid(input[position])) position++;
    while (position < inputSize && isValid(input[position])) {
        token.value += input[position++];
    }  
    
    if (token.value.empty()) return false;
    token.type = getTokenType(token.value);
    return true;
}

const HighPrecisionCalculator::TokenType HighPrecisionCalculator::getTokenType(const std::string& name) {
    bool isConst = MathConstants::isConstant(name);
    if (isConst) return TokenType::Constant;
    bool isOp = isOperator(name[0]);
    if (isOp) return TokenType::Operator;
    bool isNum = true;
    for (auto ch : name) {
        if (!(isdigit(ch) || ch == '.')) isNum = false;
    }
    if (isNum) return TokenType::Number;
    return TokenType::Variant;
}

const mpf_class HighPrecisionCalculator::getCalculationResult(const mpf_class& x, const mpf_class& y, char op) {
    if (op == '+') return ArithmeticOperations::add(x, y);
    if (op == '-') return ArithmeticOperations::subtract(x, y);
    if (op == '*') return ArithmeticOperations::multiply(x, y);
    if (op == '/') return ArithmeticOperations::divide(x, y);
    throw std::runtime_error("Error: undefined operation in HighPrecisionCalculator::calculate!");
}

const int HighPrecisionCalculator::getPrecedence(char op) {
    if (op == '+') return 1;
    if (op == '-') return 1;
    if (op == '*') return 2;
    if (op == '/') return 2;
    return 0;
}

const bool HighPrecisionCalculator::isValid(char op) {
    if (op == ' ') return false;
    return true;
}

const bool HighPrecisionCalculator::isDigit(char op) {
    return op >= '0' && op <= '9';
}

const bool HighPrecisionCalculator::isLetter(char op) {
    return op >= 'A' && op <= 'Z' || op >= 'a' && op <= 'z';
}

const bool HighPrecisionCalculator::isOperator(char op) {
    std::vector<char> stdops = {'+', '-', '*', '/', '(', ')'};
    for (char stdop : stdops) {
        if (op == stdop) return true;
    }
    return false;
}