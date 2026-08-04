#include "BlockLayout.hpp"

std::vector<QString> BLOCK_ELEMENTS = {
    "html", "body", "article", "section", "nav", "aside",
    "h1", "h2", "h3", "h4", "h5", "h6", "hgroup", "header",
    "footer", "address", "p", "hr", "pre", "blockquote",
    "ol", "ul", "menu", "li", "dl", "dt", "dd", "figure",
    "figcaption", "main", "div", "table", "form", "fieldset",
    "legend", "details", "summary"
};

void BlockLayout::flush() {
    if (line.empty()) return;
    int max_ascent = 0, max_descent = 0;
    for (const auto &it : line) {
        int x; QString word; CachedFont* cached_font; 
        std::tie(x, word, cached_font) = it;
        max_ascent = std::max(max_ascent, cached_font->metrics.ascent());
        max_descent = std::max(max_descent, cached_font->metrics.descent());
    }
    int baseline = cursor_y + 1.25 * max_ascent;
    for (auto it : line) {
        int rel_x; QString word; CachedFont* cached_font; 
        std::tie(rel_x, word, cached_font) = it;
        int new_x = x + rel_x;
        int new_y = y + baseline;
        display_list.emplace_back(new DrawText(new_x, new_y, word, cached_font));
    }
    cursor_y = baseline + 1.25 * max_descent;
    cursor_x = 0;
    line.clear();
}

void BlockLayout::open_tag(const QString& tag) {
    if (tag == "i")
        style = true;
    else if (tag == "b")
        weight = QFont::Bold;
    else if (tag == "small")
        fontSize -= 2;
    else if (tag == "big")
        fontSize += 4;
    else if (tag == "br")
        flush();
}

void BlockLayout::close_tag(const QString& tag) {
    if (tag == "i")
        style = false;
    else if (tag == "b")
        weight = QFont::Normal;
    else if (tag == "small")
        fontSize += 2;
    else if (tag == "big")
        fontSize -= 4;
    else if (tag == "p") {
        flush();
        cursor_y += VSTEP;
    }
}

void BlockLayout::add_word(const QString &word) {
    CachedFont& cached_font = get_font(fontSize, weight, style);
    int w = cached_font.metrics.horizontalAdvance(word);
    if (cursor_x + w > width) {
        flush();
    }
    line.emplace_back(cursor_x, word, &cached_font);
    cursor_x += w + cached_font.metrics.horizontalAdvance(" ");
}

void BlockLayout::recurse(Token* tree) {
    QRegularExpression re("\\s+");
    if (auto text = dynamic_cast<Text*>(tree)) {
        for (const QString &word : text->value.split(re, Qt::SkipEmptyParts))
            add_word(word);
    } else if (auto element = dynamic_cast<Element*>(tree)) {
        open_tag(element->value);
        for (const auto& token : tree->children)
            recurse(token.get());
        close_tag(element->value);
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
        cursor_x = 0;
        cursor_y = 0;
        fontSize = 12;
        weight = QFont::Normal;
        style = false;
        recurse(node);
        flush();
        height = cursor_y;
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

CachedFont& BlockLayout::get_font(int size, QFont::Weight weight, bool style) {
    std::tuple<int, QFont::Weight, bool> key = {size, weight, style};
    auto it = FONTS.find(key);

    if (it == FONTS.end()) {
        QFont font("Times", size);
        font.setWeight(weight);
        font.setItalic(style);
        it = FONTS.emplace(key, CachedFont(font)).first;
    }

    return it->second;
}

std::vector<std::unique_ptr<DrawCmd>> BlockLayout::paint() {
    std::vector<std::unique_ptr<DrawCmd>> cmds;
    qDebug() << node->value;
    if (dynamic_cast<Element*>(node) && node->value == "pre") {
        int x2 = x + width;
        int y2 = y + height;
        cmds.emplace_back(new DrawRect(x, y, x2, y2, Qt::gray));
    }
    if (layout_mode() == "inline") {
        cmds.insert(cmds.end(),
                    std::make_move_iterator(display_list.begin()),
                    std::make_move_iterator(display_list.end()));
    }
    return cmds;
}

BlockLayout::BlockLayout(Token* node): Layout(node) {}

BlockLayout::BlockLayout(Token* node, Layout* parent, Layout* previous): 
    Layout(node, parent, previous) {}