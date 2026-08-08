#include "html/Element.hpp"
#include "css/CSSParser.hpp"

void style(Token*, const std::vector<std::pair<std::unique_ptr<Selector>, QHash<QString, QString>>>&);