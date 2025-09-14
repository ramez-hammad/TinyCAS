#include <vector>
#include <string>

#include "lexer.h"

Token create_token_num(double val) { return {TokenType::TokenNum, val}; }

Token create_token_op(TokenType type) { return {type}; }

Token create_token_func(TokenType type, std::string arg) { return {type, 0, std::move(arg)}; }

Token create_token_var(char sym) { return {TokenType::TokenVar, 0, "", sym}; }

// Get function argument
std::string get_func_arg(std::string expr, size_t pos)
{
    std::string arg;
    int num_paren = 0;

    for (; pos < expr.length(); pos++) {
        if (expr.at(pos) == '(') {
            num_paren++;
            arg.push_back(expr[pos]);
        } else if (expr.at(pos) == ')') {
            num_paren--;
            if (num_paren >= 0) {
                arg.push_back(expr[pos]);
            } else {
                break;
            }
        } else {
            arg.push_back(expr[pos]);
        }
    }

    return arg;
}

std::vector<Token> tokenize(std::string expr)
{
    std::vector<Token> token_vector;

    size_t pos = 0;
    while (pos < expr.length()) {
        // Number
        if (isdigit(expr.at(pos)) || expr.at(pos) == '.') {
            size_t i = pos;
            bool decimal_point = false;

            while (i < expr.length()) {
                if (isdigit(expr.at(i))) {
                    i++;
                } else if (expr.at(i) == '.') {
                    if (decimal_point) {
                        // Error
                    } else {
                        decimal_point = true;
                        i++;
                    }
                } else {
                    break;
                }
            }

            token_vector.push_back(create_token_num(std::stod(expr.substr(pos, i - pos))));
            pos = i - 1;
        }

        switch (expr.at(pos)) {
            // Symbols
            case '+':
                token_vector.push_back(create_token_op(TokenType::TokenPlus));
                break;
            case '-':
                token_vector.push_back(create_token_op(TokenType::TokenMinus));
                break;
            case '*':
                token_vector.push_back(create_token_op(TokenType::TokenMul));
                break;
            case '/':
                token_vector.push_back(create_token_op(TokenType::TokenDiv));
                break;
            case '^':
                token_vector.push_back(create_token_op(TokenType::TokenPow));
                break;
            case '!':
                token_vector.push_back(create_token_op(TokenType::TokenFactorial));
                break;
            case '(':
                token_vector.push_back(create_token_op(TokenType::TokenLParen));
                break;
            case ')':
                token_vector.push_back(create_token_op(TokenType::TokenRParen));
                break;
            case '=':
                token_vector.push_back(create_token_op(TokenType::TokenEqual));
                break;

            // Functions
            case 's':
                if (expr.at(pos + 3) == '(') {
                    // sin
                    token_vector.push_back(create_token_func(TokenType::TokenSin, get_func_arg(expr, pos + 4)));

                    pos += 4;
                    pos += token_vector.back().arg.length();
                } else if (expr.at(pos + 4) == '(') {
                    // sinh
                    token_vector.push_back(create_token_func(TokenType::TokenSinh, get_func_arg(expr, pos + 5)));

                    pos += 5;
                    pos += token_vector.back().arg.length();
                } else {
                    // sqrt
                    token_vector.push_back(create_token_func(TokenType::TokenSqrt, get_func_arg(expr, pos + 5)));

                    pos += 5;
                    pos += token_vector.back().arg.length();
                }

                break;
            case 'c':
                if (expr.at(pos + 4) == '(') {
                    // cos
                    token_vector.push_back(create_token_func(TokenType::TokenCos, get_func_arg(expr, pos + 5)));

                    pos += 5;
                    pos += token_vector.back().arg.length();
                } else {
                    // cosh
                    token_vector.push_back(create_token_func(TokenType::TokenCosh, get_func_arg(expr, pos + 5)));

                    pos += 5;
                    pos += token_vector.back().arg.length();
                }

                break;
            case 't':
                if (expr.at(pos + 3) == '(') {
                    // tan
                    token_vector.push_back(create_token_func(TokenType::TokenTan, get_func_arg(expr, pos + 4)));

                    pos += 4;
                    pos += token_vector.back().arg.length();
                } else {
                    // tanh
                    token_vector.push_back(create_token_func(TokenType::TokenCos, get_func_arg(expr, pos + 5)));

                    pos += 5;
                    pos += token_vector.back().arg.length();
                }

                break;
            case 'a':
                if (expr.at(pos + 2) == 's') {
                    // abs
                    token_vector.push_back(create_token_func(TokenType::TokenAbs, get_func_arg(expr, pos + 4)));

                    pos += 4;
                    pos += token_vector.back().arg.length();
                } else if (expr.at(pos + 1) == 's') {
                    if (expr.at(pos + 4) == '(') {
                        // asin
                        token_vector.push_back(create_token_func(TokenType::TokenAsin, get_func_arg(expr, pos + 5)));

                        pos += 5;
                        pos += token_vector.back().arg.length();
                    } else {
                        // asinh
                        token_vector.push_back(create_token_func(TokenType::TokenAsinh, get_func_arg(expr, pos + 6)));

                        pos += 6;
                        pos += token_vector.back().arg.length();
                    }
                } else if (expr.at(pos + 1) == 'c') {
                    if (expr.at(pos + 4) == '(') {
                        // acos
                        token_vector.push_back(create_token_func(TokenType::TokenAcos, get_func_arg(expr, pos + 5)));

                        pos += 5;
                        pos += token_vector.back().arg.length();
                    } else {
                        // acosh
                        token_vector.push_back(create_token_func(TokenType::TokenAcosh, get_func_arg(expr, pos + 6)));

                        pos += 6;
                        pos += token_vector.back().arg.length();
                    }
                } else {
                    // t
                    if (expr.at(pos + 4) == '(') {
                        // atan
                        token_vector.push_back(create_token_func(TokenType::TokenAtan, get_func_arg(expr, pos + 5)));

                        pos += 5;
                        pos += token_vector.back().arg.length();
                    } else {
                        // atanh
                        token_vector.push_back(create_token_func(TokenType::TokenAtanh, get_func_arg(expr, pos + 6)));

                        pos += 6;
                        pos += token_vector.back().arg.length();
                    }
                }

                break;
            case 'l':
                if (expr.at(pos + 1) == 'n') {
                    // ln
                    token_vector.push_back(create_token_func(TokenType::TokenLog, get_func_arg(expr, pos + 3)));

                    pos += 3;
                    pos += token_vector.back().arg.length();
                } else {
                    // log
                    token_vector.push_back(create_token_func(TokenType::TokenLog, get_func_arg(expr, pos + 4)));

                    pos += 4;
                    pos += token_vector.back().arg.length();
                }
                break;
        }

        // Variables
        // A-Z, x, pi, e
        if ((expr.at(pos) >= 65 && expr.at(pos) <= 90) || expr.at(pos) == 'x' || expr.at(pos) == 'p' || expr.at(pos) == 'e') {
            token_vector.push_back(create_token_var(expr.at(pos)));
        }

        pos++;
    }

    return token_vector;
}
