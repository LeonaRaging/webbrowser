#include "Browser.hpp"

Browser::Browser() {
    canvas = new Canvas();
    canvas->setFixedSize(WIDTH, HEIGHT);

    window.setCentralWidget(canvas);

    window.show();
}

std::vector<std::unique_ptr<Token>> lex(std::string body) {
    QString qbody = QString::fromUtf8(body.c_str());
    std::vector<std::unique_ptr<Token>> out;
    QString buffer;
    bool in_tag = false;
    for (QChar c : qbody) {
        if (c == '<') {
            in_tag = true;
            if (!buffer.isEmpty()) out.push_back(std::unique_ptr<Token>(new Text(buffer)));
            buffer = "";
        }
        else if (c == '>') {
            in_tag = false;
            out.push_back(std::unique_ptr<Token>(new Tag(buffer)));
            buffer = "";
        }
        else buffer += c;
    }
    return out;
}

void Browser::load(URL url) {
    std::string body = url.request();
    auto tokens = lex(body);
    canvas->layout(tokens);
}