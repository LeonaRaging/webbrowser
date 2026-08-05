#include <QMainWindow>
#include "browser/Canvas.hpp"
#include "layout/DocumentLayout.hpp"
#include "network/URL.hpp"
#include "html/Text.hpp"
#include "html/Element.hpp"
#include "html/HTMLParser.hpp"

struct Browser {
    QMainWindow window;
    Canvas* canvas;
    std::unique_ptr<DocumentLayout> document;

    void load(URL url);
    
    Browser();
};