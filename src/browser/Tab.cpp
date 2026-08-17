#include "browser/Tab.hpp"
#include "browser/Canvas.hpp"

std::vector<std::pair<std::unique_ptr<Selector>, QHash<QString, QString>>> rules;

Tab::Tab(QWidget* parent): QWidget(parent) {
    canvas = new Canvas(this);
    canvas->setFixedSize(WIDTH, HEIGHT);
}

QString load_css() {
    QFile file("../resources/browser.css");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open browser.css:"
                << file.errorString();
        return "";
    }
    QString text = QString::fromUtf8(file.readAll());
    return text;
}

bool cascade_priority(const std::pair<std::unique_ptr<Selector>, QHash<QString, QString>>& left, const std::pair<std::unique_ptr<Selector>, QHash<QString, QString>>& right) {
    return left.first->priority < right.first->priority;    
}

void get_rules(const std::unique_ptr<Token>& node, URL& url) {
    std::vector<Token*> nodes;
    tree_to_list(node.get(), nodes);

    std::vector<QString> links;

    for (auto& node : nodes) {
        Element* element = dynamic_cast<Element*>(node);
        if (element && element->value == "link" &&
            element->attributes["rel"] == "stylesheet" &&
            element->attributes.contains("href"))
                links.push_back(element->attributes["href"]);
    }

    for (const QString& link : links) {
        URL style_url = url.resolve(link);
        QString body;
        try {
            body = QString::fromStdString(style_url.request());
        } catch (const std::exception& e) {
            continue;
        }
        auto new_rule = CSSParser(body).parse();
        rules.insert(
            rules.end(),
            std::make_move_iterator(new_rule.begin()),
            std::make_move_iterator(new_rule.end())
        );
    }

    std::sort(rules.begin(), rules.end(), cascade_priority);
}

void Tab::load(URL _url) {
    this->url = _url;
    history.push_back(_url);

    emit urlChanged(QString::fromStdString(_url.to_string()));

    std::string body = url.request();
    HTMLParser parser(QString::fromUtf8(body));

    node = std::move(parser.parse());

    rules = CSSParser(load_css()).parse();
    get_rules(node, url);

    ::style(node.get(), rules);
    
    document = std::unique_ptr<DocumentLayout>(new DocumentLayout(node.get()));
    document->layout();
    canvas->display_list.clear();
    paint_tree(document.get(), canvas->display_list);
    update();
}

void Tab::go_back() {
    if (history.size() > 1) {
        history.pop_back();
        URL url = history.back();
        history.pop_back();
        load(url);
    }
}