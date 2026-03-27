#include <math_constants.h>

const std::unordered_map<std::string, MathConstants::ConstantFunc> MathConstants::registry = {
    {"pi", MathConstants::computePi},
    {"e", MathConstants::computeE}
};

const bool MathConstants::isConstant(const std::string& name) {
    return registry.find(name) != registry.end();
}

const mpf_class MathConstants::getConstant(const std::string& name) {
    auto it = registry.find(name);
    if (it != registry.end()) {
        return it->second(256);
    }
    return 0;
}

const mpf_class MathConstants::computePi(long long digits) {
    const mpz_class A = 13591409;
    const mpz_class D = 426880;
    const mpz_class E = 10005;

    long N = digits / 14 + 1;
    unsigned long prec_bits = digits * 3.321928 + 64;
    mpf_set_default_prec(prec_bits);
    PQT res = Chudnovsky(0, N);
    mpf_class pi;
    mpf_class q_f(res.Q);
    mpf_class t_f(res.T);
    pi = D * sqrt((mpf_class)E) * q_f;
    pi /= (A * q_f + t_f);
    return pi;
}

const mpf_class MathConstants::computeE(long long digits) {
    long N = digits;
    unsigned long prec_bits = digits * 3.321928 + 64;
    mpf_set_default_prec(prec_bits);
    PQT res = Taylor(0, N);
    mpf_class e;
    mpf_class q_f(res.Q);
    mpf_class t_f(res.T);
    e = t_f / q_f;
    e += 1;
    return e;
}

MathConstants::PQT MathConstants::Chudnovsky(mpz_class n1, mpz_class n2) {
    const mpz_class A = 13591409;
    const mpz_class B = 545140134;
    const mpz_class C = 640320;
    const mpz_class C3_div_24 = C * C * C / 24;

    PQT res; 
    if (n1 >= n2) throw std::runtime_error("Error: invalid range in chudnovsky");
    else if (n1 + 1 == n2) {
        res.P = (2 * n2 - 1);
        res.P *= (6 * n2 - 1);
        res.P *= (6 * n2 - 5);
        res.Q = n2 * n2;
        res.Q *= n2;
        res.Q *= C3_div_24;
        res.T = (A + B * n2) * res.P;
        if (n2 % 2 != 0) res.T = -res.T;
    }
    else {
        mpz_class mid = (n1 + n2) / 2;
        PQT left = Chudnovsky(n1, mid);
        PQT right = Chudnovsky(mid, n2);
        res.P = left.P * right.P;
        res.Q = left.Q * right.Q;
        res.T = left.T * right.Q + left.P * right.T;
    }
    return res;
}

MathConstants::PQT MathConstants::Taylor(mpz_class n1, mpz_class n2) {
    PQT res;
    if (n1 >= n2) throw std::runtime_error("Error: invalid range in compute_PQT");
    else if (n1 + 1 == n2) {
        res.P = 1;
        res.Q = n2;
        res.T = 1;
    }
    else {
        mpz_class mid = (n1 + n2) / 2;
        PQT left = Taylor(n1, mid);
        PQT right = Taylor(mid, n2);
        res.P = 1;
        res.Q = left.Q * right.Q;
        res.T = left.T * right.Q + right.T;
    }
    return res;
}