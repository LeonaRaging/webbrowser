#pragma once

#include <QPainter>
#include "util/Util.hpp"

struct DrawCmd {
    int top;
    int bottom;
    QColor color;
    virtual ~DrawCmd() {}
    virtual void execute(QPainter &painter, int scroll_pos) = 0;
};