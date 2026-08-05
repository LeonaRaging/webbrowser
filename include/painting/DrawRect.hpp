#include <QColor>
#include "painting/DrawCmd.hpp"

struct DrawRect : public DrawCmd {
    int left;
    int right;
    QColor color;

    void execute(QPainter& painter) override;
    
    DrawRect(int, int ,int ,int, QColor);
};