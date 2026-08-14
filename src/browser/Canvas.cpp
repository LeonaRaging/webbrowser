#include "browser/Canvas.hpp"
#include "browser/Browser.hpp"

Canvas::Canvas(Browser* browser, QWidget * parent): browser(browser), QWidget(parent) {
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
    painter.fillRect(this->rect(), QColor("white"));
    for (const auto& cmd: display_list) {
        if (cmd->top > scroll_pos + HEIGHT) continue;
        if (cmd->bottom < scroll_pos) continue;
        cmd->execute(painter);
    }
}

void Canvas::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        int x = event->position().x();
        int y = event->position().y();
        y += scroll_pos;

        std::vector<Layout*> list;
        tree_to_list(dynamic_cast<Layout*>(browser->document.get()), list);

        std::vector<Layout*> objs;
        for (Layout* layout : list)
            if (layout->x <= x && x < layout->x + layout->width &&
                layout->y - layout->height < y && y <= layout->y) 
                    objs.push_back(layout);
        if (objs.empty()) return;

        Token* elt = objs[0]->node;

        while (elt) {
            Element* element = dynamic_cast<Element*>(elt);
            if (element && element->value == "a" && element->attributes.contains("href")) {
                std::string url = element->attributes.value("href").toStdString();
                browser->url = url;
                browser->load(URL(url));
                update();
                return;
            }
            elt = elt->parent;
        }
    }
}