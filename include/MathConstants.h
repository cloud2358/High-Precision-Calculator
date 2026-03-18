#ifndef MATH_CONSTANTS_H
#define MATH_CONSTANTS_H

#include <iostream>
#include <cmath>
#include <vector>
#include <gmpxx.h>

// Provide high precision math constants.
class MathConstants {
public:
    // Compute Pi to a specific number of decimal digits.
    static mpf_class compute_pi(int digits);
    static mpf_class compute_e(int digits);
private:
    // Hold partial results for recursive calculation.
    struct PQT { mpz_class P, Q, T; };

    // Chudnovsky Constants
    static inline const mpz_class A = 13591409;
    static inline const mpz_class B = 545140134;
    static inline const mpz_class C = 640320;
    static inline const mpz_class D = 426880;
    static inline const mpz_class E = 10005;
    static inline const mpz_class C3_div_24 = C * C * C / 24;

    // Compute outcome recursively
    static PQT chudnovsky(mpz_class n1, mpz_class n2);
    static PQT taylor(mpz_class n1, mpz_class n2);
};
#endif