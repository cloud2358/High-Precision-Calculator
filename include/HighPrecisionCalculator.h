#ifndef HIGH_PRECISION_CALCULATOR_H
#define HIGH_PRECISION_CALCULATOR_H

#pragma once
#include <gmpxx.h>
#include <vector>
#include <string>
#include <stack>
#include <token.h>
#include <ArithmeticOperations.h>
#include <MathConstants.h>
#include <InputTokenizer.h>


class HighPrecisionCalculator {
public:
    static const mpf_class calculate(const std::string& input);

};

#endif