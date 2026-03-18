#include "picalg.h"

int main() {
    long digits = 1000; // Change this to 10000 or more!
    
    // 1 iteration gives ~14.18 digits
    long N = digits / 14 + 1;
    unsigned long prec_bits = digits * 3.321928 + 64; 
    mpf_set_default_prec(prec_bits);

    std::cout << "Calculating " << digits << " digits of Pi..." << std::endl;

    // 1. Run Binary Splitting to get T and Q
    PQT res = compute_PQT(0, N);

    // 2. Final calculation: Pi = (D * sqrt(E) * Q) / (A * Q + T)
    mpf_class pi;
    mpf_class q_f(res.Q);
    mpf_class t_f(res.T);
    
    pi = D * sqrt((mpf_class)E) * q_f;
    pi /= (A * q_f + t_f);

    std::cout.precision(digits);
    std::cout << pi << std::endl;

    return 0;
}