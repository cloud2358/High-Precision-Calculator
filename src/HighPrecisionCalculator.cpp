#include <HighPrecisionCalculator.h>
#include <assert.h>

const mpf_class HighPrecisionCalculator::calculate(const std::string& input) {
    std::vector<Token> tokens = InputTokenizer::tokenize(input);
    
    std::vector<mpf_class> numbers;
    std::vector<char> ops;
    for (Token token : tokens) {
        if (token.type == TokenType::Number) {
            numbers.push_back((mpf_class)token.name);
        }
        else if (token.type == TokenType::Identifier) {
            if (MathConstants::isConstant(token.name)) {
                numbers.push_back(MathConstants::getConstant(token.name));
            }
            else {
                throw std::runtime_error("Error: undefined identifier!");
            }
        }
        else if (token.type == TokenType::Operator) {
            assert(token.name.size() == 1);
            if (token.name == "(") {
                ops.push_back('(');
            }
            else if (token.name == ")") {
                while (!ops.empty() && ops.back() != '(') {
                    mpf_class y = numbers.back(); numbers.pop_back();
                    mpf_class x = numbers.back(); numbers.pop_back();
                    char op = ops.back(); ops.pop_back();
                    numbers.push_back(ArithmeticOperations::getCalculationResult(x, y, op));
                }
                if (!ops.empty()) ops.pop_back();
            }
            else {
                char op = token.name[0];
                while (!ops.empty() && ArithmeticOperations::getPrecedence(ops.back()) >= ArithmeticOperations::getPrecedence(op))  {
                    mpf_class y = numbers.back(); numbers.pop_back();
                    mpf_class x = numbers.back(); numbers.pop_back();
                    numbers.push_back(ArithmeticOperations::getCalculationResult(x, y, ops.back()));
                    ops.pop_back();
                }
                ops.push_back(op);
            }
        }
    }
    while (ops.size()) {
        mpf_class y = numbers.back();
        numbers.pop_back();
        mpf_class x = numbers.back();
        numbers.pop_back();
        numbers.push_back(ArithmeticOperations::getCalculationResult(x, y, ops.back()));
        ops.pop_back();
    }
    return numbers.back();
}