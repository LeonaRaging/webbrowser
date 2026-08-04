#pragma once

#include <QFont>
#include <QFontMetrics>

struct CachedFont {
    QFont font;
    QFontMetrics metrics;

    CachedFont(const QFont& f): font(f), metrics(font) {}
};