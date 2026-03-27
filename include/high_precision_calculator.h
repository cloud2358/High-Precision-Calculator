#ifndef HIGH_PRECISION_CALCULATOR_H
#define HIGH_PRECISION_CALCULATOR_H

#pragma once
#include <gmpxx.h>
#include <vector>
#include <string>
#include <stack>
#include <arithmetic_operations.h>
#include <math_constants.h>

class HighPrecisionCalculator {
public:
    static const mpf_class calculate(const std::string& input);
private:
    enum class TokenType {
        Number,
        Operator,
        Constant,
        Variant
    };
    struct Token {
        TokenType type;
        std::string value;
    };
    static const std::vector<Token> tokenize(const std::string& input);
    static const bool getNextToken(const std::string& input, size_t& position, Token& token);
    static const TokenType getTokenType(const std::string& name);
    static const mpf_class getCalculationResult(const mpf_class& x, const mpf_class& y, char op);
    static const int getPrecedence(char op);
    static const bool isValid(char op);
    static const bool isDigit(char op);
    static const bool isLetter(char op);
    static const bool isOperator(char op);
};

#endif