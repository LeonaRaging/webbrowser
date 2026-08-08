#include "css/Style.hpp"

const QHash<QString, QString> INHERITED_PROPERTIES = {
    {"font-size", "16px"},
    {"font-style", "normal"},
    {"font-weight", "normal"},
    {"color", "black"}
};

void style(Token* node, const std::vector<std::pair<std::unique_ptr<Selector>, QHash<QString, QString>>>& rules) {
    for (auto it = INHERITED_PROPERTIES.begin(); it != INHERITED_PROPERTIES.end(); ++it) {
        if (node->parent) {
            node->style[it.key()] = node->parent->style[it.key()];
        } else {
            node->style[it.key()] = it.value();
        }
    }
    for (auto const& it : rules) {
        Selector* selector = it.first.get();
        auto body = it.second;
        if (!(selector->matches(node))) continue;
        for (auto it = body.begin(); it != body.end(); ++it) {
            node->style[it.key()] = it.value();
        }
    }
    Element* element = dynamic_cast<Element*>(node);
    if (element && element->attributes.contains("style")) {
        auto pairs = CSSParser(element->attributes["style"]).body();
        for (auto it = pairs.begin(); it != pairs.end(); ++it) {
            element->style[it.key()] = it.value();
        }
    }
    QString fontSize = node->style.value("font-size");
    if (fontSize.endsWith('%')) {
        QString parent_font_size;
        if (node->parent) {
            parent_font_size = node->parent->style.value("font-size");
        } else {
            parent_font_size = INHERITED_PROPERTIES.value("font-size");
        }
        double node_pct = fontSize.left(fontSize.length() - 1).toDouble() / 100.0;
        double parent_px = parent_font_size.left(parent_font_size.size() - 2).toDouble();
        node->style["font-size"] = QString::number(node_pct * parent_px) + "px";
    }
    for (auto const& child : node->children) {
        style(child.get(), rules);
    }
}