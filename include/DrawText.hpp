#include <QString>
#include "CachedFont.hpp"
#include "DrawCmd.hpp"

struct DrawText : public DrawCmd {
    int left;
    QString text;
    CachedFont* font;

    void execute(QPainter& painter) override;

    DrawText(int, int, QString, CachedFont*);
};