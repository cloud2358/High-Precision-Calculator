#include "myheader.h"

const unsigned int N = 10000;

typedef number<cpp_dec_float<N>> myfloat;

int main() {
    myfloat pic = boost::math::constants::pi<myfloat>();
    std::cout << "Pi to " << N << " decimal places:" << std::endl;
    std::cout << pic.str(N) << std::endl;
    return 0;
}