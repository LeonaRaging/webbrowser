#include "css/DescendantSelector.hpp"

bool DescendantSelector::matches(Token* node) const {
    if (!descendant->matches(node)) return false;
    while (node->parent) {
        if (ancestor->matches(node->parent)) return true;
        node = node->parent;
    }
    return false;
}
