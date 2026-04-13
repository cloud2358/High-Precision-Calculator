#ifndef TOKEN_H
#define TOKEN_H

#pragma once
#include <string>

enum class TokenType {
    Number,
    Operator,
    LeftParen,
    RightParen,
    Variant,
    Function,
    Constant,
    Comma,
    End
};

struct Token {
    TokenType type;
    std::string name;
};

#endif