#ifndef MATH_CONSTANTS_H
#define MATH_CONSTANTS_H

#pragma once
#include <gmpxx.h>
#include <functional>
#include <vector>
#include <string>
#include <unordered_map>
#include <settings.h>

// Provide high precision math constants.
class MathUtils {
public:
    static const bool isMathConst(const std::string& name);
    static const bool isMathFunc(const std::string& name);
    static const mpf_class getMathConst(const std::string &name);
    static const mpf_class getMathFunc(const std::string &name, const std::vector<mpf_class> &arguments);

private:
    using MathConst = std::function<mpf_class(size_t)>;
    using MathFunc = std::function<mpf_class(std::vector<mpf_class>, size_t)>;
    static const std::unordered_map<std::string, MathConst> ConstReg;
    static const std::unordered_map<std::string, MathFunc> FuncReg;
    static const mpf_class getConstantPi(size_t precision);
    static const mpf_class getConstantE(size_t precision);
    static const mpf_class getSin(const std::vector<mpf_class> &arguments, size_t precision);
    static const mpf_class getCos(const std::vector<mpf_class> &arguments, size_t precision);
    struct PQT { mpz_class P, Q, T; };
    static PQT Chudnovsky(mpz_class n1, mpz_class n2);
    static PQT Taylor(mpz_class n1, mpz_class n2);
    
};
#endif