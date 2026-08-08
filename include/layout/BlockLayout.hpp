#include <QRegularExpression>
#include "util/Util.hpp"
#include "html/Text.hpp"
#include "html/Element.hpp"
#include "util/CachedFont.hpp"
#include "layout/Layout.hpp"
#include "painting/DrawText.hpp"
#include "painting/DrawRect.hpp"

struct BlockLayout : public Layout {
    int cursor_x;
    int cursor_y;
    std::map<std::tuple<int, QFont::Weight, bool>, CachedFont> FONTS;
    std::vector<std::tuple<int, QString, CachedFont*, QColor>> line;
    
    void recurse(Token*);
    void flush();
    void add_word(Token*, const QString&);
    void layout();
    QString layout_mode();
    CachedFont& get_font(int, QFont::Weight, bool);
    std::vector<std::unique_ptr<DrawCmd>> paint() override;

    BlockLayout(Token*);
    BlockLayout(Token*, Layout*, Layout*);
};