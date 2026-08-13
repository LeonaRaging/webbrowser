#include "layout/TextLayout.hpp"

struct LineLayout : public Layout {
    void layout() override;
    std::vector<std::unique_ptr<DrawCmd>> paint() override;

    LineLayout(Token*, Layout*, Layout*);
};