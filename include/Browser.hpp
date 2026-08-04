#include <QMainWindow>
#include "Canvas.hpp"
#include "DocumentLayout.hpp"
#include "URL.hpp"
#include "Text.hpp"
#include "Element.hpp"
#include "HTMLParser.hpp"

struct Browser {
    QMainWindow window;
    Canvas* canvas;
    std::unique_ptr<DocumentLayout> document;

    void load(URL url);
    
    Browser();
};