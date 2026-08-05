#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QWheelEvent>
#include "util/Util.hpp"
#include "util/CachedFont.hpp"
#include "painting/DrawCmd.hpp"

struct Canvas : public QWidget {
    std::vector<std::unique_ptr<DrawCmd>> display_list;
    
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent*) override;
    void wheelEvent(QWheelEvent*) override;
    void scrollpage(int step);
    
    Canvas(QWidget *parent = nullptr);
};
