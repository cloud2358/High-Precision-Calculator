#include <HighPrecisionCalculator.h>
#include <assert.h>

const mpf_class HighPrecisionCalculator::calculate(const std::string& input) {
    std::vector<Token> tokens = InputTokenizer::split(input);
    if (!InputTokenizer::check(tokens)) {
        throw std::runtime_error("Grammar check fail");
    }
    return evaluateTokensStack(tokens, 0, tokens.size() - 1);
}

const mpf_class HighPrecisionCalculator::evaluateTokensStack(const std::vector<Token>& tokens, size_t l, size_t r) {
    std::vector<mpf_class> numbers;
    std::vector<char> ops;

    size_t position = l;
    while (position <= r) {
        Token token = tokens[position];
        if (token.type == TokenType::Number) {
            numbers.push_back((mpf_class)token.name);
        }
        else if (token.type == TokenType::Constant) {
            numbers.push_back(MathUtils::getMathConst(token.name));
        }
        else if (token.type == TokenType::Function) {
            position++;
            mpf_class argument = 0;
            if (tokens[position].type == TokenType::Number) {
                argument = (mpf_class)tokens[position].name;
            }
            else if (tokens[position].type == TokenType::LeftParen) {
                size_t LeftPosition = position, RightPosition = position;
                while (tokens[RightPosition].type != TokenType::RightParen) RightPosition++;
                argument = evaluateTokensStack(tokens, LeftPosition + 1, RightPosition - 1);
                position = RightPosition;
            }
            numbers.push_back(MathUtils::getMathFunc(token.name, {argument}));
        }
        else if (token.type == TokenType::Variant) {
            throw std::runtime_error("Function not finished yet!");
        }
        else if (token.type == TokenType::LeftParen) {
            ops.push_back('(');
        }
        else if (token.type == TokenType::RightParen) {
            while (!ops.empty() && ops.back() != '(') {
                mpf_class y = numbers.back(); numbers.pop_back();
                mpf_class x = numbers.back(); numbers.pop_back();
                char op = ops.back(); ops.pop_back();
                numbers.push_back(ArithmeticOperations::getCalculationResult(x, y, op));
            }
            if (!ops.empty()) ops.pop_back();
        }
        else if (token.type == TokenType::Operator) {
            char op = token.name[0];
            while (!ops.empty() && ArithmeticOperations::getPrecedence(ops.back()) >= ArithmeticOperations::getPrecedence(op)) {
                mpf_class y = numbers.back();
                numbers.pop_back();
                mpf_class x = numbers.back();
                numbers.pop_back();
                numbers.push_back(ArithmeticOperations::getCalculationResult(x, y, ops.back()));
                ops.pop_back();
            }
            ops.push_back(op);
        }
        position++;
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