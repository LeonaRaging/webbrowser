#pragma once

#include <QPainter>
#include "Util.hpp"

struct DrawCmd {
    int top;
    int bottom;
    virtual ~DrawCmd() {}
    virtual void execute(QPainter &painter) = 0;
};