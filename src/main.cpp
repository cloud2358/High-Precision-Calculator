#include <myheader.h>

void CalculatePi() {

}

int main() {
    cpp_dec_float_100 pi;
    pi.assign("3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067");
    std::cout << std::setprecision(100) << pi << std::endl;
    return 0;
}