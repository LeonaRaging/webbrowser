#include "Layout.hpp"

void Layout::layout() {
    
}

Layout::Layout(Token* node): node(node) {
    parent = nullptr;
    previous = nullptr;
}

Layout::Layout(Token* node, Layout* parent, Layout* previous):
    node(node), parent(parent), previous(previous) {
        x = 0;
        y = 0;
        width = 0;
        height = 0;
    }

void paint_tree(Layout* layout, std::vector<std::unique_ptr<DrawCmd>>& display_list) {
    std::vector<std::unique_ptr<DrawCmd>> cmds = std::move(layout->paint());

    display_list.insert(display_list.end(),
                    std::make_move_iterator(cmds.begin()),
                    std::make_move_iterator(cmds.end()));

    for (auto const& child : layout->children)
        paint_tree(child.get(), display_list);
};