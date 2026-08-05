#pragma once

#include "html/Token.hpp"
#include "util/CachedFont.hpp"
#include "painting/DrawCmd.hpp"

struct Layout {
    int x;
    int y;
    int width;
    int height;
    Token* node;
    Layout* parent;
    Layout* previous;
    std::vector<std::unique_ptr<Layout>> children;
    std::vector<std::unique_ptr<DrawCmd>> display_list;

    virtual std::vector<std::unique_ptr<DrawCmd>> paint() = 0;
    virtual void layout();

    virtual ~Layout() = default;
    Layout(Token*);
    Layout(Token*, Layout*, Layout* previous);
};

void paint_tree(Layout* layout, std::vector<std::unique_ptr<DrawCmd>>& display_list);