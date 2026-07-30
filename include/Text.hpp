#pragma once

#include "Token.hpp"

class Text : public Token {
    using Token::Token;
    QString toString() const override {
        return value;
    }
};