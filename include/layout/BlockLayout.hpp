#include <QRegularExpression>
#include "util/Util.hpp"
#include "html/Text.hpp"
#include "html/Element.hpp"
#include "util/CachedFont.hpp"
#include "layout/Layout.hpp"
#include "layout/LineLayout.hpp"
#include "layout/TextLayout.hpp"
#include "painting/DrawText.hpp"
#include "painting/DrawRect.hpp"

struct BlockLayout : public Layout {
    int cursor_x;
    
    void recurse(Token*);
    void new_line();
    void add_word(Token*, const QString&);
    void layout();
    QString layout_mode();
    std::vector<std::unique_ptr<DrawCmd>> paint() override;

    BlockLayout(Token*);
    BlockLayout(Token*, Layout*, Layout*);
};