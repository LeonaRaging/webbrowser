#include <QColor>
#include "painting/DrawCmd.hpp"

struct DrawRect : public DrawCmd {
    int left;
    int right;

    void execute(QPainter& painter, int scroll_pos) override;
    
    DrawRect(int, int ,int ,int, QColor);
};