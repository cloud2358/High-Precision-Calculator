#include <MathConstants.h>

int main() {
    long long digits;
    std::cout << "Enter calculate digits: ";
    std::cin >> digits;
    std::cout << "Calculating " << digits << " digits of e..." << std::endl;
    mpf_class e = MathConstants::compute_e(digits);
    std::cout.precision(digits);
    std::cout << e << std::endl;
    return 0;
}