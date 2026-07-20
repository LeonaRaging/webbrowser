#include "Canvas.hpp"
#include <iostream>
const int HSTEP = 13, VSTEP = 18;
int LIMIT = 800;

void Canvas::layout(const std::string &text) {
    int x = HSTEP, y = VSTEP;

    QString q_text = QString::fromUtf8(text);

    for (QChar c : q_text) {
        if (c == '\n') {
            x = HSTEP;
            y += VSTEP;
            continue;
        }
        display_list.emplace_back(x, y, c);
        x += HSTEP;
        if (x >= WIDTH - HSTEP) {
            y += VSTEP;
            x = HSTEP;
        }
        LIMIT = y;
    }
    update();
}

Canvas::Canvas(QWidget * parent): QWidget(parent) {
    setFocusPolicy(Qt::StrongFocus);
}

const int SCROLL_STEP = 100;

void Canvas::scrollpage(int step) {
    if (scroll + step >= 0 && scroll + step <= LIMIT)
        scroll += step;
    update();
}

void Canvas::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Down)
        scrollpage(SCROLL_STEP);
    else if (event->key() == Qt::Key_Up) {
        scrollpage(-SCROLL_STEP);
    } else {
        QWidget::keyPressEvent(event);
    }
}

void Canvas::wheelEvent(QWheelEvent *event) {
    int delta = event->angleDelta().y();
    if (delta > 0)
        scrollpage(-SCROLL_STEP);
    else if (delta < 0)
        scrollpage(SCROLL_STEP);
}

void Canvas::paintEvent(QPaintEvent *) {
    QFont font("Noto Sans CJK SC", 13);

    QPainter painter(this);
    painter.setFont(font);

    for (auto it : display_list) {
        int x, y; QChar c;
        std::tie(x, y, c) = it;
        if (y > scroll + HEIGHT) continue;
        if (y + VSTEP < scroll) continue;
        painter.drawText(x, y - scroll, QChar(c));
    }
}