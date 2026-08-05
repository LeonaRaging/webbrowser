#pragma once

#include <QString>
#include <QDebug>

class Token {
    public:
        QString value;
        Token* parent = nullptr;
        std::vector<std::unique_ptr<Token>> children;
        explicit Token(const QString &v): value(v) {}
        explicit Token(const QString &v, Token* parent): value(v), parent(parent) {};
        virtual QString toString() const = 0;
        virtual ~Token() = default;
};

inline QDebug operator<<(QDebug dbg, const Token& token) {
    dbg.noquote() << token.toString();
    return dbg;
}