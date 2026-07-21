#include "Canvas.hpp"

const int HSTEP = 13, VSTEP = 18;
int LIMIT = 800;

CachedFont& Canvas::get_font(int size, QFont::Weight weight, bool style) {
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

void Canvas::flush() {
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
        int x; QString word; CachedFont* cached_font; 
        std::tie(x, word, cached_font) = it;
        display_list.emplace_back(x, baseline, word, cached_font);
    }
    cursor_y = baseline + 1.25 * max_descent;
    LIMIT = cursor_y;
    cursor_x = HSTEP;
    line.clear();
}

void Canvas::layout(const std::vector<std::unique_ptr<Token>> &tokens) {
    cursor_x = HSTEP, cursor_y = VSTEP;
    int fontSize = 12;
    QFont::Weight weight = QFont::Normal;
    bool style = false;

    for (const auto &token: tokens) {
        QRegularExpression re("\\s+");
        if (auto text = dynamic_cast<Text*>(token.get())) {
            for (const QString &word : text->value.split(re, Qt::SkipEmptyParts)) {
                CachedFont& cached_font = get_font(fontSize, weight, style);
                int w = cached_font.metrics.horizontalAdvance(word);
                if (cursor_x + w > WIDTH - HSTEP) {
                    flush();
                }
                line.emplace_back(cursor_x, word, &cached_font);
                cursor_x += w + cached_font.metrics.horizontalAdvance(" ");
            }
        } else if (auto tag = dynamic_cast<Tag*>(token.get())) {
            if (tag->value == "i")
                style = true;
            else if (tag->value == "/i")
                style = false;
            else if (tag->value == "b")
                weight = QFont::Bold;
            else if (tag->value == "/b")
                weight = QFont::Normal;
            else if (tag->value == "small")
                fontSize -= 2;
            else if (tag->value == "/small")
                fontSize += 2;
            else if (tag->value == "big")
                fontSize += 4;
            else if (tag->value == "/big")
                fontSize -= 4;
            else if (tag->value == "br")
                flush();
            else if (tag->value == "/p") {
                flush();
                cursor_y += VSTEP;
            }
        }
    }
    flush();
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
    QPainter painter(this);

    for (const auto &it : display_list) {
        int x, y; QString c; CachedFont* cached_font;
        std::tie(x, y, c, cached_font) = it;
        if (y > scroll + HEIGHT) continue;
        if (y + VSTEP < scroll) continue;
        painter.setFont(cached_font->font);
        painter.drawText(x, y - scroll, c);
    }
}