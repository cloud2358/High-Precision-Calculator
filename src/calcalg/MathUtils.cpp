#include <MathUtils.h>

const std::unordered_map<std::string, MathUtils::MathConst> MathUtils::ConstReg = {
    {"pi", getConstantPi},
    {"e", getConstantE}
};

const std::unordered_map<std::string, MathUtils::MathFunc> MathUtils::FuncReg = {
    {"sin", getSin},
    {"cos", getCos}
};
const bool MathUtils::isMathConst(const std::string& name) {
    return ConstReg.find(name) != ConstReg.end();
}
const bool MathUtils::isMathFunc(const std::string& name) {
    return FuncReg.find(name) != FuncReg.end();
}

const mpf_class MathUtils::getMathConst(const std::string& name) {
    auto it =ConstReg.find(name);
    if (it != ConstReg.end()) {
        return it->second(DEFAULT_PRECISION);
    }
    return 0;
}

const mpf_class MathUtils::getMathFunc(const std::string& name, const std::vector<mpf_class>& arguments) {
    auto it = FuncReg.find(name);
    if (it != FuncReg.end()) {
        return it->second(arguments, DEFAULT_PRECISION);
    }
    throw std::runtime_error("Function not found");
    return 0;
}

// precision = 10 base precise digits count
const mpf_class MathUtils::getConstantPi(size_t precision) {
    const mpz_class A = 13591409;
    const mpz_class D = 426880;
    const mpz_class E = 10005;

    unsigned int iter_num = precision / 14 + 1;
    unsigned int prec_bits = precision * 3.321928 + 64;
    mpf_set_default_prec(prec_bits);
    PQT res = Chudnovsky(0, iter_num);
    mpf_class pi;
    mpf_class q_f(res.Q);
    mpf_class t_f(res.T);
    pi = D * sqrt((mpf_class)E) * q_f;
    pi /= (A * q_f + t_f);
    return pi;
}

const mpf_class MathUtils::getConstantE(size_t precision) {
    unsigned int N = precision;
    unsigned int prec_bits = precision * 3.321928 + 64;
    mpf_set_default_prec(prec_bits);
    PQT res = Taylor(0, N);
    mpf_class e;
    mpf_class q_f(res.Q);
    mpf_class t_f(res.T);
    e = t_f / q_f;
    e += 1;
    return e;
}

const mpf_class MathUtils::getSin(const std::vector<mpf_class> &arguments, size_t precision) {
    if (arguments.size() != 1) throw std::runtime_error("Function 'sin' should have 1 argument");
    mpf_class x = arguments[0];
    unsigned int iter_num = precision;
    unsigned int prec_bits = precision * 3.321928 + 64;
    mpf_set_default_prec(prec_bits);
    mpf_class sin_x = 0;
    mpf_class term = x;
    mpf_class x2 = x * x;
    mpf_class epsilon = mpf_class(1);
    for (size_t i = 0; i <= precision; ++i) epsilon /= 10;
    for (size_t k = 0; k < iter_num; ++k) {
        sin_x += term;
        mpf_class denom(static_cast<unsigned long>(2 * k + 2));
        denom *= static_cast<unsigned long>(2 * k + 3);
        term *= -x2 / denom;
        if (abs(term) < epsilon) break;
    }
    return sin_x;
}

const mpf_class MathUtils::getCos(const std::vector<mpf_class> &arguments, size_t precision) {
    if (arguments.size() != 1) throw std::runtime_error("Argument num error");
    mpf_class x = arguments[0];
    unsigned int iter_num = precision;
    unsigned int prec_bits = precision * 3.321928 + 64;
    mpf_set_default_prec(prec_bits);
    mpf_class cos_x = 0;
    mpf_class term = 1;
    mpf_class x2 = x * x;
    mpf_class epsilon = mpf_class(1);
    for (size_t i = 0; i <= precision; ++i) epsilon /= 10;
    for (size_t k = 0; k < iter_num; ++k) {
        cos_x += term;
        mpf_class denom(static_cast<unsigned long>(2 * k + 2));
        denom *= static_cast<unsigned long>(2 * k + 1);
        term *= -x2 / denom;
        if (abs(term) < epsilon) break;
    }
    return cos_x;
}

MathUtils::PQT MathUtils::Chudnovsky(mpz_class n1, mpz_class n2) {
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

MathUtils::PQT MathUtils::Taylor(mpz_class n1, mpz_class n2) {
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