#include <iostream>
#include <cmath>
#include <vector>
#include <gmpxx.h>

// Structure to hold partial results of the Binary Splitting
struct PQT {
    mpz_class P, Q, T;
};

// Chudnovsky Constants
const mpz_class A = 13591409;
const mpz_class B = 545140134;
const mpz_class C = 640320;
const mpz_class D = 426880;
const mpz_class E = 10005;
const mpz_class C3_24 = C * C * C / 24;

// Recursive Binary Splitting function
PQT compute_PQT(long n1, long n2) {
    PQT res;
    if (n1 + 1 == n2) {
        // Base case: Compute a single term
        // P = (6n-5)(2n-1)(6n-1)
        res.P = (2 * n2 - 1);
        res.P *= (6 * n2 - 1);
        res.P *= (6 * n2 - 5);
        
        // Q = n^3 * C^3 / 24
        res.Q = n2 * n2;
        res.Q *= n2;
        res.Q *= C3_24;
        
        // T = (A + Bn) * P
        res.T = (A + B * n2) * res.P;
        if (n2 % 2 != 0) res.T = -res.T;
    } else {
        // Recursive case: Divide and conquer
        long mid = (n1 + n2) / 2;
        PQT left = compute_PQT(n1, mid);
        PQT right = compute_PQT(mid, n2);
        
        // Combine results
        res.P = left.P * right.P;
        res.Q = left.Q * right.Q;
        res.T = left.T * right.Q + left.P * right.T;
    }
    return res;
}