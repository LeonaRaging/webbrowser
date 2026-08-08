#pragma once

#include "html/Element.hpp"
#include "css/Selector.hpp"

struct TagSelector : public Selector {
    QString tag;

    bool matches(Token*) const override;

    TagSelector(const QString& tag);
};