#include <high_precision_calculator.h>
#include <assert.h>

const mpf_class HighPrecisionCalculator::calculate(const std::string& input) {
    std::vector<Token> tokens = tokenize(input);
    
    std::vector<mpf_class> numbers;
    std::vector<char> ops;
    for (Token token : tokens) {
        if (token.type == TokenType::Number) {
            numbers.push_back((mpf_class)token.value);
        }
        else if (token.type == TokenType::Constant) {
            numbers.push_back(MathConstants::getConstant(token.value));
        }
        else if (token.type == TokenType::Operator) {
            assert(token.value.size() == 1);
            if (token.value == "(") {
                ops.push_back('(');
            }
            else if (token.value == ")") {
                while (!ops.empty() && ops.back() != '(') {
                    mpf_class y = numbers.back(); numbers.pop_back();
                    mpf_class x = numbers.back(); numbers.pop_back();
                    char op = ops.back(); ops.pop_back();
                    numbers.push_back(getCalculationResult(x, y, op));
                }
                if (!ops.empty()) ops.pop_back();
            }
            else {
                char op = token.value[0];
                while (!ops.empty() && getPrecedence(ops.back()) >= getPrecedence(op))  {
                    mpf_class y = numbers.back(); numbers.pop_back();
                    mpf_class x = numbers.back(); numbers.pop_back();
                    numbers.push_back(getCalculationResult(x, y, ops.back()));
                    ops.pop_back();
                }
                ops.push_back(op);
            }
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
    if (position >= inputSize) return false;
    if (isDigit(input[position])) {
        token.type = TokenType::Number;
        while (position < inputSize) {
            if (!isDigit(input[position]) && input[position] != '.') break;
            token.value += input[position]; position++;
        }
    }
    else if (isOperator(input[position])) {
        token.type = TokenType::Operator;
        token.value += input[position]; position++;
    }
    else if (isLetter(input[position])) {
        while (position < inputSize) {
            if (!isLetter(input[position]) && !isDigit(input[position])) break;
            token.value += input[position]; position++;
        }
        if (MathConstants::isConstant(token.value)) token.type = TokenType::Constant;
        else throw std::runtime_error("Variant function working on progress");
    }
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