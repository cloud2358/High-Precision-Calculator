#include <arithmetic_operations.h>

const std::unordered_map<std::string, size_t> ArithmeticOperations::registry = {
    {"+", 1},
    {"-", 1},
    {"*", 2},
    {"/", 2}
};

const mpf_class ArithmeticOperations::getCalculationResult(const mpf_class& x, const mpf_class& y, char op) {
    if (op == '+') return ArithmeticOperations::add(x, y);
    if (op == '-') return ArithmeticOperations::subtract(x, y);
    if (op == '*') return ArithmeticOperations::multiply(x, y);
    if (op == '/') return ArithmeticOperations::divide(x, y);
    throw std::runtime_error("Error: undefined operation in HighPrecisionCalculator::calculate!");
    return mpf_class(0);
}

const size_t ArithmeticOperations::getPrecedence(const char op) {
    if (op == '+') return 1;
    if (op == '-') return 1;
    if (op == '*') return 2;
    if (op == '/') return 2;
    return 0;
}

const mpf_class ArithmeticOperations::add(const mpf_class &x, const mpf_class &y) {
    return x + y;
}

const mpf_class ArithmeticOperations::subtract(const mpf_class &x, const mpf_class &y) {
    return x - y;
}

const mpf_class ArithmeticOperations::multiply(const mpf_class &x, const mpf_class &y) {
    return x * y;
}

const mpf_class ArithmeticOperations::divide(const mpf_class &x, const mpf_class &y) {
    return x / y;
}

const mpf_class ArithmeticOperations::power(const mpf_class &x, const mpf_class &y) {
    return 0;
}