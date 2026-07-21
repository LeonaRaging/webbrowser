#include <QFont>

struct CachedFont {
    QFont font;
    QFontMetrics metrics;

    CachedFont(const QFont& f): font(f), metrics(font) {}
};