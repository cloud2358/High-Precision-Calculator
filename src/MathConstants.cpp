#include <MathConstants.h>

mpf_class MathConstants::compute_pi(int digits) {
    // 1 iteration gives ~14.18 digits
    long N = digits / 14 + 1;
    unsigned long prec_bits = digits * 3.321928 + 64;
    mpf_set_default_prec(prec_bits);
    PQT res = chudnovsky(0, N);
    mpf_class pi;
    mpf_class q_f(res.Q);
    mpf_class t_f(res.T);
    pi = D * sqrt((mpf_class)E) * q_f;
    pi /= (A * q_f + t_f);
    return pi;
}

mpf_class MathConstants::compute_e(int digits) {
    long N = digits;
    unsigned long prec_bits = digits * 3.321928 + 64;
    mpf_set_default_prec(prec_bits);
    PQT res = taylor(0, N);
    mpf_class e;
    mpf_class q_f(res.Q);
    mpf_class t_f(res.T);
    e = t_f / q_f;
    e += 1;
    return e;
}

MathConstants::PQT MathConstants::chudnovsky(mpz_class n1, mpz_class n2) {
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
        PQT left = chudnovsky(n1, mid);
        PQT right = chudnovsky(mid, n2);
        res.P = left.P * right.P;
        res.Q = left.Q * right.Q;
        res.T = left.T * right.Q + left.P * right.T;
    }
    return res;
}

MathConstants::PQT MathConstants::taylor(mpz_class n1, mpz_class n2) {
    PQT res;
    if (n1 >= n2) throw std::runtime_error("Error: invalid range in compute_PQT");
    else if (n1 + 1 == n2) {
        res.P = 1;
        res.Q = n2;
        res.T = 1;
    }
    else {
        mpz_class mid = (n1 + n2) / 2;
        PQT left = taylor(n1, mid);
        PQT right = taylor(mid, n2);
        res.P = 1;
        res.Q = left.Q * right.Q;
        res.T = left.T * right.Q + right.T;
    }
    return res;
}