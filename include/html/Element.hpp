#pragma once

#include "html/Token.hpp"

class Element : public Token {
    public:
        using Token::Token;
        QString toString() const override {
            return "<" + value + ">";
        }
        QHash<QString, QString> attributes;
        explicit Element(const QString &v, QHash<QString, QString> attributes, Token* parent): Token(v, parent), attributes(attributes) {};
};