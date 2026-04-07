#ifndef TOKEN_H
#define TOKEN_H

#pragma once
#include <string>

enum class TokenType {
    Number,
    Operator,
    Variant,
    Function,
    Comma,
    Fullstop
};

struct Token {
    TokenType type;
    std::string name;
};

#endif