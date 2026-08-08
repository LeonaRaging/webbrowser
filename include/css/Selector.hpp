#pragma once

#include "html/Token.hpp"

struct Selector {
    int priority;

    virtual ~Selector() = default;
    virtual bool matches(Token*) const = 0;
};