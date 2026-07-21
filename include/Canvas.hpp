#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QRegularExpression>
#include <unordered_map>
#include "Text.hpp"
#include "Tag.hpp"
#include "CachedFont.hpp"

const int WIDTH = 800;
const int HEIGHT = 600;

struct Canvas : public QWidget {
    public:
        void layout(const std::vector<std::unique_ptr<Token>>&);
        Canvas(QWidget *parent = nullptr);
    protected:
        void paintEvent(QPaintEvent *) override;
        void keyPressEvent(QKeyEvent*) override;
        void wheelEvent(QWheelEvent*) override;
        void scrollpage(int step);
    private:
        std::map<std::tuple<int, QFont::Weight, bool>, CachedFont> FONTS;
        int cursor_x, cursor_y, scroll = 0;
        std::vector<std::tuple<int, QString, CachedFont*>> line;
        std::vector<std::tuple<int, int, QString, CachedFont*>> display_list;
        CachedFont& get_font(int, QFont::Weight, bool);
        void flush();
};
