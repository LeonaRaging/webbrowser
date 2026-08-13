#include "util/CachedFont.hpp"

std::map<std::tuple<int, QFont::Weight, bool>, CachedFont> FONTS;

CachedFont* get_font(int size, QFont::Weight weight, bool style) {
    std::tuple<int, QFont::Weight, bool> key = {size, weight, style};
    auto it = FONTS.find(key);

    if (it == FONTS.end()) {
        QFont font("Times", size);
        font.setWeight(weight);
        font.setItalic(style);
        it = FONTS.emplace(key, CachedFont(font)).first;
    }

    return &it->second;
}