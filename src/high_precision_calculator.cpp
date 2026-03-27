#include <high_precision_calculator.h>

#include <iostream>
const mpf_class HighPrecisionCalculator::calculate(const std::string& input) {
    std::vector<Token> tokens = tokenize(input);
    
    std::vector<mpf_class> numbers;
    std::vector<char> ops;
    for (Token token : tokens) {
        if (token.type) {
            numbers.push_back((mpf_class)token.value);
            continue;
        }
        if (token.value.size() != 1) throw std::runtime_error("Error: token(operators) size should be 1 at HighPrecisionCalculator::evaluate!");
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
        if (!token.value.empty()) throw std::runtime_error("Error: Token size should be 0 at HighPrecisionCalculator::tokenize!");
        bool flag = getNextToken(input, position, token);
        if (flag) targetVector.push_back(token);
    }
    return targetVector;
}

const bool HighPrecisionCalculator::getNextToken(const std::string& input, size_t& position, HighPrecisionCalculator::Token& token) {
    if (position < 0) throw std::runtime_error("Error: negative position in HighPrecisionCalculator::getNextToken!");
    size_t inputSize = input.size();
    while (position < inputSize && !isValid(input[position])) position++;
    if (position >= inputSize) return false;
    while (position < inputSize && isNum(input[position])) token.value += input[position++];
    if (!token.value.empty()) token.type = true;
    else token.type = false, token.value += input[position++];
    return true;
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

const bool HighPrecisionCalculator::isNum(char op) {
    return op >= '0' && op <= '9';
}