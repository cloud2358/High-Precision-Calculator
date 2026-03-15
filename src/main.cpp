#include <myheader.h>

/*
CHUDNVSKY(iterNum):
    s = 13591409
    a = 0
    f = 1
    for i = 1 iterNum
        f = f * i
        a = a * (12i - 2)(12i - 6)(12i - 10)
        b = b * -262537412640768000
        s += (13591409 + 545140134i) * a / (b * f);
    return 426880 * sqrt(10005) / s
*/

void CalculatePi() {

}

int main() {
    cpp_dec_float_100 pi;
    pi.assign("3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067");
    std::cout << std::setprecision(100) << pi << std::endl;
    return 0;
}