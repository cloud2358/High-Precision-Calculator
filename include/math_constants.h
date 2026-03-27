#ifndef MATH_CONSTANTS_H
#define MATH_CONSTANTS_H

#pragma once
#include <gmpxx.h>
#include <functional>
#include <string>
#include <unordered_map>

// Provide high precision math constants.
class MathConstants {
public:
    

    static const bool isConstant(const std::string& name);
    static const mpf_class getConstant(const std::string& name);

private:
    
    using ConstantFunc = std::function<mpf_class(long long)>;
    static const std::unordered_map<std::string, ConstantFunc> registry;
    static const mpf_class computePi(long long digits);
    static const mpf_class computeE(long long digits);
    struct PQT { mpz_class P, Q, T; };
    static PQT Chudnovsky(mpz_class n1, mpz_class n2);
    static PQT Taylor(mpz_class n1, mpz_class n2);
    
};
#endif