#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QRegularExpression>
#include <unordered_map>
#include "Text.hpp"
#include "Element.hpp"
#include "CachedFont.hpp"

const int WIDTH = 800;
const int HEIGHT = 600;

struct Canvas : public QWidget {
    public:
        void recurse(Token*);
        Canvas(QWidget *parent = nullptr);
    protected:
        void paintEvent(QPaintEvent *) override;
        void keyPressEvent(QKeyEvent*) override;
        void wheelEvent(QWheelEvent*) override;
        void scrollpage(int step);
    private:
        int fontSize;
        bool style;
        QFont::Weight weight;
        std::map<std::tuple<int, QFont::Weight, bool>, CachedFont> FONTS;
        int cursor_x, cursor_y, scroll = 0;
        std::vector<std::tuple<int, QString, CachedFont*>> line;
        std::vector<std::tuple<int, int, QString, CachedFont*>> display_list;
        CachedFont& get_font(int, QFont::Weight, bool);
        void flush();
        void open_tag(const QString&);
        void close_tag(const QString&);
        void add_word(const QString&);
};
