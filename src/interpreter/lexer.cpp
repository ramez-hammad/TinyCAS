#include <vector>
#include <string>

#include "lexer.h"

Token create_token_num(double val)
{
    return {TokenType::TokenNum, val};
}

Token create_token_op(TokenType type)
{
    return {type};
}

std::vector<Token> tokenize(std::string expr)
{
    std::vector<Token> token_vector;

    size_t pos = 0;
    while (pos < expr.length()) {
        // Number
        if (isdigit(expr.at(pos))) {
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
            // Operators
            case '+':
                token_vector.push_back(create_token_op(TokenType::TokenPlus));
                break;
            case '-':
                token_vector.push_back(create_token_op(TokenType::TokenPlus));
                break;
            case '*':
                token_vector.push_back(create_token_op(TokenType::TokenPlus));
                break;
            case '/':
                token_vector.push_back(create_token_op(TokenType::TokenPlus));
                break;
        }
        pos++;
    }

    return token_vector;
}
