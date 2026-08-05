#include "layout/Layout.hpp"
#include "layout/BlockLayout.hpp"

struct DocumentLayout : public Layout {

    std::vector<std::unique_ptr<DrawCmd>> paint() override;
    void layout() override;

    DocumentLayout(Token*);
    DocumentLayout(Token*, Layout*, Layout* previous);
};