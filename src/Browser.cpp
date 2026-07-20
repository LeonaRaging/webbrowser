#include "Browser.hpp"

Browser::Browser() {
    canvas = new Canvas();
    canvas->setFixedSize(WIDTH, HEIGHT);

    window.setCentralWidget(canvas);

    window.show();
}

std::string lex(std::string body) {
    bool in_tag = false;
    std::string text;
    for (char c : body) {
        if (c == '<') in_tag = true;
        else if (c == '>') in_tag = false;
        else if (!in_tag) text += c;
    }
    return text;
}

void Browser::load(URL url) {
    canvas->layout(lex(url.request()));
}