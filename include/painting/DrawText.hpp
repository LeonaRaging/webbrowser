#pragma once

#include <QString>
#include "util/CachedFont.hpp"
#include "painting/DrawCmd.hpp"

struct DrawText : public DrawCmd {
    int left;
    QString text;
    CachedFont* font;

    void execute(QPainter& painter, int scroll_pos) override;

    DrawText(int, int, QString, CachedFont*, QColor);
};