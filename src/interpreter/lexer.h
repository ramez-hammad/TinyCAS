#pragma once

enum class TokenType
{
    TokenNum,
    TokenPlus,
    TokenMinus,
    TokenMul,
    TokenDiv,
    TokenNull
};

class Token
{
public:
    TokenType type;
    double val;
};


std::vector<Token> tokenize(std::string expr);
