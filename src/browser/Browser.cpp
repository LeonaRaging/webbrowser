#include "browser/Browser.hpp"

Browser::Browser() {
    canvas = new Canvas();
    canvas->setFixedSize(WIDTH, HEIGHT);

    window.setCentralWidget(canvas);

    window.show();
}

void Browser::load(URL url) {
    std::string body = url.request();
    HTMLParser parser(QString::fromUtf8(body));
    auto nodes = std::move(parser.parse());
    document = std::unique_ptr<DocumentLayout>(new DocumentLayout(nodes.get()));
    document->layout();
    paint_tree(document.get(), canvas->display_list);
}