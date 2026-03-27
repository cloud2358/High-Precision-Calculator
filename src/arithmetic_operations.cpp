#include <arithmetic_operations.h>

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

void ArithmeticOperations::setDefaultPrecision() {
    mpf_set_default_prec(256);
}