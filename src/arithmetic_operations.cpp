#include <arithmetic_operations.h>

const std::unordered_map<std::string, size_t> ArithmeticOperations::registry = {
    {"+", 1},
    {"-", 1},
    {"*", 2},
    {"/", 2}
};

const bool ArithmeticOperations::isOperator(const std::string& name) {
    return registry.find(name) != registry.end();
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