#ifndef HIGH_PRECISION_CALCULATOR_H
#define HIGH_PRECISION_CALCULATOR_H

#pragma once
#include <gmpxx.h>
#include <vector>
#include <string>
#include <stack>
#include <token.h>
#include <ArithmeticOperations.h>
#include <MathUtils.h>
#include <InputTokenizer.h>


class HighPrecisionCalculator {
public:
    static const std::vector<mpf_class> calculate(const std::string& input);
private:
    static const std::vector<mpf_class> getAllResults(const std::vector<Token>& tokens, size_t l, size_t r);
    static const mpf_class getResult(const std::vector<Token> &tokens, size_t l, size_t r);
};

#endif