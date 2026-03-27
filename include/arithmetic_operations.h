#ifndef ARITHMETIC_OPERATIONS_H
#define ARITHMETIC_OPERATIONS_H

#pragma once
#include <gmpxx.h>
#include <functional>
#include <string>
#include <unordered_map>

class ArithmeticOperations {
public:
    static const bool isOperator(const std::string& name);
    static const mpf_class add(const mpf_class& x, const mpf_class& y);
    static const mpf_class subtract(const mpf_class& x, const mpf_class& y);
    static const mpf_class multiply(const mpf_class& x, const mpf_class& y);
    static const mpf_class divide(const mpf_class& x, const mpf_class& y);
    static const mpf_class power(const mpf_class& x, const mpf_class& y);
private:
    static const std::unordered_map<std::string, size_t> registry;
};

#endif