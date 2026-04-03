#ifndef EXTENDED_OPERATIONS_H
#define EXTENDED_OPERATIONS_H

#include <gmpxx.h>
#include <functional>
#include <vector>
#include <string>
#include <unordered_map>

class ExtendedOperations {
public:
    using Exfunction = std::function<mpf_class(std::vector<mpf_class>)>;
    mpf_class calculateFunc(std::string name, std::vector<mpf_class> arguments);
private:
    static const std::unordered_map<std::string, Exfunction> registry;
    static const mpf_class calculateSin(const std::vector<mpf_class>& arguments);
    static const mpf_class calculateCos(const std::vector<mpf_class>& arguments);
};

#endif