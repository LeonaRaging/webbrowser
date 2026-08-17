#include "painting/DrawText.hpp"

void DrawText::execute(QPainter &painter, int scroll_pos) {
    painter.setFont(font->font);
    painter.setPen(color);
    painter.drawText(left, top - scroll_pos, text);
}  

DrawText::DrawText(int x1, int y1, QString text, CachedFont* font, QColor color):
    left(x1), text(text), font(font) {
        top = y1;
        bottom = y1 + font->metrics.lineSpacing();
        this->color = color;
    }