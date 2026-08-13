#include "layout/TextLayout.hpp"

void TextLayout::layout() {
    QFont::Weight weight = ((node->style.value("font-weight") == "bold") ? QFont::Bold : QFont::Normal);
    bool style = ((node->style.value("font-style") == "italic") ? true : false);
    QString font_size = node->style.value("font-size");
    int size = int(font_size.left(font_size.size() - 2).toDouble() * 0.75);
    font = get_font(size, weight, style);

    width = font->metrics.horizontalAdvance(word);

    if (previous) {
        int space = font->metrics.horizontalAdvance(" ");
        x = previous->x + space + previous->width;
    } else {
        x = parent->x;
    }

    height = font->metrics.lineSpacing();
}

std::vector<std::unique_ptr<DrawCmd>> TextLayout::paint() {
    std::vector<std::unique_ptr<DrawCmd>> cmds;
    QColor bgcolor(node->style.value("color"));
    cmds.emplace_back(new DrawText(x, y, word, font, bgcolor));
    return cmds;
}

TextLayout::TextLayout(Token* node, QString word, Layout* parent, Layout* previous):
    Layout(node, parent, previous), word(word) {font = nullptr;}