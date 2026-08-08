#include "css/TagSelector.hpp"

bool TagSelector::matches(Token* node) const {
    return (dynamic_cast<Element*>(node) && node->value == tag);
}

TagSelector::TagSelector(const QString& tag): tag(tag) {priority = 1;}