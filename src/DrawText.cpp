#include "DrawText.hpp"

void DrawText::execute(QPainter &painter) {
    painter.setFont(font->font);
    painter.drawText(left, top - scroll_pos, text);
}  

DrawText::DrawText(int x1, int y1, QString text, CachedFont* font):
    left(x1), text(text), font(font) {
        top = y1;
        bottom = y1 + font->metrics.lineSpacing();
    }