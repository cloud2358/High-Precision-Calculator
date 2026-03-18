#include <MathConstants.h>

int main() {
    long long digits;
    std::cout << "Enter calculate digits: ";
    std::cin >> digits;
    std::cout << "Calculating " << digits << " digits of Pi..." << std::endl;
    mpf_class pi = MathConstants::compute_pi(digits);
    std::cout.precision(digits);
    std::cout << pi << std::endl;
    return 0;
}