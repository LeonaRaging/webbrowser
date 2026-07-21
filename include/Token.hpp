#pragma once

#include <QString>

class Token {
    public:
        QString value;
        explicit Token(const QString &v): value(v) {}
        virtual ~Token() = default;
};