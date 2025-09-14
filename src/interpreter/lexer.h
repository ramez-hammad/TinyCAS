#pragma once

enum class TokenType
{
    TokenNum,
    TokenPlus,
    TokenMinus,

    // Unary operators are only identified in the parser
    TokenUnaryMinus,
    TokenUnaryPlus,

    TokenMul,
    TokenDiv,
    TokenPow,
    TokenFactorial,
    TokenLParen,
    TokenRParen,
    TokenEqual,
    TokenComma,
    TokenSin,
    TokenCos,
    TokenTan,
    TokenSinh,
    TokenCosh,
    TokenTanh,
    TokenAsin,
    TokenAcos,
    TokenAtan,
    TokenAsinh,
    TokenAcosh,
    TokenAtanh,
    TokenLn,
    TokenLog,
    TokenSqrt,
    TokenAbs,
    TokenVar,
    TokenNull
};

class Token
{
public:
    TokenType type;
    double val; // For numbers
    std::string arg; // For functions
    char sym; // For variables
};


std::vector<Token> tokenize(std::string expr);
