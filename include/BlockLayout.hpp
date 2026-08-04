#include <QRegularExpression>
#include "Util.hpp"
#include "Text.hpp"
#include "Element.hpp"
#include "CachedFont.hpp"
#include "Layout.hpp"
#include "DrawText.hpp"
#include "DrawRect.hpp"

struct BlockLayout : public Layout {
    int cursor_x;
    int cursor_y;
    int fontSize;
    bool style;
    QFont::Weight weight;
    std::map<std::tuple<int, QFont::Weight, bool>, CachedFont> FONTS;
    std::vector<std::tuple<int, QString, CachedFont*>> line;
    
    void recurse(Token*);
    void flush();
    void open_tag(const QString&);
    void close_tag(const QString&);
    void add_word(const QString&);
    void layout();
    QString layout_mode();
    CachedFont& get_font(int, QFont::Weight, bool);
    std::vector<std::unique_ptr<DrawCmd>> paint() override;

    BlockLayout(Token*);
    BlockLayout(Token*, Layout*, Layout*);
};