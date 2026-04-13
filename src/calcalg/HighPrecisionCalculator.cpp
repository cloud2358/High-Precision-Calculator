#include <HighPrecisionCalculator.h>
#include <assert.h>

const std::vector<mpf_class> HighPrecisionCalculator::calculate(const std::string& input) {
    std::vector<Token> tokens = InputTokenizer::split(input);
    if (!InputTokenizer::check(tokens,1)) {
        throw std::runtime_error("Grammar check fail");
    }
    return getAllResults(tokens, 0, tokens.size() - 1);
}

const std::vector<mpf_class> HighPrecisionCalculator::getAllResults(const std::vector<Token>& tokens, size_t l, size_t r) {
    if (l > r) throw std::runtime_error("l > r");
    std::vector<mpf_class> results;
    size_t position = l, lastPosition = l, parenCount = 0;
    while (position <= r) {
        Token token = tokens[position];
        if (token.type == TokenType::LeftParen) {
            parenCount++;
        }
        else if (token.type == TokenType::RightParen) {
            parenCount--;
        }
        else if (token.type == TokenType::Comma && parenCount == 0) {
            mpf_class result = getResult(tokens, lastPosition, position - 1);
            results.push_back(result);
            lastPosition = position + 1;
        }
        position++;
    }
    results.push_back(getResult(tokens, lastPosition, r));
    return results;
}

const mpf_class HighPrecisionCalculator::getResult(const std::vector<Token>& tokens, size_t l, size_t r) {
    if (l > r) throw std::runtime_error("l > r");
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
            std::vector<mpf_class> args;
            if (tokens[position].type == TokenType::Number) {
                args.push_back((mpf_class)tokens[position].name);
            }
            else if (tokens[position].type == TokenType::LeftParen) {
                size_t LeftPosition = position, RightPosition = position;
                while (tokens[RightPosition].type != TokenType::RightParen) RightPosition++;
                args = getAllResults(tokens, LeftPosition + 1, RightPosition - 1);
                position = RightPosition;
            }
            numbers.push_back(MathUtils::getMathFunc(token.name, args));
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
                if (numbers.empty()) throw std::runtime_error("no number found in stack");
                mpf_class y = numbers.back();
                numbers.pop_back();
                if (numbers.empty()) throw std::runtime_error("at least 2 number should be in stack");
                mpf_class x = numbers.back();
                numbers.pop_back();
                numbers.push_back(ArithmeticOperations::getCalculationResult(x, y, ops.back()));
                ops.pop_back();
            }
            ops.push_back(op);
        }
        else throw std::runtime_error("illegal token in sub-expression");
        position++;
    }
    while (ops.size()) {
        if (numbers.empty()) throw std::runtime_error("no number found in stack");
        mpf_class y = numbers.back();
        numbers.pop_back();
        if (numbers.empty()) throw std::runtime_error("at least 2 number should be in stack");
        mpf_class x = numbers.back();
        numbers.pop_back();
        numbers.push_back(ArithmeticOperations::getCalculationResult(x, y, ops.back()));
        ops.pop_back();
    }
    if (numbers.empty()) throw std::runtime_error("number stack is empty");
    return numbers.back();
}