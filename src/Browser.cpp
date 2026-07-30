#include "Browser.hpp"

Browser::Browser() {
    canvas = new Canvas();
    canvas->setFixedSize(WIDTH, HEIGHT);

    window.setCentralWidget(canvas);

    window.show();
}

void Browser::load(URL url) {
    std::string body = url.request();
    HTMLParser parser(QString::fromUtf8(body));
    auto nodes = parser.parse();
    canvas->recurse(nodes.get());
}