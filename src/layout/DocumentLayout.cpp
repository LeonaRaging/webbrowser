#include "layout/DocumentLayout.hpp"

std::vector<std::unique_ptr<DrawCmd>> DocumentLayout::paint() {
    return std::vector<std::unique_ptr<DrawCmd>>();
}

void DocumentLayout::layout() {
    width = WIDTH - 2 * HSTEP;
    x = HSTEP;
    y = VSTEP;

    std::unique_ptr<Layout> child(new BlockLayout(node, this, nullptr));
    child->layout();
    height = child->height;
    children.push_back(std::move(child));
}

DocumentLayout::DocumentLayout(Token* node): Layout(node) {}

DocumentLayout::DocumentLayout(Token* node, Layout* parent, Layout* previous): Layout(node, parent, previous) {}