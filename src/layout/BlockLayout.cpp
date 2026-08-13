#include "layout/BlockLayout.hpp"

std::vector<QString> BLOCK_ELEMENTS = {
    "html", "body", "article", "section", "nav", "aside",
    "h1", "h2", "h3", "h4", "h5", "h6", "hgroup", "header",
    "footer", "address", "p", "hr", "pre", "blockquote",
    "ol", "ul", "menu", "li", "dl", "dt", "dd", "figure",
    "figcaption", "main", "div", "table", "form", "fieldset",
    "legend", "details", "summary"
};

void BlockLayout::new_line() {
    cursor_x = 0;
    LineLayout* last_line = (children.empty() ? nullptr : dynamic_cast<LineLayout*>(children.back().get()));
    std::unique_ptr<LineLayout> line = std::unique_ptr<LineLayout>(new LineLayout(node, this, last_line));
    children.push_back(std::move(line));
}

void BlockLayout::add_word(Token* node, const QString &word) {
    QFont::Weight weight = ((node->style.value("font-weight") == "bold") ? QFont::Bold : QFont::Normal);
    bool style = ((node->style.value("font-style") == "italic") ? true : false);
    QString font_size = node->style.value("font-size");
    int fontSize = int(font_size.left(font_size.size() - 2).toDouble() * 0.75);
    QColor color(node->style.value("color"));

    CachedFont* cached_font = get_font(fontSize, weight, style);
    int w = cached_font->metrics.horizontalAdvance(word);
    if (cursor_x + w > width) {
        new_line();
    }

    LineLayout* line = dynamic_cast<LineLayout*>(children.back().get());
    TextLayout* previous_word = (line->children.empty() ? nullptr : dynamic_cast<TextLayout*>(line->children.back().get()));
    std::unique_ptr<TextLayout> text = std::unique_ptr<TextLayout>(new TextLayout(node, word, line, previous_word));
    line->children.push_back(std::move(text));

    cursor_x += w + cached_font->metrics.horizontalAdvance(" ");
}

void BlockLayout::recurse(Token* tree) {
    QRegularExpression re("\\s+");
    if (auto text = dynamic_cast<Text*>(tree)) {
        for (const QString &word : text->value.split(re, Qt::SkipEmptyParts))
            add_word(tree, word);
    } else if (auto element = dynamic_cast<Element*>(tree)) {
        if (element->value == "br")
            new_line();
        for (const auto& token : tree->children)
            recurse(token.get());
    }
}

void BlockLayout::layout() {
    x = parent->x;
    width = parent->width;

    if (previous != nullptr) {
        y = previous->y + previous->height;    
    } else y = parent->y;

    QString mode = layout_mode();
    if (mode == "block") {
        Layout* previous = nullptr;
        for (auto const& child: node->children) {
            std::unique_ptr<BlockLayout> next(new BlockLayout(child.get(), this, previous));
            next->layout();
            height += next->height;
            previous = next.get();
            children.push_back(std::move(next));
        }
    } else {
        new_line();
        recurse(node);

        height = 0;
        for (const auto& child : children) {
            child->layout();
            height += child->height;
        }
    }
}

QString BlockLayout::layout_mode() {
    if (dynamic_cast<Text*>(node))
        return "inline";
    else {
        for (auto const& child : node->children) {
            Element* tag = dynamic_cast<Element*>(child.get());
            if (tag && contains(BLOCK_ELEMENTS, tag->value))
                return "block";
        }
    }
    return (node->children.empty() ? "block" : "inline");
}

std::vector<std::unique_ptr<DrawCmd>> BlockLayout::paint() {
    std::vector<std::unique_ptr<DrawCmd>> cmds;
    QColor bgcolor(node->style.value("background-color", "transparent"));
    if (bgcolor != Qt::transparent) {
        int x2 = x + width;
        int y2 = y + height;
        cmds.emplace_back(new DrawRect(x, y, x2, y2, bgcolor));
    }
    return cmds;
}

BlockLayout::BlockLayout(Token* node): Layout(node) {}

BlockLayout::BlockLayout(Token* node, Layout* parent, Layout* previous): 
    Layout(node, parent, previous) {}