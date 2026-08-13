#pragma once

#include <QFont>
#include <QFontMetrics>
#include <map>

struct CachedFont {
    QFont font;
    QFontMetrics metrics;

    CachedFont(const QFont& f): font(f), metrics(font) {}
};

extern std::map<std::tuple<int, QFont::Weight, bool>, CachedFont> FONTS;

CachedFont* get_font(int, QFont::Weight, bool);