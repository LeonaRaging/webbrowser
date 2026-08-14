#include <QMainWindow>
#include <QFile>
#include "layout/DocumentLayout.hpp"
#include "network/URL.hpp"
#include "html/Text.hpp"
#include "html/Element.hpp"
#include "html/HTMLParser.hpp"
#include "css/Style.hpp"

struct Canvas;

struct Browser {
    std::string url;
    QMainWindow window;
    Canvas* canvas;
    std::unique_ptr<Token> node;
    std::unique_ptr<DocumentLayout> document;

    void load(URL url);
    
    Browser();
};