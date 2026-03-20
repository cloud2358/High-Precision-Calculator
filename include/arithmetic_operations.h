#ifndef ARITHMETIC_OPERATIONS_H
#define ARITHMETIC_OPERATIONS_H

#pragma once
#include <gmpxx.h>

class ArithmeticOperations {
public:
    static const mpf_class add(const mpf_class& x, const mpf_class& y);
    static const mpf_class subtract(const mpf_class& x, const mpf_class& y);
    static const mpf_class multiply(const mpf_class& x, const mpf_class& y);
    static const mpf_class divide(const mpf_class& x, const mpf_class& y);
    static const mpf_class power(const mpf_class& x, const mpf_class& y);

    static void SetDefaultPresition(size_t n);
private:

};

#endif