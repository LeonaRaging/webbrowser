#include "layout/LineLayout.hpp"

std::vector<std::unique_ptr<DrawCmd>> LineLayout::paint() {
    return std::vector<std::unique_ptr<DrawCmd>>();
}

void LineLayout::layout() {
    width = parent->width;
    x = parent->x;

    if (previous) {
        y = previous->y + previous->height;
    } else {
        y = parent->y;
    }

    int max_ascent = 0, max_descent = 0;
    for (const auto& child : children) {
        if (auto word = dynamic_cast<TextLayout*>(child.get())) {
            word->layout();
            max_ascent = std::max(max_ascent, word->font->metrics.ascent());
            max_descent = std::max(max_descent, word->font->metrics.descent());
        }
    }
    int baseline = y + 1.25 * max_ascent;
    for (const auto& child : children) {
        if (auto word = dynamic_cast<TextLayout*>(child.get())) {
            word->y = baseline;
        }
    }

    height = 1.25 * (max_ascent + max_descent);
}

LineLayout::LineLayout(Token* node, Layout* parent, Layout* previous):
    Layout(node, parent, previous) {};