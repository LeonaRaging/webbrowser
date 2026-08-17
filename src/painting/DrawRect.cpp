#include "painting/DrawRect.hpp"

void DrawRect::execute(QPainter& painter, int scroll_pos) {
    painter.fillRect(left, top - scroll_pos, right - left + 1, bottom - top + 1, color);
}

DrawRect::DrawRect(int x1, int y1, int x2, int y2, QColor color):
    left(x1), right(x2) {
        top = y1;
        bottom = y2;
        this->color = color;
    }