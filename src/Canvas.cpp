#include "Canvas.hpp"

Canvas::Canvas(QWidget * parent): QWidget(parent) {
    setFocusPolicy(Qt::StrongFocus);
}

void Canvas::scrollpage(int step) {
    if (scroll_pos + step >= 0)
        scroll_pos += step;
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
    QPainter painter(this);

    for (const auto& cmd: display_list) {
        if (cmd->top > scroll_pos + HEIGHT) continue;
        if (cmd->bottom < scroll_pos) continue;
        cmd->execute(painter);
    }
}