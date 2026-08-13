#pragma once

#include "layout/Layout.hpp"
#include "painting/DrawText.hpp"

struct TextLayout : public Layout {
    QString word;
    CachedFont* font;

    void layout() override;
    std::vector<std::unique_ptr<DrawCmd>> paint() override;

    TextLayout(Token*, QString, Layout*, Layout*);
};